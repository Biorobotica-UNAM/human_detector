#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Bool, Header
from cv_bridge import CvBridge
import cv2
import numpy as np
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

def estimate_pointing_target_2d(elbow, wrist, frame_height):
    x0, y0, _ = elbow
    x1, y1, _ = wrist
    dx = x1 - x0
    dy = y1 - y0
    if abs(dy) < 1e-6:
        dy = 1e-6
    t = (frame_height - y0) / dy
    x_target = x0 + t * dx
    y_target = frame_height
    return int(x_target), int(y_target)

def draw_pointing_arrow(frame, elbow, wrist):
    h = frame.shape[0]
    target = estimate_pointing_target_2d(elbow, wrist, h)
    cv2.arrowedLine(frame, (int(wrist[0]), int(wrist[1])), target, (255,0,0), 2, tipLength=0.2)
    cv2.circle(frame, target, 6, (255,0,0), -1)
    return target


class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')

        self.latest_frame = None
        self.filtered_target = None

        self.declare_parameter('model_type', 'yolo')
        self.model_type = self.get_parameter('model_type').get_parameter_value().string_value

        if self.model_type == 'yolo':
            self.detector = YoloDetector()
            self.get_logger().info('Usando YOLO como modelo de detección.')
        else:
            self.get_logger().error(f'Modelo desconocido: {self.model_type}')
            rclpy.shutdown()
            return

        self.bridge = CvBridge()

        self.camera_sub = self.create_subscription(
            Image,
            '/kinect/image_raw', #/kinect/image_raw---/camera/rgb/image_raw
            self.image_callback,
            10
        )

        # Publicador de detección de humanos
        self.human_detection_pub = self.create_publisher(Bool, '/human_detection/human_detected', 10)
        #self.human_keypoints_pub = self.create_publisher(PersonTracks, '/human_detection/keypoints', 10)
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image', 10)

        self.create_service(DetectPointing, '/human_detection/detect_and_point', self.handle_service)
        self.get_logger().info("Nodo listo: /human_detection/detect_and_point y publicación de pose.")    

    def image_callback(self, msg):
        # save image
        self.latest_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        frame = self.latest_frame.copy()

        # detección
        detections = self.detector.infer(frame)

        human_detected = Bool()
        human_detected.data = len(detections) > 0
        self.human_detection_pub.publish(human_detected)

        if len(detections) > 0:
            frame = draw_pose(frame, detections[0]['keypoints'])
        
        #image
        self.human_pose_image_pub.publish(
            self.bridge.cv2_to_imgmsg(frame, 'bgr8')
        )

        
    def handle_service(self, request, response):

        if self.latest_frame is None:
            response.human_detected = False
            response.target_x = int(-1)
            response.target_y = int(-1)
            response.target_z = float(0.10)
            response.direction = "unknown"
            return response

        frame = self.latest_frame.copy()
        detections = self.detector.infer(frame)

        response.human_detected = len(detections) > 0

        if len(detections) == 0:
            response.direction = "unknown"
            response.target_x = int(-1)
            response.target_y = int(-1)
            response.target_z = float(0.10)
            response.pose_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            return response

        keypoints = detections[0]['keypoints']
        left_pts  = [keypoints[5], keypoints[7], keypoints[9]]
        right_pts = [keypoints[6], keypoints[8], keypoints[10]]

        left_valid  = all(p[2] > 0.3 for p in left_pts)
        right_valid = all(p[2] > 0.3 for p in right_pts)

        if not left_valid and not right_valid:
            response.direction = "unknown"
            response.target_x = int(-1)
            response.target_y = int(-1)
            response.target_z = float(0.10)
            response.pose_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            return response

        def dist(p0, p1):
            return np.linalg.norm(np.array(p0[:2]) - np.array(p1[:2]))

        left_dist  = dist(left_pts[1], left_pts[2]) if left_valid else 0
        right_dist = dist(right_pts[1], right_pts[2]) if right_valid else 0

        if left_dist > right_dist:
            pts = left_pts
            response.direction = "left"
        else:
            pts = right_pts
            response.direction = "right"

  
        pts_xy = np.array([(x, y) for (x, y, c) in pts], dtype=np.float32)
        xs = pts_xy[:, 0]
        ys = pts_xy[:, 1]

        if np.std(xs) < 1e-3:
            x_target = int(xs.mean())
        else:
            m, b = np.polyfit(xs, ys, 1)
            y_target = frame.shape[0]
            x_target = int((y_target - b) / m)

        y_target = frame.shape[0]
        alpha = 0.25
        target_raw = np.array([x_target, y_target], dtype=float)

        if self.filtered_target is None:
            self.filtered_target = target_raw
        else:
            self.filtered_target = alpha * target_raw + (1 - alpha) * self.filtered_target

        x_final = int(self.filtered_target[0])
        y_final = int(self.filtered_target[1])

        #response
        response.target_x = int(x_final)
        response.target_y = int(y_final)
        response.target_z = float(0.20)

        frame = draw_pose(frame, keypoints)
        cv2.circle(frame, (x_final, y_final), 8, (0, 0, 255), -1)
        response.pose_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')

        return response


    def destroy_node(self):
        try:
            self.detector.destroy()
        except:
            pass
        super().destroy_node()


def draw_pose(frame, keypoints):

    for (p0, p1) in SKELETON:
        x0, y0, c0 = keypoints[p0]
        x1, y1, c1 = keypoints[p1]

        if c0 > 0.3 and c1 > 0.3:  # confiance
            cv2.line(
                frame,
                (int(x0), int(y0)),
                (int(x1), int(y1)),
                (0, 255, 0),
                2
            )

    for (x, y, c) in keypoints:
        if c > 0.3:
            cv2.circle(
                frame,
                (int(x), int(y)),
                3,
                (0, 0, 255),
                -1
            )

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
        # rclpy.shutdown()

if __name__ == '__main__':
    main()