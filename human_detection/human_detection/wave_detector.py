#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, PointCloud2
from std_msgs.msg import Bool
from cv_bridge import CvBridge
from geometry_msgs.msg import TransformStamped
import cv2
import numpy as np
import tf2_ros
import struct
import sensor_msgs_py.point_cloud2 as pc2
from human_interfaces.srv import DetectPointing
from .yolo_model import YoloDetector

SKELETON = [(5, 7), (7, 9), (6, 8), (8, 10), (5, 6), (0, 5), (0, 6)]

class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')
        # Inicialización del modelo de detección
        self.bridge = CvBridge()
        self.detector = YoloDetector()
        self.tf_broadcaster = tf2_ros.TransformBroadcaster(self) 
        self.latest_frame = None
        self.latest_pcd = None
        #suscripciones
        self.image_sub = self.create_subscription(Image, '/kinect/image_raw', self.image_callback, 10)
        self.pcd_sub = self.create_subscription(PointCloud2, '/kinect/points', self.pcd_callback, 10)
        #publicadores
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image_wrist', 10)
        #servicios
        self.create_service(DetectPointing, '/human_detection/detect_wrist', self.handle_service)
        
        self.get_logger().info("NODE READY: /human_detection/detect_wrist and /human_detection/pose_image_wrist(debug)")

    def image_callback(self, msg):
        self.latest_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

    def pcd_callback(self, msg):
        self.latest_pcd = msg

    def get_3d_point(self, u, v):
        if self.latest_pcd is None: return None
        
        # Parámetros de la nube de puntos
        width = self.latest_pcd.width
        height = self.latest_pcd.height
        point_step = self.latest_pcd.point_step # Cuántos bytes mide cada punto (ej. 32)
        row_step = self.latest_pcd.row_step     # Cuántos bytes mide cada fila

        def fetch_point(curr_u, curr_v):
            if not (0 <= curr_u < width and 0 <= curr_v < height):
                return None
            offset = (int(curr_v) * row_step) + (int(curr_u) * point_step)
            
            try:
                x_data = self.latest_pcd.data[offset : offset + 4]
                y_data = self.latest_pcd.data[offset + 4 : offset + 8]
                z_data = self.latest_pcd.data[offset + 8 : offset + 12]

                x_val = struct.unpack('f', x_data)[0]
                y_val = struct.unpack('f', y_data)[0]
                z_val = struct.unpack('f', z_data)[0]
                
                if np.isfinite(z_val) and z_val > 0.1:
                    return (x_val, y_val, z_val)
            except:
                return None
            return None

        valid_pts = []
        for i in range(-5, 6, 2):
            for j in range(-5, 6, 2):
                pt = fetch_point(u + i, v + j)
                if pt: valid_pts.append(pt)

        if valid_pts:
            avg_x = np.mean([p[0] for p in valid_pts])
            avg_y = np.mean([p[1] for p in valid_pts])
            valid_z = [p[2] for p in valid_pts]
            return (avg_x, avg_y, np.median(valid_z))

        return None

    def publish_hand_tf(self, p3d, side):
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = self.latest_pcd.header.frame_id
        t.child_frame_id = f'detected_hand_{side}'
        t.transform.translation.x = float(p3d[0])
        t.transform.translation.y = float(p3d[1])
        t.transform.translation.z = float(p3d[2])
        t.transform.rotation.w = 1.0
        self.tf_broadcaster.sendTransform(t)

    def handle_service(self, request, response):
        if self.latest_frame is None or self.latest_pcd is None:
            self.get_logger().error("No image or point cloud data available")
            response.human_detected = False
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

        if best_person is None:
            self.get_logger().info("don't detect any person with raised hand")
            response.human_detected = False
            return response

        response.human_detected = True
        kp = best_person['keypoints']
        
        # Punto medio del torso (píxeles)
        mid_x = int((kp[5][0] + kp[6][0]) / 2)
        mid_y = int((kp[5][1] + kp[6][1]) / 2)
        
        center_p3d = self.get_3d_point(mid_x, mid_y)
        if center_p3d is None:
            center_p3d = self.get_3d_point(kp[5][0], kp[5][1])

        if center_p3d:
            horiz = "left" if mid_x < 213 else "right" if mid_x > 426 else "center"
            dist_val = float(center_p3d[2])
            status = "too_close" if dist_val < 1.0 else "far" if dist_val > 2.5 else "ideal"

            self.publish_human_tf(center_p3d, horiz, status)
            
            self.publish_human_tf(center_p3d, "center")
            self.get_logger().info(f"Detección: {response.direction} a {response.z:.2f}m")
        else:
            response.z = 1.0
            response.direction = "human_unknown_no_depth"
            self.get_logger().error("No depth data for detected human, defaulting to 1.0m and unknown direction")

        # Dibujar círculo de estado (Azul)
        cv2.circle(frame, (mid_x, mid_y), 20, (255, 0, 0), -1)
        self.human_pose_image_pub.publish(self.bridge.cv2_to_imgmsg(frame, 'bgr8'))
        
        from sensor_msgs.msg import Image as ROSImage
        response.pose_image = ROSImage()
        return response
    
    def publish_human_tf(self, p3d, horiz, status):
        t = TransformStamped()
        # Usamos el tiempo actual de ROS 2
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = self.latest_pcd.header.frame_id
        t.child_frame_id = f'human in {horiz}_{status}'
        
        t.transform.translation.x = float(p3d[0])
        t.transform.translation.y = float(p3d[1])
        t.transform.translation.z = float(p3d[2])
        
        t.transform.rotation.x = 0.0
        t.transform.rotation.y = 0.0
        t.transform.rotation.z = 0.0
        t.transform.rotation.w = 1.0
        self.tf_broadcaster.sendTransform(t)
        self.get_logger().info(f"Published TF for detected human at x: {p3d[0]:.2f}, y: {p3d[1]:.2f}, z: {p3d[2]:.2f} '{horiz}_{status}'")
    
def main(args=None):
    rclpy.init(args=args)
    node = HumanDetectorNode()
    try: rclpy.spin(node)
    except: pass
    finally: rclpy.shutdown()

if __name__ == '__main__': main()