#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from human_interfaces.srv import SaveLastFace
import cv2
import os
import time
import re
from human_detection.face_detector import FaceDetector


class FaceService(Node):
    def __init__(self):
        super().__init__('face_service')

        self.bridge = CvBridge()
        self.detector = FaceDetector()

        self.subscription = self.create_subscription(
            Image,
            '/kinect/image_raw',
            self.image_callback,
            10
        )

        self.last_frame = None

        self.srv = self.create_service(
            SaveLastFace,
            'save_last_face',
            self.save_callback
        )
        
        self.save_dir = os.path.expanduser("~/faces")
        os.makedirs(self.save_dir, exist_ok=True)

        self.get_logger().info("Service 'save_last_face' Ready.")

    def image_callback(self, msg):
        try:
            self.last_frame = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"frame error {e}")

    def save_callback(self, request, response):
        if self.last_frame is None:
            response.success = False
            response.message = "No frame received"
            return response

        frame = self.last_frame.copy()

        face = self.detector.detect_face(frame)

        if face is None:
            response.success = False
            response.message = "Don't detect face"
            return response
        
        existing_names = []

        for file in os.listdir(self.save_dir):
            match = re.match(r"(.+)_\d+\.jpg", file)
            if match:
                existing_names.append(match.group(1))
        
        print("\n--- Detect Face ---")
        name = input("WHAT IS YOUR NAME?: ").strip()

        if name == "":
            response.success = False
            response.message = "Empty name, cancelled."
            return response

        if name in existing_names:
            print(f"\n its'{name}' your name?")
            resp = input(" (s = sí / n = no): ").strip().lower()

            if resp != 's':
                # Pedir nuevo nombre
                new_name = input("okey, What is your name?: ").strip()
                if new_name != "":
                    name = new_name
                else:
                    response.success = False
                    response.message = "new name is empty, cancelled."
                    return response

    

        # Guardar imagen
        timestamp = int(time.time())
        filename = f"{name}_{timestamp}.jpg"
        filepath = os.path.join(self.save_dir, filename)

        cv2.imwrite(filepath, face)

        response.success = True
        response.message = f"Face saved in: {filepath}"
        return response


def main(args=None):
    rclpy.init(args=args)
    node = FaceService()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
