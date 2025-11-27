import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import Bool, Header
from human_interfaces.msg import PersonTracks, PersonTrack
from cv_bridge import CvBridge
import cv2
import numpy as np

# from .models.movenet import MoveNetDetector

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

        # Parámetros
        self.declare_parameter('model_type', 'yolo')
        self.model_type = self.get_parameter('model_type').get_parameter_value().string_value

        # Inicializar el detector basado en el modelo seleccionado
        if self.model_type == 'yolo':
            self.detector = YoloDetector()
            self.get_logger().info('Usando YOLO como modelo de detección.')
        else:
            self.get_logger().error(f'Modelo desconocido: {self.model_type}')
            rclpy.shutdown()
            return

        # CvBridge para convertir imágenes ROS a OpenCV
        self.bridge = CvBridge()

        # Suscriptor a la cámara
        self.camera_sub = self.create_subscription(
            Image,
            '/camera/rgb/image_raw',
            self.image_callback,
            10
        )

        # Publicador de detección de humanos
        self.human_detection_pub = self.create_publisher(Bool, '/human_detection/human_detected', 10)
        self.human_keypoints_pub = self.create_publisher(PersonTracks, '/human_detection/keypoints', 10)
        self.human_pose_image_pub = self.create_publisher(Image, '/human_detection/pose_image', 10)

    def image_callback(self, msg):
        # Convertir la imagen ROS a OpenCV
        frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

        # Realizar la detección
        detections = self.detector.infer(frame)

        # Publicar si se detectó un humano
        human_detected = Bool()
        human_detected.data = len(detections) > 0
        frame = draw_pose(frame, detections[0]['keypoints']) if len(detections) > 0 else None
        
        self.human_detection_pub.publish(human_detected)

        # Publicar los keypoints del humano detectado (si hay alguno)
        self.publish_keypoints(detections)

        self.human_pose_image_pub.publish(
            self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')) if frame is not None else None
        

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
            kp = det["keypoints"]   # np.array shape (17,3)
            score = det["score"]

            # Aplanar keypoints
            flat_kp = kp.reshape(-1).astype(np.float32).tolist()

            person = PersonTrack()
            person.id = -1  # aún no tiene ID, el tracker lo asigna
            person.keypoints = flat_kp
            person.confidence = float(score)
            person.stamp = msg.header.stamp

            msg.persons.append(person)

        # Publicar
        self.human_keypoints_pub.publish(msg)


    def destroy_node(self):
        # Liberar recursos si es necesario
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