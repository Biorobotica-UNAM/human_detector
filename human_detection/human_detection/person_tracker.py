#!/usr/bin/env python3
# =============================================================================
#  person_tracker.py  —  RoboCup-grade version
#  Fixes vs original:
#    [BUG-1] enable_callback ya no es un stub vacío. El nodo respeta el estado
#            de enable y deja de procesar + publicar cuando está desactivado.
#    [BUG-2] Limpieza de tracks al desactivar para no publicar estados residuales
#            al re-activar el sistema.
#  Mejoras:
#    [OPT-1] Publicación de MarkerArray para TODOS los tracks confirmados, no
#            solo el target. Facilita depuración en RViz2.
#    [OPT-2] Reenganche de target perdido: si el target_track_id desaparece,
#            el sistema busca el track confirmado más cercano a la última posición
#            conocida en lugar de simplemente seleccionar el más centrado.
#    [OPT-3] Descriptor de track enriquecido: incluye aspect ratio del bounding
#            box para diferenciar mejor entre personas.
#    [OPT-4] Publicación de diagnóstico: número de tracks activos y confianza.
#    [OPT-5] Ventana de mediana ampliada y fallback iterativo para nube de puntos.
# =============================================================================

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
from std_msgs.msg import Bool, Int32, Float32
from std_srvs.srv import SetBool
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener
import tf2_geometry_msgs

# Parámetros globales
MIN_CONFIDENCE    = 0.85   # confianza mínima YOLO
SMOOTHING_FACTOR  = 0.18   # suavizado de posición (no usado directamente, mantenido para compatibilidad)
MAX_LOST_FRAMES   = 45     # ~1.5 s antes de descartar un track
MATCH_THRESHOLD   = 400.0  # umbral de coste para asociar detección a track
MIN_HITS_CONFIRM  = 3      # hits mínimos para confirmar un track
REATTACH_RADIUS   = 1.5    # radio en píxeles para reenganche de target


class Track:
    """Mantiene el estado de una persona detectada a lo largo del tiempo."""

    def __init__(self, track_id: int, pos_2d: np.ndarray, desc: np.ndarray):
        self.id           = track_id
        self.desc         = desc.copy()
        self.age          = 0
        self.hits         = 1
        self.is_confirmed = False
        self.pos          = pos_2d.copy()
        self.vel          = np.zeros(2)
        self.last_pos     = pos_2d.copy()   

    def predict(self):
        self.last_pos = self.pos.copy()
        self.pos = self.pos + self.vel
        self.age += 1

    def update(self, pos_2d: np.ndarray, desc: np.ndarray):
        new_vel   = pos_2d - self.pos
        self.vel  = 0.3 * new_vel + 0.7 * self.vel
        self.last_pos = self.pos.copy()
        self.pos  = pos_2d.copy()
        self.desc = 0.5 * desc + 0.5 * self.desc
        self.age  = 0
        self.hits += 1
        if self.hits >= MIN_HITS_CONFIRM:
            self.is_confirmed = True


