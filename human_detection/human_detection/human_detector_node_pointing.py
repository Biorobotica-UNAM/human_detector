#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Bool, Header
from cv_bridge import CvBridge
import cv2
import numpy as np
from human_interfaces.srv import DetectPointing
#from human_interfaces.msg import PersonTracks, PersonTrack
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

"""def draw_pose(frame, keypoints):
    for (p0, p1) in SKELETON:
        x0, y0, c0 = keypoints[p0]
        x1, y1, c1 = keypoints[p1]
        if c0 > 0.3 and c1 > 0.3:
            cv2.line(frame, (int(x0), int(y0)), (int(x1), int(y1)), (0,255,0), 2)
    for (x, y, c) in keypoints:
        if c > 0.3:
            cv2.circle(frame, (int(x), int(y)), 3, (0,0,255), -1)
    return frame"""

class HumanDetectorNode(Node):
    def __init__(self):
        super().__init__('human_detector_node')

        self.latest_frame = None

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

    """def image_callback(self, msg):
        # Convertir la imagen ROS a OpenCV
        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        #frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        # Realizar la detección
        detections = self.detector.infer(frame)

        # Publicar si se detectó un humano
        human_detected = Bool()
        human_detected.data = len(detections) > 0
        
        frame = draw_pose(frame, detections[0]['keypoints']) if len(detections) > 0 else None
        
        self.human_detection_pub.publish(human_detected)

        # Publicar los keypoints del humano detectado (si hay alguno)
        #self.publish_keypoints(detections)

        self.human_pose_image_pub.publish(
            self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')) #if frame is not None else None"""
    def image_callback(self, msg):
        # Guardar la imagen para el servicio
        self.latest_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        frame = self.latest_frame.copy()

        # Realizar la detección
        detections = self.detector.infer(frame)

        # Publicar detección de humano
        human_detected = Bool()
        human_detected.data = len(detections) > 0
        self.human_detection_pub.publish(human_detected)

        # Dibujar pose si hay detecciones
        if len(detections) > 0:
            frame = draw_pose(frame, detections[0]['keypoints'])
        
        # Publicar imagen con pose
        self.human_pose_image_pub.publish(
            self.bridge.cv2_to_imgmsg(frame, 'bgr8')
        )

        
    def handle_service(self, request, response):
        if self.latest_frame is None:
            response.human_detected = False
            response.target_x = -1
            response.target_y = -1
            response.pose_image = None
            response.target_z = 0.10
            response.direction = "unknown"
            return response

        frame = self.latest_frame.copy()
        detections = self.detector.infer(frame)
        response.human_detected = len(detections) > 0

        if len(detections) == 0:
            response.target_x = -1
            response.target_y = -1
            response.target_z = 0.10
            response.direction = "unknown"
            response.pose_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            return response

        keypoints = detections[0]['keypoints']

        left_elbow = keypoints[7]
        left_wrist = keypoints[9]
        right_elbow = keypoints[8]
        right_wrist = keypoints[10]

        # Calcular la distancia
        left_active = np.linalg.norm(np.array(left_wrist[:2]) - np.array(left_elbow[:2]))
        right_active = np.linalg.norm(np.array(right_wrist[:2]) - np.array(right_elbow[:2]))

        if left_active > right_active:
            elbow, wrist = left_elbow, left_wrist
            response.direction = "left"
        else:
            elbow, wrist = right_elbow, right_wrist
            response.direction = "right"

        # Calcular coordenadas
        frame_height = frame.shape[0]
        target_x, target_y = estimate_pointing_target_2d(elbow, wrist, frame_height)
        target_z = 0.20 
        response.target_x = target_x
        response.target_y = target_y
        response.target_z = target_z

        frame = draw_pose(frame, keypoints)
        cv2.circle(frame, (target_x, target_y), 8, (0, 0, 255), -1)

        response.pose_image = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
        return response

        

    def publish_keypoints(self, detections):
        """
        detections: lista de dicts con:
            "keypoints": np.array shape (17,3)
            "box": [...], (opcional)
            "score": float
        """

        msg = PersonTracks()
        msg.header = Header()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "camera_link"

        for det in detections:
            kp = det["keypoints"] 
            score = det["score"]

            flat_kp = kp.reshape(-1).astype(np.float32).tolist()

            person = PersonTrack()
            person.id = -1 
            person.keypoints = flat_kp
            person.confidence = float(score)
            person.stamp = msg.header.stamp

            msg.persons.append(person)

        self.human_keypoints_pub.publish(msg)


    def destroy_node(self):
        self.detector.destroy()
        super().destroy_node()


def draw_pose(frame, keypoints):
    # keypoints shape: (17, 3)

    for (p0, p1) in SKELETON:
        x0, y0, c0 = keypoints[p0]
        x1, y1, c1 = keypoints[p1]

        if c0 > 0.3 and c1 > 0.3:  # confianza mínima
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