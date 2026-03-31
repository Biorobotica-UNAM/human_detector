import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
import numpy as np
import struct
from scipy.optimize import linear_sum_assignment
from sensor_msgs.msg import PointCloud2 
from visualization_msgs.msg import Marker, MarkerArray
from vision_interfaces.msg import YoloDetections, YoloDetection
from geometry_msgs.msg import PointStamped
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs


MIN_CONFIDENCE = 0.85      # 85% de confianza mínimo
SMOOTHING_FACTOR = 0.18     # Suavizado de movimiento (0.1 a 0.5) menor = más suave/lento, mayor = más reactivo/rapido
MAX_LOST_FRAMES = 45       # ~1.5 segundos de espera antes de buscar a otro humano
MATCH_THRESHOLD = 400.0    # Umbral de asociación entre frames

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

        self.declare_parameter("point_cloud_topic", "/kinect/points")
        self.declare_parameter("target_frame", "kinect_depth_fixed") #base_link

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Variables de bloqueo
        self.target_id = None
        self.lost_frames = 0

        # Suscriptores
        self.sub_yolo = self.create_subscription(YoloDetections, 'detections_list', self.callback, 10)
        self.sub_pc = self.create_subscription(
            PointCloud2, self.get_parameter("point_cloud_topic").value, 
            self.pc_callback, QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT, depth=1))

        # Publicadores
        self.pub_target = self.create_publisher(PointStamped, '/human_detection/target_point', 10)
        self.marker_pub = self.create_publisher(MarkerArray, '/human_detection/track_markers', 10)

        self.latest_pc = None
        self.tracks = []
        self.next_id = 0
        
        self.get_logger().info(" human Tracker reafy to track humans")

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
                cx, cy = (det.x_min + det.x_max) / 2.0, (det.y_min + det.y_max) / 2.0
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

        # Lógica de Bloqueo (Filtra solo al ID elegido)
        selected_track = None
        if self.target_id is not None:
            selected_track = next((t for t in self.tracks if t.id == self.target_id), None)
            
            if not selected_track:
                self.lost_frames += 1
                if self.lost_frames % 10 == 0:
                    self.get_logger().warn(f"Person {self.target_id} lost...")
            else:
                self.lost_frames = 0

        # Si no hay objetivo o se perdió definitivamente, buscar al más central
        if self.target_id is None or self.lost_frames >= MAX_LOST_FRAMES:
            confirmed = [t for t in self.tracks if t.is_confirmed]
            if confirmed:
                confirmed.sort(key=lambda t: abs(t.pos[0] - 320))
                self.target_id = confirmed[0].id
                self.get_logger().info(f" New Person: ID {self.target_id}")

        if selected_track:
            raw_3d = self.get_3d_point(selected_track.pos[0], selected_track.pos[1])
            if raw_3d:
                self._send_goal(raw_3d, selected_track.id)

    def _send_goal(self, coords, tid):
        p = PointStamped()
        p.header.frame_id = self.latest_pc.header.frame_id
        p.header.stamp = self.get_clock().now().to_msg()
        p.point.x, p.point.y, p.point.z = map(float, coords)

        try:
            t_frame = self.get_parameter("target_frame").value
            trans = self.tf_buffer.lookup_transform(t_frame, p.header.frame_id, rclpy.time.Time())
            p_base = tf2_geometry_msgs.do_transform_point(p, trans)
            self.pub_target.publish(p_base)
            self._publish_marker(p_base, tid)
        except: pass

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