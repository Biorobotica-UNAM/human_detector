#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, PointCloud2
from cv_bridge import CvBridge
from geometry_msgs.msg import TransformStamped, PointStamped
import cv2
import numpy as np
import tf2_ros
import struct
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
from human_interfaces.srv import DetectPointing
from .yolo_model import YoloDetector

class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')
        self.bridge = CvBridge()
        self.detector = YoloDetector()
        self.tf_broadcaster = tf2_ros.StaticTransformBroadcaster(self) 
        
        self.latest_frame = None
        self.last_cloud = None
        self.frame_id = None

        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        self.declare_parameter("image_topic", "/kinect/image_raw") #/head_rgbd_sensor/rgb/image_rect_color
        self.declare_parameter("pointcloud_topic", "/kinect/points") #/hardware/camera/points

        self.image_topic = self.get_parameter("image_topic").get_parameter_value().string_value
        self.pointcloud_topic = self.get_parameter("pointcloud_topic").get_parameter_value().string_value

        # Suscripciones
        self.image_sub = self.create_subscription(
            Image, self.image_topic, self.image_callback, 10)
        self.pcd_sub = self.create_subscription(
            PointCloud2, self.pointcloud_topic, self.pcd_callback, qos_profile)
        
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image_wrist', 10)
        
        self.create_service(DetectPointing, '/human_detection/detect_wrist', self.handle_service)
        self.get_logger().info("[VISION NODE] Nodo listo. Esperando llamada del servicio...")

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
            except: return None
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
            p3d = self.get_3d_point(mid_x, mid_y)

            if p3d is not None:
                response.human_detected = True
                response.point.header.stamp = self.last_cloud.header.stamp
                response.point.header.frame_id = self.frame_id
                response.point.point.x = float(p3d[0])
                response.point.point.y = float(p3d[1])
                response.point.point.z = float(p3d[2])
                response.point.header.frame_id = self.frame_id
            
                
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
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.stamp = stamp 
        t.header.frame_id = self.last_cloud.header.frame_id
        t.child_frame_id = f'costumer'
        
        t.transform.translation.x = float(p3d[0])
        t.transform.translation.y = float(p3d[1])
        t.transform.translation.z = float(p3d[2])
        t.transform.rotation.w = 1.0
        
        self.tf_broadcaster.sendTransform(t)

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