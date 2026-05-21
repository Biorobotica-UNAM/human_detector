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

class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')
        self.bridge = CvBridge()
        self.detector = YoloDetector()
        # Se mantiene como StaticTransformBroadcaster por tu requerimiento
        self.tf_broadcaster = tf2_ros.StaticTransformBroadcaster(self) 
        
        # Buffer necesario para transformar la posición al suelo (base_link)
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)

        self.latest_frame = None
        self.last_cloud = None
        self.frame_id = None
        self.camera_info = None  # Se llena una sola vez desde el topic

        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        self.declare_parameter("image_topic", "/kinect/image_raw") #/head_rgbd_sensor/rgb/image_rect_color
        self.declare_parameter("pointcloud_topic", "/kinect/points") #/hardware/camera/points
        self.declare_parameter("camera_info_topic", "/kinect/camera_info")

        self.image_topic = self.get_parameter("image_topic").get_parameter_value().string_value
        self.pointcloud_topic = self.get_parameter("pointcloud_topic").get_parameter_value().string_value
        self.camera_info_topic = self.get_parameter("camera_info_topic").get_parameter_value().string_value

        # Suscripciones
        self.image_sub = self.create_subscription(
            Image, self.image_topic, self.image_callback, 10)
        self.pcd_sub = self.create_subscription(
            PointCloud2, self.pointcloud_topic, self.pcd_callback, qos_profile)
        # Se destruye sola tras recibir el primer mensaje (intrínsecos no cambian)
        self.camera_info_sub = self.create_subscription(
            CameraInfo, self.camera_info_topic, self._camera_info_callback, 10)
        
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image_wrist', 10)
        
        self.create_service(DetectPointing, '/human_detection/detect_wrist', self.handle_service)
        self.get_logger().info("[VISION NODE] Nodo listo. Esperando llamada del servicio...")

    def _camera_info_callback(self, msg):
        """Guarda los intrínsecos una sola vez y se da de baja."""
        self.camera_info = {'fx': msg.k[0], 'fy': msg.k[4], 'cx': msg.k[2], 'cy': msg.k[5]}
        self.destroy_subscription(self.camera_info_sub)
        self.get_logger().info(f"[VISION NODE] CameraInfo recibido: fx={msg.k[0]:.1f} fy={msg.k[4]:.1f}")

    def _project_to_floor(self, u, v):
        """
        Fallback: proyecta el rayo cámara->pixel hasta el plano Z=0 en base_link.
        Devuelve (x, y, z) en el frame de la cámara, igual que get_3d_point,
        para que el resto del pipeline no cambie nada.
        Retorna None si no hay CameraInfo o si la transformada falla.
        """
        if self.camera_info is None or self.last_cloud is None:
            return None
        try:
            ci = self.camera_info
            # Dirección del rayo en frame cámara (Z=1 normalizado)
            ray = np.array([(u - ci['cx']) / ci['fx'],
                            (v - ci['cy']) / ci['fy'],
                            1.0])

            cam_frame = self.last_cloud.header.frame_id
            tf = self.tf_buffer.lookup_transform(
                'base_link', cam_frame,
                rclpy.time.Time(), rclpy.duration.Duration(seconds=0.2))

            # Rotación cámara -> base_link
            q = tf.transform.rotation
            R = np.array([
                [1-2*(q.y**2+q.z**2),   2*(q.x*q.y-q.z*q.w), 2*(q.x*q.z+q.y*q.w)],
                [2*(q.x*q.y+q.z*q.w),   1-2*(q.x**2+q.z**2), 2*(q.y*q.z-q.x*q.w)],
                [2*(q.x*q.z-q.y*q.w),   2*(q.y*q.z+q.x*q.w), 1-2*(q.x**2+q.y**2)]
            ])
            origin = np.array([tf.transform.translation.x,
                               tf.transform.translation.y,
                               tf.transform.translation.z])

            ray_base = R @ ray
            if abs(ray_base[2]) < 1e-6:
                return None  # Rayo paralelo al suelo

            # Intersección con plano Z=0 (suelo en base_link)
            t = -origin[2] / ray_base[2]
            if t < 0:
                return None
            p_base = origin + t * ray_base

            # Convertimos de vuelta al frame de cámara para no romper el pipeline
            p_base_stamped = PointStamped()
            p_base_stamped.header.frame_id = 'base_link'
            p_base_stamped.header.stamp = rclpy.time.Time().to_msg()
            p_base_stamped.point.x, p_base_stamped.point.y, p_base_stamped.point.z = \
                float(p_base[0]), float(p_base[1]), 0.0

            tf_inv = self.tf_buffer.lookup_transform(
                cam_frame, 'base_link',
                rclpy.time.Time(), rclpy.duration.Duration(seconds=0.2))
            p_cam = tf2_geometry_msgs.do_transform_point(p_base_stamped, tf_inv)

            return np.array([p_cam.point.x, p_cam.point.y, p_cam.point.z])

        except Exception as e:
            self.get_logger().warn(f"[VISION NODE] Fallback proyección fallido: {e}")
            return None

    def image_callback(self, msg):
        if self.frame_id is None:
            self.frame_id = msg.header.frame_id
        self.latest_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

    def pcd_callback(self, msg):
        self.last_cloud = msg

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

    def handle_service(self, request, response):
        response.human_detected = False
        response.direction = "none"
        #response.pose_image = Image()

        response.point = PointStamped()

        if self.latest_frame is None or self.last_cloud is None:
            self.get_logger().warn("Sensores no listos (RGB/PCD)")
            return response

        frame = self.latest_frame.copy()
        detections = self.detector.infer(frame)
        best_person = None

        for det in detections:
            kp = det['keypoints']
            l_up = kp[9][1] < kp[5][1] if kp[9][2] > 0.3 else False
            r_up = kp[10][1] < kp[6][1] if kp[10][2] > 0.3 else False
            if l_up or r_up:
                best_person = det
                break

        if best_person:
            kp = best_person['keypoints']
            mid_x = int((kp[5][0] + kp[6][0]) / 2)
            mid_y = int((kp[5][1] + kp[6][1]) / 2)
            p3d = self.get_3d_point(mid_x, mid_y) or self._project_to_floor(mid_x, mid_y)  # <-- fallback

            if p3d is not None:
                response.human_detected = True
                response.point.header.stamp = self.last_cloud.header.stamp
                response.point.header.frame_id = self.frame_id
                response.point.point.x = float(p3d[0])
                response.point.point.y = float(p3d[1])
                response.point.point.z = float(p3d[2])
            
                
                horiz = "center"
                if mid_x < 213: horiz = "left"
                elif mid_x > 426: horiz = "right"
                
                dist_stat = "ideal" if 1.2 < p3d[2] < 2.8 else "reposition"
                response.direction = f"{horiz}_{dist_stat}"
                clean_name = response.direction.replace(" ", "_")
                self.get_logger().info(f"Detección: {response.direction} in position X={p3d[0]:.2f}, Y={p3d[1]:.2f}, Z={p3d[2]:.2f}")
                self.publish_human_tf(p3d, clean_name, self.last_cloud.header.stamp)
                
            
            cv2.circle(frame, (mid_x, mid_y), 20, (0, 255, 0), -1)
            debug_img = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            self.human_pose_image_pub.publish(debug_img)

        return response
    
    def publish_human_tf(self, p3d, name, stamp):
        try:
            # Creamos el punto en el frame de la cámara
            p_cam = PointStamped()
            p_cam.header.stamp = stamp
            p_cam.header.frame_id = self.last_cloud.header.frame_id
            p_cam.point.x, p_cam.point.y, p_cam.point.z = map(float, p3d)

            # Transformamos a base_link para obtener coordenadas respecto al suelo del robot
            transform = self.tf_buffer.lookup_transform('base_link', p_cam.header.frame_id, rclpy.time.Time(), rclpy.duration.Duration(seconds=0.1))
            p_base = tf2_geometry_msgs.do_transform_point(p_cam, transform)

            # Cálculo de offset de 0.5m
            dist = np.sqrt(p_base.point.x**2 + p_base.point.y**2)
            offset = 0.7
            if dist > offset:
                ratio = (dist - offset) / dist
                f_x, f_y = p_base.point.x * ratio, p_base.point.y * ratio
            else:
                f_x, f_y = p_base.point.x, p_base.point.y

            # Publicamos la TF estática referenciada a base_link
            t = TransformStamped()
            t.header.stamp = self.get_clock().now().to_msg()
            t.header.frame_id = 'base_link'
            t.child_frame_id = 'customer'
            
            t.transform.translation.x = float(f_x)
            t.transform.translation.y = float(f_y)
            t.transform.translation.z = 0.0 # <--- Forzado al suelo
            t.transform.rotation.w = 1.0
            
            self.tf_broadcaster.sendTransform(t)
        except Exception as e:
            self.get_logger().error(f"Error en publish_human_tf: {e}")

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