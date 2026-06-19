#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, PointCloud2, CameraInfo
from cv_bridge import CvBridge
from geometry_msgs.msg import TransformStamped, PointStamped
import cv2
import numpy as np
import tf2_ros
import struct
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from human_interfaces.srv import DetectPointing
from .yolo_model import YoloDetector
import tf2_geometry_msgs 

CONF = 0.3
UMBRAL_DIST = 40
UMBRAL_EXT = 30

class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')

        self.bridge = CvBridge()
        self.detector = YoloDetector()

        # Broadcaster TF dinámico y Buffer
        self.tf_broadcaster = tf2_ros.TransformBroadcaster(self)
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)

        # Variables
        self.latest_frame = None
        self.last_cloud = None
        self.frame_id = None
        self.camera_info = None  
        self.customer_tf = None

        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        self.declare_parameter("image_topic", "/kinect/image_raw")
        self.declare_parameter("pointcloud_topic", "/kinect/points")
        self.declare_parameter("camera_info_topic", "/kinect/camera_info")

        self.image_topic = self.get_parameter("image_topic").get_parameter_value().string_value
        self.pointcloud_topic = self.get_parameter("pointcloud_topic").get_parameter_value().string_value
        self.camera_info_topic = self.get_parameter("camera_info_topic").get_parameter_value().string_value

        # Subscripciones
        self.image_sub = self.create_subscription(Image, self.image_topic, self.image_callback, 10)
        self.pcd_sub = self.create_subscription(PointCloud2, self.pointcloud_topic, self.pcd_callback, qos_profile)
        self.camera_info_sub = self.create_subscription(CameraInfo, self.camera_info_topic, self._camera_info_callback, 10)
        
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image_wrist', 10)
        
        # Servicio actualizado
        self.create_service(DetectPointing, '/human_detection/detect_wrist', self.handle_service)
        self.get_logger().info("[VISION NODE] Nodo listo. Esperando peticiones...")
        self.tf_timer = self.create_timer(0.1, self.rpub_customer_tf)

    def _camera_info_callback(self, msg):
        self.camera_info = {'fx': msg.k[0], 'fy': msg.k[4], 'cx': msg.k[2], 'cy': msg.k[5]}
        self.destroy_subscription(self.camera_info_sub)
        self.get_logger().info(f"[VISION NODE] CameraInfo recibido: fx={msg.k[0]:.1f} fy={msg.k[4]:.1f}")

    def image_callback(self, msg):
        if self.frame_id is None:
            self.frame_id = msg.header.frame_id
        self.latest_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

    def pcd_callback(self, msg):
        self.last_cloud = msg

    # kp[5]=L_Shoulder, kp[6]=R_Shoulder, kp[7]=L_Elbow, kp[8]=R_Elbow, kp[9]=L_Wrist, kp[10]=R_Wrist

    def is_waving(self, kp, side="any"):
        l_up = kp[9][1] < kp[5][1] if (kp[9][2] > 0.3 and kp[5][2] > 0.3) else False
        r_up = kp[10][1] < kp[6][1] if (kp[10][2] > 0.3 and kp[6][2] > 0.3) else False
        
        if side == "left" and l_up: return "left", 9
        if side == "right" and r_up: return "right", 10
        if side == "any" or side == "":
            if l_up: return "left", 9
            if r_up: return "right", 10
        return None, None

    def is_raising(self, kp, side="any"):
        l_raise = (kp[9][1] < kp[7][1] < kp[5][1]) if (kp[9][2] > 0.3 and kp[7][2] > 0.3 and kp[5][2] > 0.3) else False
        r_raise = (kp[10][1] < kp[8][1] < kp[6][1]) if (kp[10][2] > 0.3 and kp[8][2] > 0.3 and kp[6][2] > 0.3) else False

        if side == "left" and l_raise: return "left", 9
        if side == "right" and r_raise: return "right", 10
        if side == "any" or side == "":
            if l_raise: return "left", 9
            if r_raise: return "right", 10
        return None, None

    def is_pointing(self, kp, side="any"):

        if kp[9][2] > CONF and kp[5][2] > CONF:
            dx_l = abs(kp[9][0] - kp[5][0])
            dy_l = kp[9][1] - kp[5][1]      
            extended_l = dx_l > UMBRAL_DIST 

            #l_up   = extended_l and dy_l < -UMBRAL_EXT 
            l_ext  = extended_l and abs(dy_l) <= UMBRAL_EXT 
            l_down = extended_l and dy_l > UMBRAL_EXT    
        else:
            #l_up = l_ext = l_down = False
            l_ext = l_down = False

        if kp[10][2] > CONF and kp[6][2] > CONF:
            dx_r = abs(kp[10][0] - kp[6][0])
            dy_r = kp[10][1] - kp[6][1]
            extended_r = dx_r > UMBRAL_DIST

            #r_up   = extended_r and dy_r < -UMBRAL_EXT
            r_ext  = extended_r and abs(dy_r) <= UMBRAL_EXT
            r_down = extended_r and dy_r > UMBRAL_EXT
        else:
            #r_up = r_ext = r_down = False
            r_ext = r_down = False

        if side == "left":
            #if l_up:   return "left_up",   9
            if l_ext:  return "left_ext",  9
            if l_down: return "left_down", 9

        elif side == "right":
            #if r_up:   return "right_up",   10
            if r_ext:  return "right_ext",  10
            if r_down: return "right_down", 10

        else: 
            #if l_up:   return "left_up",   9
            if l_ext:  return "left_ext",  9
            if l_down: return "left_down", 9
            #if r_up:   return "right_up",   10
            if r_ext:  return "right_ext",  10
            if r_down: return "right_down", 10

        return None, None

    def handle_service(self, request, response):
        response.human_detected = False
        response.direction = "none"
        response.point = PointStamped()

        if self.latest_frame is None or self.last_cloud is None:
            self.get_logger().warn("Sensores no listos (RGB/PCD)")
            return response

        # Leer argumentos del request
        action = request.action_type.lower().strip()
        side = request.arm_side.lower().strip() if request.arm_side else "any"

        frame = self.latest_frame.copy()
        detections = self.detector.infer(frame)
        
        target_person = None
        detected_side = None
        wrist_kp_idx = None

        for det in detections:
            kp = det['keypoints']
            
            # Filtrar según la acción solicitada
            if action == "wave" or action == "waving":
                detected_side, wrist_kp_idx = self.is_waving(kp, side)
            elif action == "raising" or action == "raise":
                detected_side, wrist_kp_idx = self.is_raising(kp, side)
            elif action == "pointing" or action == "point":
                detected_side, wrist_kp_idx = self.is_pointing(kp, side)
            else:
                self.get_logger().error(f"Acción '{action}' no soportada.")
                return response

            if detected_side is not None:
                target_person = det
                break # Encontró la primera persona que cumple la condición

        if target_person:
            kp = target_person['keypoints']
            
            # muñeca objetivo
            tgt_x = int(kp[wrist_kp_idx][0])
            tgt_y = int(kp[wrist_kp_idx][1])
            
            # centro de la persona entre ambos hombros
            sh_l_x, sh_l_y = kp[5][0], kp[5][1]
            sh_r_x, sh_r_y = kp[6][0], kp[6][1]
            
            pecho_x = int((sh_l_x + sh_r_x) / 2)
            pecho_y = int((sh_l_y + sh_r_y) / 2)
            
            p3d_pecho = self.get_3d_point(pecho_x, pecho_y)
            if p3d_pecho is None:
                p3d_pecho = self._project_to_floor(pecho_x, pecho_y)

            if p3d_pecho is not None:
                response.human_detected = True

                p_cam = PointStamped()
                p_cam.header.stamp = self.last_cloud.header.stamp
                p_cam.header.frame_id = self.frame_id

                p_cam.point.x = float(p3d_pecho[0])
                p_cam.point.y = float(p3d_pecho[1])
                p_cam.point.z = float(p3d_pecho[2])

                transform = self.tf_buffer.lookup_transform(
                    "base_link",
                    p_cam.header.frame_id,
                    rclpy.time.Time(),
                    rclpy.duration.Duration(seconds=0.1),
                )

                p_base = tf2_geometry_msgs.do_transform_point(p_cam, transform)

                # Devolver SIEMPRE el punto en base_link
                response.point = p_base

                horiz = "center"
                if pecho_x < 213: horiz = "left"
                elif pecho_x > 426: horiz = "right"
                
                dist_stat = "ideal" if 1.2 < p3d_pecho[2] < 2.8 else "reposition"
                
                response.direction = f"{action}_{detected_side}_{horiz}_{dist_stat}"
                clean_name = response.direction.replace(" ", "_")
                
                self.get_logger().info(f"Gesto detectado. Calculando aproximación al pecho: {response.direction}")

                self.publish_human_tf(p3d_pecho, clean_name, self.last_cloud.header.stamp)

            cv2.circle(frame, (tgt_x, tgt_y), 15, (0, 255, 0), -1) # Muñeca
            cv2.circle(frame, (pecho_x, pecho_y), 15, (255, 0, 0), -1) # Pecho
            cv2.line(frame, (pecho_x, pecho_y), (tgt_x, tgt_y), (255, 255, 0), 2)
            cv2.putText(frame, f"{action} (Torso)", (pecho_x - 40, pecho_y - 20), 
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)
            
            debug_img = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            self.human_pose_image_pub.publish(debug_img)

        return response

    def get_3d_point(self, u, v):
        if self.last_cloud is None: return None
        width, height = self.last_cloud.width, self.last_cloud.height
        point_step, row_step = self.last_cloud.point_step, self.last_cloud.row_step

        def fetch_single_point(curr_u, curr_v):
            if not (0 <= curr_u < width and 0 <= curr_v < height): return None
            offset = (int(curr_v) * row_step) + (int(curr_u) * point_step)
            try:
                data = self.last_cloud.data[offset : offset + 12]
                x, y, z = struct.unpack('fff', data)
                if np.isfinite(z) and z > 0.1: return (x, y, z)
            except struct.error: return None
            return None
        points = []
        for i in range(-1, 2):
            for j in range(-1, 2):
                p = fetch_single_point(u + i, v + j)
                if p: points.append(p)
        
        if not points: return None
        return np.mean(points, axis=0)

    def _project_to_floor(self, u, v):
        """
        Proyecta el rayo cámara->pixel hasta el plano Z=0 en base_link de forma segura.
        """
        if self.camera_info is None or self.last_cloud is None:
            return None
        try:
            ci = self.camera_info
            cam_frame = self.last_cloud.header.frame_id

            ray_x = (u - ci['cx']) / ci['fx']
            ray_y = (v - ci['cy']) / ci['fy']
            ray_z = 1.0

            tf_cam_to_base = self.tf_buffer.lookup_transform(
                'base_link', cam_frame,
                rclpy.time.Time(), rclpy.duration.Duration(seconds=0.2))

            origin_cam = PointStamped()
            origin_cam.header.frame_id = cam_frame
            origin_cam.point.x, origin_cam.point.y, origin_cam.point.z = 0.0, 0.0, 0.0
            origin_base = tf2_geometry_msgs.do_transform_point(origin_cam, tf_cam_to_base)

            ray_point_cam = PointStamped()
            ray_point_cam.header.frame_id = cam_frame
            ray_point_cam.point.x, ray_point_cam.point.y, ray_point_cam.point.z = ray_x, ray_y, ray_z
            ray_point_base = tf2_geometry_msgs.do_transform_point(ray_point_cam, tf_cam_to_base)
            vec_x = ray_point_base.point.x - origin_base.point.x
            vec_y = ray_point_base.point.y - origin_base.point.y
            vec_z = ray_point_base.point.z - origin_base.point.z

            if abs(vec_z) < 1e-6:
                return None  # El rayo es paralelo al suelo

            t = -origin_base.point.z / vec_z
            if t < 0:
                return None  # La intersección queda detrás de la cámara

            p_base_x = origin_base.point.x + t * vec_x
            p_base_y = origin_base.point.y + t * vec_y
            p_base_z = 0.0  # Forzado en el suelo de base_link
            p_base_stamped = PointStamped()
            p_base_stamped.header.frame_id = 'base_link'
            p_base_stamped.header.stamp = rclpy.time.Time().to_msg()
            p_base_stamped.point.x, p_base_stamped.point.y, p_base_stamped.point.z = p_base_x, p_base_y, p_base_z

            tf_base_to_cam = self.tf_buffer.lookup_transform(
                cam_frame, 'base_link',
                rclpy.time.Time(), rclpy.duration.Duration(seconds=0.2))
            
            p_cam = tf2_geometry_msgs.do_transform_point(p_base_stamped, tf_base_to_cam)

            return np.array([p_cam.point.x, p_cam.point.y, p_cam.point.z])

        except Exception as e:
            self.get_logger().warn(f"[VISION NODE] Fallback proyección fallido: {e}")
            return None

    def publish_human_tf(self, p3d, name, stamp):
        try:
            p_cam = PointStamped()
            p_cam.header.stamp = stamp
            p_cam.header.frame_id = self.last_cloud.header.frame_id
            p_cam.point.x, p_cam.point.y, p_cam.point.z = map(float, p3d)

            transform = self.tf_buffer.lookup_transform('base_link', p_cam.header.frame_id, rclpy.time.Time(), rclpy.duration.Duration(seconds=0.1))
            p_base = tf2_geometry_msgs.do_transform_point(p_cam, transform)

            dist = np.sqrt(p_base.point.x**2 + p_base.point.y**2)
            offset = 0.7
            if dist > offset:
                ratio = (dist - offset) / dist
                f_x, f_y = p_base.point.x * ratio, p_base.point.y * ratio
            else:
                f_x, f_y = p_base.point.x, p_base.point.y

            t = TransformStamped()
            t.header.stamp = stamp
            t.header.frame_id = 'base_link'
            t.child_frame_id = name
            t.transform.translation.x = float(f_x)
            t.transform.translation.y = float(f_y)
            t.transform.translation.z = 0.0
            t.transform.rotation.w = 1.0

            self.customer_tf = t
            self.tf_broadcaster.sendTransform(t)
        except Exception as e:
            self.get_logger().error(f"Error en publish_human_tf: {e}")

    def rpub_customer_tf(self):
        if self.customer_tf is not None:
            try:
                # Sync stamp with the latest map→base_link transform so that
                # lookup_transform('map','customer',Time(0)) finds both hops
                # at the exact same timestamp — no extrapolation needed.
                tf_mb = self.tf_buffer.lookup_transform(
                    'map', 'base_link', rclpy.time.Time())
                self.customer_tf.header.stamp = tf_mb.header.stamp
            except Exception:
                self.customer_tf.header.stamp = self.get_clock().now().to_msg()
            self.tf_broadcaster.sendTransform(self.customer_tf)

def main(args=None):
    rclpy.init(args=args)
    node = HumanDetectorNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
