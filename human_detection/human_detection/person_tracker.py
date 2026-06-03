import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
import numpy as np
import struct
from scipy.optimize import linear_sum_assignment
from sensor_msgs.msg import PointCloud2 
from visualization_msgs.msg import Marker, MarkerArray
from vision_interfaces.msg import YoloDetections, YoloDetection
from geometry_msgs.msg import PointStamped
from std_srvs.srv import SetBool, Trigger
from std_msgs.msg import Float32, Bool
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs


MIN_CONFIDENCE = 0.85      # 85% de confianza mínimo
SMOOTHING_FACTOR = 0.18     # Suavizado de movimiento (0.1 a 0.5) menor = más suave/lento, mayor = más reactivo/rapido
MAX_LOST_FRAMES = 45       # ~1.5 segundos de espera antes de buscar a otro humano
MATCH_THRESHOLD = 400.0    # Umbral de asociación entre frames

# --- Suavizado de cabeza ---
HEAD_MOVEMENT_THRESHOLD = 0.02  
POSITION_SMOOTHING = 0.25       # suavizado adicional de la posición 3D (menor = más suave)

class Track:
    def __init__(self, track_id, pos_2d, desc):
        self.id = track_id
        self.desc = desc
        self.age = 0
        self.hits = 1
        self.is_confirmed = False
        self.pos = pos_2d 
        self.vel = np.array([0.0, 0.0])

    def predict(self):
        self.pos = self.pos + self.vel
        self.age += 1

    #filtro
    def update(self, pos_2d, desc):
    
        new_vel = pos_2d - self.pos
        self.vel = (1 - SMOOTHING_FACTOR) * self.vel + SMOOTHING_FACTOR * new_vel
        self.pos = (1 - SMOOTHING_FACTOR) * self.pos + SMOOTHING_FACTOR * pos_2d
        
        if desc is not None:
            self.desc = 0.95 * self.desc + 0.05 * desc
        self.age = 0
        self.hits += 1
        if self.hits >= 3: self.is_confirmed = True