class PersonTracker(Node):

    def __init__(self):
        super().__init__('person_tracker')
        self.get_logger().info("INITIALIZING PERSON TRACKER ...")

        # Estado de enable inicializado 
        self.tracking_enabled = False
        self.enable_active    = False  

        self.tf_buffer   = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        qos_pc = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Suscriptores
        self.sub_yolo   = self.create_subscription(
            YoloDetections, '/vision/yolo_detections', self.yolo_callback, 10)
        
        self.sub_pc     = self.create_subscription(
            PointCloud2, '/camera/camera/depth/color/points',
            self.pc_callback, qos_profile=qos_pc)
        
        self.sub_enable = self.create_subscription(
            Bool, '/vision/enable_continuous', self.enable_callback, 10)

        # Publicadores 
        self.pub_target     = self.create_publisher(PointStamped,  '/hri/human_tracking/target_point', 10)
        self.pub_look_at    = self.create_publisher(PointStamped,  '/hri/human_tracking/look_at_point', 10)
        self.pub_markers    = self.create_publisher(MarkerArray,   '/hri/human_tracking/markers', 10)

        # topic de Diagnóstico
        self.pub_num_tracks = self.create_publisher(Int32,         '/hri/human_tracking/num_tracks', 10)
        self.pub_confidence = self.create_publisher(Float32,       '/hri/human_tracking/confidence', 10)

        # Servicio focus
        self.srv_focus = self.create_service(
            SetBool, '/vision/focus', self.handle_focus_service)

        # Cliente de enable conti
        self.cli_enable_continuous = self.create_client(SetBool, '/vision/enable_continuous')

    
        self.tracks          = []
        self.next_id         = 1
        self.latest_pc       = None
        self.target_track_id = None
        self.last_target_pos = None  

    def enable_callback(self, msg: Bool):
        prev = self.enable_active
        self.enable_active = msg.data

        if not self.enable_active and prev:

            # limpia estado al desactivar
            self.get_logger().info("PersonTracker: DISABLED")
            self.tracks          = []
            self.target_track_id = None
            self.last_target_pos = None
            self.latest_pc       = None
            ma = MarkerArray()
            m = Marker()
            m.action = Marker.DELETEALL
            ma.markers.append(m)
            self.pub_markers.publish(ma)

        elif self.enable_active and not prev:
            self.get_logger().info("PersonTracker: ENABLED")

    # Servicio focus
    def handle_focus_service(self, request, response):
        self.tracking_enabled = request.data
        self.get_logger().info(f"Focus state: {self.tracking_enabled}")

        if self.cli_enable_continuous.service_is_ready():
            req         = SetBool.Request()
            req.data    = request.data
            future      = self.cli_enable_continuous.call_async(req)
            future.add_done_callback(self._vision_service_done_callback)
            response.success = True
            response.message = f"Focus propagated: {request.data}"
        else:
            self.get_logger().warn("Vision continuous service not available.")
            response.success = False
            response.message = "Vision service not ready."

        return response

    def _vision_service_done_callback(self, future):
        try:
            res = future.result()
            self.get_logger().debug(f"Vision service OK: {res.message}")
        except Exception as e:
            self.get_logger().error(f"Vision service failed: {e}")

    # Callback nube de puntos
    def pc_callback(self, msg):
        if not self.enable_active:
            return
        self.latest_pc = msg

    # Callback YOLO 
    def yolo_callback(self, msg):
    
        if not self.enable_active:
            return

        detections = [d for d in msg.detections
                      if d.class_name == "person" and d.score >= MIN_CONFIDENCE]

        for t in self.tracks:
            t.predict()

        if detections:
            det_positions   = []
            det_descriptors = []

            for d in detections:
                cx = (d.box.x_min + d.box.x_max) / 2.0
                cy = (d.box.y_min + d.box.y_max) / 2.0
                w  =  d.box.x_max - d.box.x_min
                h  =  d.box.y_max - d.box.y_min
                det_positions.append(np.array([cx, cy]))
                # Descriptor enriquecido: w, h, score, aspect ratio
                aspect = w / (h + 1e-6)
                det_descriptors.append(np.array([w, h, d.score, aspect]))

            if not self.tracks:
                for pos, desc in zip(det_positions, det_descriptors):
                    self.tracks.append(Track(self.next_id, pos, desc))
                    self.next_id += 1
            else:
                cost_matrix = np.zeros((len(self.tracks), len(det_positions)))
                for i, t in enumerate(self.tracks):
                    for j, d_pos in enumerate(det_positions):
                        dist      = np.sum((t.pos - d_pos) ** 2)
                        desc_dist = np.sum((t.desc - det_descriptors[j]) ** 2) * 50.0
                        cost_matrix[i, j] = dist + desc_dist

                row_ind, col_ind = linear_sum_assignment(cost_matrix)
                assigned_tracks  = set()
                assigned_dets    = set()

                for r, c in zip(row_ind, col_ind):
                    if cost_matrix[r, c] < MATCH_THRESHOLD:
                        self.tracks[r].update(det_positions[c], det_descriptors[c])
                        assigned_tracks.add(r)
                        assigned_dets.add(c)

                for j, d_pos in enumerate(det_positions):
                    if j not in assigned_dets:
                        self.tracks.append(Track(self.next_id, d_pos, det_descriptors[j]))
                        self.next_id += 1

        self.tracks = [t for t in self.tracks if t.age < MAX_LOST_FRAMES]
        confirmed   = [t for t in self.tracks if t.is_confirmed]

        if not confirmed:
            self.target_track_id = None
            self._publish_diagnostics(0, 0.0)
            return

        # Selección / reenganche de target
        if self.target_track_id is not None:
            target = next((t for t in confirmed if t.id == self.target_track_id), None)
            if target is None:
        
                if self.last_target_pos is not None:
                    dists  = [np.linalg.norm(t.pos - self.last_target_pos) for t in confirmed]
                    min_i  = int(np.argmin(dists))
                    if dists[min_i] < REATTACH_RADIUS:
                        target = confirmed[min_i]
                        self.get_logger().info(
                            f"Target reattached → track {target.id} "
                            f"(dist={dists[min_i]:.2f}px)")
                    else:
                        confirmed.sort(key=lambda t: abs(t.pos[0] - 320))
                        target = confirmed[0]
                else:
                    confirmed.sort(key=lambda t: abs(t.pos[0] - 320))
                    target = confirmed[0]
                self.target_track_id = target.id
        else:
            confirmed.sort(key=lambda t: abs(t.pos[0] - 320))
            target = confirmed[0]
            self.target_track_id = target.id

        # Guardar ultima posicion del target para reenganche
        self.last_target_pos = target.pos.copy()

        if target is not None and self.latest_pc is not None:
            p_stamped = self.extract_3d_point(target.pos, msg.header.stamp)
            if p_stamped is not None:
                self.publish_targets(p_stamped, target.id)

        conf = min(1.0, target.hits / 10.0) if target else 0.0
        self._publish_diagnostics(len(confirmed), conf)

        self._publish_all_markers(confirmed, target.id)

    def extract_3d_point(self, pos_2d, stamp):
        try:
            pc  = self.latest_pc
            px  = int(clamp(pos_2d[0], 0, pc.width  - 1))
            py  = int(clamp(pos_2d[1], 0, pc.height - 1))

            offset   = py * pc.row_step + px * pc.point_step
            data_xyz = pc.data[offset: offset + 12]
            if len(data_xyz) < 12:
                return None

            x, y, z = struct.unpack_from('fff', data_xyz)

            if np.isnan(x) or np.isnan(y) or np.isnan(z) or z <= 0.1:
                # Ventana de búsqueda ampliada con mediana
                window = 15
                x_list, y_list, z_list = [], [], []
                for dy in range(-window // 2, window // 2 + 1):
                    for dx in range(-window // 2, window // 2 + 1):
                        nx = int(clamp(px + dx, 0, pc.width  - 1))
                        ny = int(clamp(py + dy, 0, pc.height - 1))
                        no = ny * pc.row_step + nx * pc.point_step
                        d  = pc.data[no: no + 12]
                        if len(d) == 12:
                            xi, yi, zi = struct.unpack_from('fff', d)
                            if not np.isnan(xi) and not np.isnan(zi) and zi > 0.1:
                                x_list.append(xi)
                                y_list.append(yi)
                                z_list.append(zi)
                if z_list:
                    x = float(np.median(x_list))
                    y = float(np.median(y_list))
                    z = float(np.median(z_list))
                else:
                    return None

            p = PointStamped()
            p.header.frame_id = pc.header.frame_id
            p.header.stamp    = stamp
            p.point.x = float(x)
            p.point.y = float(y)
            p.point.z = float(z)
            return p

        except Exception as e:
            self.get_logger().error(f"Error extracting 3D point: {e}")
            return None

    # Publicar target y look_at
    def publish_targets(self, p, tid):
        try:
            trans   = self.tf_buffer.lookup_transform(
                "base_link", p.header.frame_id, rclpy.time.Time())
            p_base  = tf2_geometry_msgs.do_transform_point(p, trans)
            self.pub_target.publish(p_base)
            if self.tracking_enabled:
                self.pub_look_at.publish(p_base)
        except Exception as e:
            self.get_logger().warn(f"Transform error: {e}")

    def _publish_all_markers(self, confirmed_tracks, target_id):
        ma = MarkerArray()

        # Limpiar markers anteriores
        clear = Marker()
        clear.action = Marker.DELETEALL
        ma.markers.append(clear)

        for t in confirmed_tracks:
            is_target = (t.id == target_id)
            m = Marker()
            m.header.frame_id = "base_link"
            m.header.stamp    = self.get_clock().now().to_msg()
            m.ns              = "persons"
            m.id              = t.id
            m.type            = Marker.CYLINDER
            m.action          = Marker.ADD
            m.scale.x = m.scale.y = 0.35
            m.scale.z = 0.2
            m.pose.position.z = 0.1
            if is_target:
                m.color.r, m.color.g, m.color.b, m.color.a = 1.0, 0.3, 0.0, 0.8
            else:
                m.color.r, m.color.g, m.color.b, m.color.a = 0.3, 0.3, 1.0, 0.5
            ma.markers.append(m)

            # Label
            lbl = Marker()
            lbl.header    = m.header
            lbl.ns        = "person_labels"
            lbl.id        = t.id
            lbl.type      = Marker.TEXT_VIEW_FACING
            lbl.text      = f"{'TARGET' if is_target else 'track'} #{t.id}"
            lbl.scale.z   = 0.2
            lbl.color.r   = lbl.color.g = lbl.color.b = lbl.color.a = 1.0
            ma.markers.append(lbl)

        self.pub_markers.publish(ma)

    # Diagnost
    def _publish_diagnostics(self, num_tracks: int, confidence: float):
        n_msg      = Int32();   n_msg.data = num_tracks
        c_msg      = Float32(); c_msg.data = float(confidence)
        self.pub_num_tracks.publish(n_msg)
        self.pub_confidence.publish(c_msg)


def clamp(n, minn, maxn):
    return max(min(n, maxn), minn)


def main(args=None):
    rclpy.init(args=args)
    node = PersonTracker()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()