#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from human_interfaces.srv import DetectPointing
from cv_bridge import CvBridge
import cv2
import os

class HumanDetectionClient(Node):
    def __init__(self):
        super().__init__('human_detection_client')
        self.cli = self.create_client(DetectPointing, '/human_detection/detect_and_point')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Esperando al servicio de detección...')
        self.req = DetectPointing.Request()
        self.bridge = CvBridge()

    def send_request(self):
        future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, future)
        if future.result() is not None:
            res = future.result()
            if res.human_detected:
                self.get_logger().info('Human detected: True')
                self.get_logger().info(f'Target x: {res.target_x}')
                self.get_logger().info(f'Target y: {res.target_y}')
                self.get_logger().info(f'Direction: {res.direction}')

                cv_image = self.bridge.imgmsg_to_cv2(res.pose_image, desired_encoding='bgr8')
                cv2.imwrite(os.path.expanduser('~/human.png'), cv_image)
                self.get_logger().info('save image')
            else:
                self.get_logger().info('Human detected: False')
        else:
            self.get_logger().error('Fallo al llamar el servicio')

def main(args=None):
    rclpy.init(args=args)
    node = HumanDetectionClient()
    node.send_request()
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
