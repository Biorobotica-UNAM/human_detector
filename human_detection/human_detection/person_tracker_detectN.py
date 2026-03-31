import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
import numpy as np
import struct
from scipy.optimize import linear_sum_assignment
from std_msgs.msg import Bool
from sensor_msgs.msg import PointCloud2 
from visualization_msgs.msg import Marker, MarkerArray
from vision_interfaces.msg import YoloDetections, YoloDetection # Mensajes del nuevo nodo
from human_interfaces.msg import PersonTracks, PersonTrack
from geometry_msgs.msg import PointStamped
from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs

# Parámetros de seguimiento
MAX_TRACK_AGE = 15
MATCH_THRESHOLD = 500.0   # Ajustado para Bboxes
DIST_WEIGHT = 0.7
DESC_WEIGHT = 0.3
MIN_HITS = 1

def get_bbox_descriptor(det):
    """
    Genera un descriptor simple basado en la forma de la caja.
    Ayuda a distinguir entre personas de diferentes tamaños/distancias.
    """
    w = det.x_max - det.x_min
    h = det.y_max - det.y_min
    aspect_ratio = w / h if h > 0 else 0
    area = w * h
    return np.array([aspect_ratio, area], dtype=np.float32)

class Track:
    def __init__(self, track_id, bbox_center, desc):
        self.id = track_id
        self.desc = desc
        self.age = 0
        self.hits = 1
        self.is_confirmed = False
        
        self.pos = bbox_center # (x_center, y_center)
        self.vel = np.array([0.0, 0.0])

    def predict(self):
        self.pos += self.vel
        self.age += 1

    def update(self, bbox_center, desc):
        new_vel = bbox_center - self.pos
        self.vel = 0.7 * self.vel + 0.3 * new_vel
        self.pos = bbox_center
        
        if desc is not None:
            self.desc = 0.9 * self.desc + 0.1 * desc
            
        self.age = 0
        self.hits += 1
        if self.hits >= MIN_HITS:
            self.is_confirmed = True

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
        self.declare_parameter("yolo_topic", "/yolo/detections_list")
        
        self.debug_mode = self.get_parameter('enable_debug_markers').value

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Suscripciones
        self.sub_enable = self.create_subscription(Bool, '/person_tracker/enable', self.detection_callback, 10)
        self.sub_pc = self.create_subscription(PointCloud2, self.get_parameter("point_cloud_topic").value, self.pc_callback, qos_pc)
        # Cambio: Ahora escuchamos YoloDetections
        self.sub_yolo = self.create_subscription(YoloDetections, self.get_parameter("yolo_topic").value, self.yolo_callback, 10)
        
        # Publicadores
        self.pub_tracks = self.create_publisher(PersonTracks, "/human_detection/person_tracks", 10)
        self.marker_pub = self.create_publisher(MarkerArray, '/human_detection/track_markers', 10)
        self.target_points = self.create_publisher(PointStamped, '/human_detection/target_point', 10)

        self.enabled = False
        self.latest_pc = None
        self.tracks = []
        self.next_id = 0
        self.get_logger().info("Bbox Tracker Node Ready")

    def pc_callback(self, msg):
        self.latest_pc = msg

    def get_3d_point(self, u, v):
        if self.latest_pc is None: return None
        try:
            u_idx = int(np.clip(u, 0, self.latest_pc.width - 1))
            v_idx = int(np.clip(v, 0, self.latest_pc.height - 1))
            offset = (v_idx * self.latest_pc.row_step) + (u_idx * self.latest_pc.point_step)
            x, y, z = struct.unpack('fff', self.latest_pc.data[offset:offset+12])
            if np.isnan(x) or np.isnan(y) or np.isnan(z): return None
            return (x, y, z)
        except Exception as e:
            return None

    def detection_callback(self, msg):
        self.enabled = msg.data
        if not self.enabled:
            self.tracks.clear()
            self._publish_empty_markers()

    def yolo_callback(self, msg):
        if not self.enabled: return
        
        current_dets = []
        for det in msg.detections:
            # Solo trackear personas
            if det.class_name != 'person':
                continue
            
            # Centro de la caja para la posición 2D
            cx = (det.x_min + det.x_max) / 2.0
            cy = (det.y_min + det.y_max) / 2.0
            
            desc = get_bbox_descriptor(det)
            current_dets.append({
                'pos': np.array([cx, cy]),
                'desc': desc,
                'bbox': [det.x_min, det.y_min, det.x_max, det.y_max]
            })

        # Predicción de tracks existentes
        for t in self.tracks: t.predict()

        # Asociación de datos (Hungarian Algorithm)
        assigned_dets = set()
        if self.tracks and current_dets:
            cost_matrix = self._build_cost_matrix(current_dets)
            row_ind, col_ind = linear_sum_assignment(cost_matrix)
            for t_idx, d_idx in zip(row_ind, col_ind):
                if cost_matrix[t_idx, d_idx] < MATCH_THRESHOLD:
                    self.tracks[t_idx].update(current_dets[d_idx]['pos'], current_dets[d_idx]['desc'])
                    assigned_dets.add(d_idx)

        # Limpieza de tracks viejos
        self.tracks = [t for t in self.tracks if t.age < MAX_TRACK_AGE]

        # Nuevos tracks
        for i, det in enumerate(current_dets):
            if i not in assigned_dets:
                self.tracks.append(Track(self.next_id, det['pos'], det['desc']))
                self.next_id += 1
        
        self._publish_tracks()

    def _build_cost_matrix(self, detections):
        cost = np.zeros((len(self.tracks), len(detections)))
        for i, tr in enumerate(self.tracks):
            for j, det in enumerate(detections):
                d_pos = np.linalg.norm(tr.pos - det['pos'])
                # Escalamos d_desc porque los valores de área son grandes
                d_desc = np.linalg.norm(tr.desc - det['desc']) 
                cost[i, j] = (DIST_WEIGHT * d_pos) + (DESC_WEIGHT * d_desc)
        return cost

    def _publish_tracks(self):
        if not self.tracks or self.latest_pc is None:
            return
        
        now = self.get_clock().now()
        current_frame = self.latest_pc.header.frame_id
        
        # Mensaje de salida compatible
        msg = PersonTracks()
        msg.header.frame_id = current_frame
        msg.header.stamp = now.to_msg()

        # Tomamos el track más cercano/importante (el primero en este caso)
        tr = self.tracks[0]
        real_pos = self.get_3d_point(tr.pos[0], tr.pos[1])

        if real_pos:
            target_pt = PointStamped()
            target_pt.header.frame_id = current_frame
            target_pt.header.stamp = now.to_msg()
            target_pt.point.x, target_pt.point.y, target_pt.point.z = map(float, real_pos)

            # Transformación a mapa
            try:
                transformed_msg = self.tf_buffer.transform(target_pt, 'map', timeout=rclpy.duration.Duration(seconds=0.05))
                self.target_points.publish(transformed_msg)
                
                if self.debug_mode:
                    self._publish_debug_marker(transformed_msg)
            except Exception:
                self.target_points.publish(target_pt)

        # Publicar todos los tracks activos
        for t in self.tracks:
            pt = PersonTrack()
            pt.id = t.id
            pt.position = [t.pos[0], t.pos[1], 0.0] # Posición 2D en imagen
            msg.persons.append(pt)
        
        self.pub_tracks.publish(msg)

    def _publish_debug_marker(self, point_stamped):
        marker_array = MarkerArray()
        sphere = Marker()
        sphere.header = point_stamped.header
        sphere.ns = "HumanTracks"; sphere.id = 0; sphere.type = Marker.SPHERE
        sphere.action = Marker.ADD
        sphere.pose.position = point_stamped.point
        sphere.scale.x = sphere.scale.y = sphere.scale.z = 0.25
        sphere.color.r, sphere.color.g, sphere.color.b, sphere.color.a = 0.0, 1.0, 0.0, 0.8
        marker_array.markers.append(sphere)
        self.marker_pub.publish(marker_array)

    def _publish_empty_markers(self):
        empty = MarkerArray()
        m = Marker()
        m.action = Marker.DELETEALL
        empty.markers.append(m)
        self.marker_pub.publish(empty)

def main(args=None):
    rclpy.init(args=args)
    node = PersonTrackerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()