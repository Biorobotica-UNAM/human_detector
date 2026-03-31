import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
import numpy as np
import struct
from scipy.optimize import linear_sum_assignment
from std_msgs.msg import Bool
from sensor_msgs.msg import PointCloud2 
from visualization_msgs.msg import Marker, MarkerArray
from human_interfaces.msg import PersonTracks, PersonTrack
from geometry_msgs.msg import PointStamped

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs

MAX_TRACK_AGE = 15        # Frames que un track puede estar "perdido" antes de borrarse
MATCH_THRESHOLD = 1000.0   # Umbral de costo combinado (distancia + descriptor)
DIST_WEIGHT = 0.8         # Peso de la posición física (0.0 a 1.0)
DESC_WEIGHT = 0.2         # Peso de la apariencia (0.0 a 1.0)
MIN_HITS = 1              # Frames seguidos viendo a alguien para asignarle un ID estable


def normalize_descriptor(kp):
    try:
        s_l, s_r, h_l, h_r = kp[5], kp[6], kp[11], kp[12]
        if any(pt[2] < 0.2 for pt in [s_l, s_r, h_l, h_r]):
            return None

        def dist(a, b): return np.linalg.norm(a[:2] - b[:2])
        
        d_sh = dist(s_l, s_r)
        d_hp = dist(h_l, h_r)
        d_t_l = dist(s_l, h_l)
        d_t_r = dist(s_r, h_r)

        base = np.mean([d_sh, d_hp, d_t_l, d_t_r])
        if base < 1e-3: return None
        
        return np.array([d_sh/base, d_hp/base, d_t_l/base, d_t_r/base], dtype=np.float32)
    except:
        return None

#filtro kalman para suavizar la posicion y velocidad
class Track:
    def __init__(self, track_id, kp, desc):
        self.id = track_id
        self.desc = desc
        self.kp = kp
        self.age = 0
        self.hits = 1
        self.is_confirmed = False
        
        self.pos = np.mean(kp[:, :2], axis=0)
        self.vel = np.array([0.0, 0.0])

    def predict(self):
        self.pos += self.vel
        self.age += 1

    def update(self, kp, desc):
        self.kp = kp
        new_pos = np.mean(kp[:, :2], axis=0)
        new_vel = new_pos - self.pos
        self.vel = 0.7 * self.vel + 0.3 * new_vel
        
        self.pos = new_pos
        if desc is not None:
            self.desc = 0.9 * self.desc + 0.1 * desc
            
        self.age = 0
        self.hits += 1
        if self.hits >= MIN_HITS:
            self.is_confirmed = True


