#!/usr/bin/env python3
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, PointCloud2
from std_msgs.msg import Bool
from geometry_msgs.msg import TransformStamped
from cv_bridge import CvBridge
import cv2
import numpy as np
import tf2_ros
import message_filters
import sensor_msgs_py.point_cloud2 as pc2

from human_interfaces.srv import DetectPointing
from .yolo_model import YoloDetector

SKELETON = [
    (5, 7), (7, 9),     # left arm
    (6, 8), (8, 10),    # right arm
    (11, 13), (13, 15), # left leg
    (12, 14), (14, 16), # right leg
    (5, 6),             # shoulders
    (11, 12),           # hips
    (5, 11),            # left torso diagonal
    (6, 12),            # right torso diagonal
    (0, 5), (0, 6)      # head → shoulders
]

class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')

        self.latest_frame = None
        self.latest_pcd = None
        self.bridge = CvBridge()
        self.detector = YoloDetector()
        self.tf_broadcaster = tf2_ros.TransformBroadcaster(self)
        self.image_sub = message_filters.Subscriber(self, Image, '/kinect/image_raw')
        self.pcd_sub = message_filters.Subscriber(self, PointCloud2, '/kinect/points')
        
        self.ts = message_filters.ApproximateTimeSynchronizer(
            [self.image_sub, self.pcd_sub], queue_size=10, slop=0.1
        )
        self.ts.registerCallback(self.sync_callback)
        self.human_detection_pub = self.create_publisher(Bool, '/human_detection/human_detected_wirst', 10)
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image_wirst', 10)
        self.create_service(DetectPointing, '/human_detection/detect_wirst', self.handle_service)
        self.get_logger().info("Nodo de detección de saludo y TF 3D listo.")

    def sync_callback(self, img_msg, pcd_msg):
        self.latest_frame = self.bridge.imgmsg_to_cv2(img_msg, desired_encoding='bgr8')
        self.latest_pcd = pcd_msg
        
        # Publicación continua de detección básica
        detections = self.detector.infer(self.latest_frame)
        msg = Bool()
        msg.data = len(detections) > 0
        self.human_detection_pub.publish(msg)

    def get_3d_point(self, u, v):
        if self.latest_pcd is None:
            return None
        
        try:
            points = list(pc2.read_points(
                self.latest_pcd, 
                field_names=("x", "y", "z"), 
                skip_nans=True, 
                uvs=[[int(u), int(v)]]
            ))
            return points[0] if len(points) > 0 else None
        except Exception as e:
            self.get_logger().error(f"Error al leer PointCloud: {e}")
            return None

    def publish_hand_tf(self, coords_3d, side):
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = self.latest_pcd.header.frame_id # Usualmente 'kinect_optical_frame'
        t.child_frame_id = f'detected_hand_{side}'

        t.transform.translation.x = float(coords_3d[0])
        t.transform.translation.y = float(coords_3d[1])
        t.transform.translation.z = float(coords_3d[2])
        t.transform.rotation.w = 1.0 # Sin rotación específica
        
        self.tf_broadcaster.sendTransform(t)

    def handle_service(self, request, response):
        if self.latest_frame is None or self.latest_pcd is None:
            response.human_detected = False
            return response

        frame = self.latest_frame.copy()
        detections = self.detector.infer(frame)
        response.human_detected = len(detections) > 0

        if not response.human_detected:
            return response

        keypoints = detections[0]['keypoints']
        
        # Índices: 5=L_Shoulder, 9=L_Wrist | 6=R_Shoulder, 10=R_Wrist
        l_wrist, r_wrist = keypoints[9], keypoints[10]
        l_shldr, r_shldr = keypoints[5], keypoints[6]

        is_left_up = l_wrist[2] > 0.4 and l_wrist[1] < l_shldr[1]
        is_right_up = r_wrist[2] > 0.4 and r_wrist[1] < r_shldr[1]

        target_kp = None
        side = "unknown"

        if is_left_up or is_right_up:
            if l_wrist[1] < r_wrist[1]:
                target_kp, side = l_wrist, "left"
            else:
                target_kp, side = r_wrist, "right"

        if target_kp is not None:
            coords_3d = self.get_3d_point(target_kp[0], target_kp[1])
            
            if coords_3d:
                self.publish_hand_tf(coords_3d, side)
                response.target_x = int(target_kp[0])
                response.target_y = int(target_kp[1])
                response.target_z = float(coords_3d[2])
                response.direction = f"greeting_{side}"
                cv2.circle(frame, (int(target_kp[0]), int(target_kp[1])), 15, (0, 255, 255), -1)
                cv2.putText(frame, f"SALUDO {side.upper()}", (int(target_kp[0]), int(target_kp[1]-20)),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 255), 2)

        frame = draw_pose(frame, keypoints)
        response.pose_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
        self.human_pose_image_pub.publish(response.pose_image)
        
        return response

    def destroy_node(self):
        try: self.detector.destroy()
        except: pass
        super().destroy_node()

def draw_pose(frame, keypoints):
    for (p0, p1) in SKELETON:
        x0, y0, c0 = keypoints[p0]
        x1, y1, c1 = keypoints[p1]
        if c0 > 0.3 and c1 > 0.3:
            cv2.line(frame, (int(x0), int(y0)), (int(x1), int(y1)), (0, 255, 0), 2)
    for (x, y, c) in keypoints:
        if c > 0.3:
            cv2.circle(frame, (int(x), int(y)), 3, (0, 0, 255), -1)
    return frame

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