class PersonTrackerNode(Node):
    def __init__(self):
        super().__init__('person_tracker_node')

        qos_pc = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        self.declare_parameter("point_cloud_topic", "/kinect/points")
        self.declare_parameter("target_frame", "base_link")

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Variables de bloqueo
        self.target_id = None
        self.lost_frames = 0
        self.tracking_enabled = False

        # Suavizado de cabeza
        self.last_published_pos = None
        self.smoothed_pos = None

        # Suscriptores
        self.sub_yolo = self.create_subscription(YoloDetections, '/vision/detections_list', self.callback, 10)
        self.sub_pc = self.create_subscription(PointCloud2, self.get_parameter("point_cloud_topic").value, self.pc_callback, qos_pc)

        # Publicadores
        self.pub_target = self.create_publisher(PointStamped, '/human_detection/target_point', 10)
        self.pub_confidence = self.create_publisher(Float32, '/hri/human_tracking/confidence', 10)
        self.pub_look_at = self.create_publisher(PointStamped, '/hardware/head/look_at', 10)
        self.marker_pub = self.create_publisher(MarkerArray, '/human_detection/track_markers', 10)
        self.pub_bypass = self.create_publisher(Bool, '/navigation/camera_obstacles/bypass', 10)

        self.srv_focus = self.create_service(SetBool, '/vision/focus', self.handle_focus_service)
        self.srv_focus_enable = self.create_service(Trigger,'/vision/focus/enable', self.handle_focus_enable_service)
        self.srv_focus_disable = self.create_service(Trigger,'/vision/focus/disable', self.handle_focus_disable_service)
        self.cli_enable_continuous = self.create_client(SetBool, '/vision/enable_continuous')

        self.latest_pc = None
        self.tracks = []
        self.next_id = 0
        
        self.get_logger().info(" human Tracker ready!")

    def update_head_focus(self, target_point):
        if self.tracking_enabled:
            msg = PointStamped()
            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = "base_link"
            msg.point = target_point
            self.pub_look_at.publish(msg)

            bypass_msg = Bool()
            bypass_msg.data = True
            self.pub_bypass.publish(bypass_msg)

    def handle_focus_enable_service(self, request, response):
        self.tracking_enabled = True
        msg_bypass = Bool()
        msg_bypass.data = True
        self.pub_bypass.publish(msg_bypass)
        self.cli_enable_continuous.call_async(SetBool.Request(data=True))
        response.success = True
        response.message = "Head tracking focus ENABLED"
        self.get_logger().info(response.message)
        return response

    def handle_focus_disable_service(self, request, response):
        self.tracking_enabled = False
        bypass_msg = Bool()
        bypass_msg.data = False
        self.pub_bypass.publish(bypass_msg)
        self.cli_enable_continuous.call_async(SetBool.Request(data=False))
        response.success = True
        response.message = "Head tracking focus DISABLED"
        self.get_logger().info(response.message)
        return response

    def handle_focus_service(self, request, response):
        """Manejador del servicio para activar/desactivar el seguimiento visual."""
        self.tracking_enabled = request.data
        bypass_msg = Bool()
        bypass_msg.data = self.tracking_enabled
        self.pub_bypass.publish(bypass_msg)
        self.cli_enable_continuous.call_async(SetBool.Request(data=self.tracking_enabled))
        response.success = True
        status = "ENABLED" if self.tracking_enabled else "DISABLED"
        response.message = f"Head tracking focus is now {status}"
        self.get_logger().info(response.message)
        return response

    def pc_callback(self, msg):
        self.latest_pc = msg

    def get_3d_point(self, u, v):
        if self.latest_pc is None: return None
        # Muestreo circular: Si el centro falla, busca en los alrededores
        search_pattern = [(0,0), (3,3), (-3,-3), (3,-3), (-3,3), (0,5), (0,-5)]
        for du, dv in search_pattern:
            try:
                offset = (int(v+dv) * self.latest_pc.row_step) + (int(u+du) * self.latest_pc.point_step)
                x, y, z = struct.unpack('fff', self.latest_pc.data[offset:offset+12])
                if not np.isnan(x) and x != 0: return (x, y, z)
            except: continue
        return None

    def callback(self, msg):
        current_dets = []
        for det in msg.detections:
            if det.class_name == "person" and det.confidence >= MIN_CONFIDENCE:
                cx = (det.x_min + det.x_max) / 2
                cy = det.y_min + (det.y_max - det.y_min) * 0.15 # ajuste para mover el punto dentro de un % del Bbox, grax
                w, h = (det.x_max - det.x_min), (det.y_max - det.y_min)
                desc = np.array([w/h, w*h]) if h != 0 else np.array([0.0, 0.0])
                current_dets.append({'pos': np.array([cx, cy]), 'desc': desc})

        for t in self.tracks: t.predict()

        assigned_dets = set()
        if self.tracks and current_dets:
            cost_matrix = self._build_cost_matrix(current_dets)
            row_ind, col_ind = linear_sum_assignment(cost_matrix)
            for t_idx, d_idx in zip(row_ind, col_ind):
                if cost_matrix[t_idx, d_idx] < MATCH_THRESHOLD:
                    self.tracks[t_idx].update(current_dets[d_idx]['pos'], current_dets[d_idx]['desc'])
                    assigned_dets.add(d_idx)

        self.tracks = [t for t in self.tracks if t.age < 20]
        for i, det in enumerate(current_dets):
            if i not in assigned_dets:
                self.tracks.append(Track(self.next_id, det['pos'], det['desc']))
                self.next_id += 1
        
        self._process_output()

    def _build_cost_matrix(self, detections):
        cost = np.zeros((len(self.tracks), len(detections)))
        for i, tr in enumerate(self.tracks):
            for j, det in enumerate(detections):
                cost[i, j] = np.linalg.norm(tr.pos - det['pos']) + (np.abs(tr.desc[0] - det['desc'][0]) * 50)
        return cost

    def _process_output(self):
        if not self.tracks or self.latest_pc is None: return

        selected_track = None
        if self.target_id is not None:
            selected_track = next((t for t in self.tracks if t.id == self.target_id), None)
            
            if not selected_track:
                self.lost_frames += 1
                if self.lost_frames % 10 == 0:
                    self.get_logger().warn(f"Person {self.target_id} lost...")
            else:
                self.lost_frames = 0

        if self.target_id is None or self.lost_frames >= MAX_LOST_FRAMES:
            
            if self.tracking_enabled:
                bypass_msg = Bool()
                bypass_msg.data = False
                self.pub_bypass.publish(bypass_msg)
            
            confirmed = [t for t in self.tracks if t.is_confirmed]
            if confirmed:
                center_x = self.latest_pc.width / 2
                confirmed.sort(key=lambda t: abs(t.pos[0] - center_x))
                #confirmed.sort(key=lambda t: abs(t.pos[0] - 320))
                self.target_id = confirmed[0].id
                self.smoothed_pos = None
                self.last_published_pos = None
                self.get_logger().info(f" New Person: ID {self.target_id}")

    
        if self.target_id is not None:
            selected_track = next((t for t in self.tracks if t.id == self.target_id), None)

        if selected_track:
            raw_3d = self.get_3d_point(selected_track.pos[0], selected_track.pos[1])
            if raw_3d:
                self._send_outputs(raw_3d, selected_track.id)

    def _send_outputs(self, coords, tid):
        p = PointStamped()
        p.header.frame_id = self.latest_pc.header.frame_id
        p.header.stamp = self.get_clock().now().to_msg()
        p.point.x, p.point.y, p.point.z = map(float, coords)

        try:
            t_frame = self.get_parameter("target_frame").value
            trans = self.tf_buffer.lookup_transform(t_frame, p.header.frame_id, rclpy.time.Time())
            p_base = tf2_geometry_msgs.do_transform_point(p, trans)

            new_pos = np.array([p_base.point.x, p_base.point.y, p_base.point.z])
            if self.smoothed_pos is None:
                self.smoothed_pos = new_pos
            else:
                self.smoothed_pos = (1 - POSITION_SMOOTHING) * self.smoothed_pos + POSITION_SMOOTHING * new_pos
            p_base.point.x, p_base.point.y, p_base.point.z = self.smoothed_pos

            conf_msg = Float32()
            conf_msg.data = float(min(1.0, self.tracks[0].hits / 10.0)) if self.tracks else 0.0 
            self.pub_confidence.publish(conf_msg)
            self.pub_target.publish(p_base)
            
            if self.tracking_enabled:
                bypass_msg = Bool()
                bypass_msg.data = True
                self.pub_bypass.publish(bypass_msg)

                if self.last_published_pos is None or \
                   np.linalg.norm(self.smoothed_pos - self.last_published_pos) > HEAD_MOVEMENT_THRESHOLD:
                    self.pub_look_at.publish(p_base)
                    self.last_published_pos = self.smoothed_pos.copy()
            else:
                bypass_msg = Bool()
                bypass_msg.data = False
                self.pub_bypass.publish(bypass_msg)

            self._publish_marker(p_base, tid)
        except Exception as e:
            self.get_logger().error(f"Transform error: {e}")

    def _publish_marker(self, p_base, tid):
        ma = MarkerArray()
        m = Marker()
        m.header = p_base.header
        m.id = 999
        m.type = Marker.TEXT_VIEW_FACING
        m.text = f"TARGET LOCKED: {tid}"
        m.pose.position = p_base.point
        m.pose.position.z += 0.6
        m.scale.z = 0.25
        m.color.r, m.color.g, m.color.b, m.color.a = 1.0, 0.0, 0.0, 1.0
        
        m2 = Marker()
        m2.header = p_base.header
        m2.id = tid
        m2.type = Marker.CYLINDER
        m2.pose.position = p_base.point
        m2.scale.x = m2.scale.y = 0.3; m2.scale.z = 0.1
        m2.color.r, m2.color.a = 1.0, 0.7
        
        ma.markers.extend([m, m2])
        self.marker_pub.publish(ma)

def main():
    rclpy.init()
    node = PersonTrackerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()