# nodo principal de tracking
class PersonTrackerNode(Node):
    def __init__(self):
        super().__init__('person_tracker_node')

        qos_pc = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        
        self.declare_parameter('enable_debug_markers', True)
        self.declare_parameter("point_cloud_topic", "/kinect/points")
        self.debug_mode = self.get_parameter('enable_debug_markers').value

        # TF2 listener
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Subscribers
        detection_enable = self.create_subscription(Bool, '/person_tracker/enable', self.detection_callback, 10)
        self.sub_pc = self.create_subscription(PointCloud2, self.get_parameter("point_cloud_topic").value, self.pc_callback, qos_pc)
        self.sub_kp = self.create_subscription(PersonTracks, '/human_detection/keypoints', self.callback, 10)
        
        # Publishers
        self.pub_tracks = self.create_publisher(PersonTracks, "/human_detection/person_tracks", 10)
        self.marker_pub = self.create_publisher(MarkerArray, '/human_detection/track_markers', 10)
        self.target_points = self.create_publisher(PointStamped, '/human_detection/target_point', 10)

        self.enabled = False
        self.latest_pc = None
        self.tracks = []
        self.next_id = 0
        self.get_logger().info("Tracker Node Ready")

    def pc_callback(self, msg):
        self.latest_pc = msg

    def get_3d_point(self, u, v):
        if self.latest_pc is None:return None
        try:
            u_idx = int(np.clip(u, 0, self.latest_pc.width - 1))
            v_idx = int(np.clip(v, 0, self.latest_pc.height - 1))

            offset = (v_idx * self.latest_pc.row_step) + (u_idx * self.latest_pc.point_step)
            x, y, z = struct.unpack('fff', self.latest_pc.data[offset:offset+12])

            if np.isnan(x) or np.isnan(y) or np.isnan(z): return None
            return (x, y, z)
        except Exception as e:
            self.get_logger().error(f"ERROR TO SEE THE 3D POINT: {e}")
            return None
    """
    def callback(self, msg):
        # 1. Preparar deteccione
        current_dets = []
        for det in msg.persons:
            raw_kp = np.array(det.keypoints)
            if raw_kp.size >= 51:
                kp_resat = raw_kp[:51]
                kp = kp_resat.reshape((17, 3))
            else:
                self.get_logger().warn(f"deteccion fail: ({raw_kp.size}/51)")
                continue
            desc = normalize_descriptor(kp)
            if desc is not None:
                current_dets.append({
                    'kp': kp, 
                    'desc': desc, 
                    'pos': np.mean(kp[:, :2], axis=0)
                })

        #self.get_logger().info(f"Detecciones procesadas: {len(current_dets)}")
        for t in self.tracks:
            t.predict()

        assigned_dets = set()
        if len(self.tracks) > 0 and len(current_dets) > 0:
            cost_matrix = self._build_cost_matrix(current_dets)
            row_ind, col_ind = linear_sum_assignment(cost_matrix)
            
            for t_idx, d_idx in zip(row_ind, col_ind):
                if cost_matrix[t_idx, d_idx] < MATCH_THRESHOLD:
                    self.tracks[t_idx].update(current_dets[d_idx]['kp'], current_dets[d_idx]['desc'])
                    assigned_dets.add(d_idx)

            self.get_logger().info(f"Tracks actualizados: {len(assigned_dets)}")

        self.tracks = [t for t in self.tracks if t.age < MAX_TRACK_AGE]

        # 5. Crear nuevos tracks
        for i, det in enumerate(current_dets):
            if i not in assigned_dets:
                self.tracks.append(Track(self.next_id, det['kp'], det['desc']))
                self.next_id += 1
        
        #self.get_logger().info(f"Tracks activos en memoria: {len(self.tracks)}")

        self._publish_tracks()
        """
    
    def detection_callback(self, msg):
        self.enabled = msg.data
        if not self.enabled:
            self.get_logger().info("Detección deshabilitada, limpiando tracks...")
            self.tracks.clear()
            self._publish_tracks()  # Publicar mensaje vacío para limpiar visualización
            return

    
    def callback(self, msg):
        if not self.enabled: return
        
        current_dets = []
        for det in msg.persons:
            raw_kp = np.array(det.keypoints)
            if raw_kp.size >= 51:
                kp = raw_kp[:51].reshape((17, 3))
                desc = normalize_descriptor(kp)
                if desc is not None:
                    current_dets.append({'kp': kp, 'desc': desc, 'pos': np.mean(kp[:, :2], axis=0)})

        for t in self.tracks: t.predict()

        assigned_dets = set()
        if self.tracks and current_dets:
            cost_matrix = self._build_cost_matrix(current_dets)
            row_ind, col_ind = linear_sum_assignment(cost_matrix)
            for t_idx, d_idx in zip(row_ind, col_ind):
                if cost_matrix[t_idx, d_idx] < MATCH_THRESHOLD:
                    self.tracks[t_idx].update(current_dets[d_idx]['kp'], current_dets[d_idx]['desc'])
                    assigned_dets.add(d_idx)

        self.tracks = [t for t in self.tracks if t.age < MAX_TRACK_AGE]

        for i, det in enumerate(current_dets):
            if i not in assigned_dets:
                self.tracks.append(Track(self.next_id, det['kp'], det['desc']))
                self.next_id += 1
        
        self._publish_tracks()

    def _build_cost_matrix(self, detections):
        cost = np.zeros((len(self.tracks), len(detections)))
        for i, tr in enumerate(self.tracks):
            for j, det in enumerate(detections):
                d_pos = np.linalg.norm(tr.pos - det['pos'])
                d_desc = np.linalg.norm(tr.desc - det['desc'])
                cost[i, j] = (DIST_WEIGHT * d_pos) + (DESC_WEIGHT * d_desc * 100)
        return cost

    def _publish_tracks(self):
        if self.latest_pc is None:
            return
        
        current_frame = self.latest_pc.header.frame_id
        now = self.get_clock().now()
        
        msg = PersonTracks()
        msg.header.frame_id = current_frame
        msg.header.stamp = now.to_msg()

        if len(self.tracks) == 0: return
        tr = self.tracks[0]
        real_pos = self.get_3d_point(tr.pos[0], tr.pos[1])

        if real_pos:
            target_msg = PointStamped()
            # Crear el punto en el frame de la cámara
            target_msg.header.stamp = self.latest_pc.header.stamp 
            target_msg.header.frame_id = current_frame
            target_msg.point.x, target_msg.point.y, target_msg.point.z = map(float, real_pos)
            try:
                transform = self.tf_buffer.lookup_transform(
                    "base_link",
                    target_msg.header.frame_id, 
                    rclpy.time.Time())
                
                final_point = tf2_geometry_msgs.do_transform_point(target_msg, transform)
                self.target_points.publish(final_point)
                
            except Exception as e:
                self.get_logger().warn(f"TF Falló, usando frame local: {e}", throttle_duration_sec=2.0)


        if self.debug_mode:
                marker_array = MarkerArray()
                sphere = Marker()
                sphere.header.frame_id = final_point.header.frame_id
                sphere.header.stamp = now.to_msg()
                sphere.ns = "HumanTracks"; sphere.id = 0; sphere.type = Marker.SPHERE
                sphere.action = Marker.ADD
                sphere.pose.position = final_point.point
                sphere.scale.x = sphere.scale.y = sphere.scale.z = 0.2
                sphere.color.r, sphere.color.g, sphere.color.a = 1.0, 1.0, 0.8
                marker_array.markers.append(sphere)
                self.marker_pub.publish(marker_array)

        # Publicar mensaje de PersonTracks para otros nodos
        pt = PersonTrack()
        pt.id = tr.id
        pt.keypoints = tr.kp.flatten().tolist()
        pt.position = tr.pos.tolist()
        msg.persons.append(pt)
        self.pub_tracks.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = PersonTrackerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        #rclpy.shutdown()

if __name__ == '__main__':
    main()