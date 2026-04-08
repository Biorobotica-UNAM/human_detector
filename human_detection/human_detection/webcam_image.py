import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
from builtin_interfaces.msg import Time


class WebcamImageNode(Node):
    def __init__(self):
        super().__init__('webcam_image_node')

        self.declare_parameter("camera_index", 0)
        self.declare_parameter("width", 640)
        self.declare_parameter("height", 480)
        self.declare_parameter("fps", 30)
        self.declare_parameter("frame_id", '')
        self.declare_parameter("topic_name", "/camera/rgb/image_raw")

        self.bridge = CvBridge()

        # Leer parámetros
        self.camera_index = self.get_parameter("camera_index").value
        self.width = self.get_parameter("width").value
        self.height = self.get_parameter("height").value
        self.fps = self.get_parameter("fps").value
        self.frame_id = self.get_parameter("frame_id").value
        self.topic_name = self.get_parameter("topic_name").value

        self.get_logger().info(f"Iniciando cámara en /dev/video{self.camera_index}")

        # Publicador
        self.camera_pub = self.create_publisher(Image, self.topic_name, 10)

        # Inicializa la cámara
        self.cap = None
        self.open_camera()

        # Timer
        period = 1.0 / float(self.fps)
        self.timer = self.create_timer(period, self.timer_callback)

    # ----------------------------------------------------------------------
    # Abrir cámara con V4L2 backend
    # ----------------------------------------------------------------------
    def open_camera(self):
        self.cap = cv2.VideoCapture(self.camera_index, cv2.CAP_V4L2)

        if not self.cap.isOpened():
            self.get_logger().error(f"No se pudo abrir /dev/video{self.camera_index}")
            return

        # Set cámara config
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, self.width)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, self.height)
        self.cap.set(cv2.CAP_PROP_FPS, self.fps)

        # Confirmación
        w = self.cap.get(cv2.CAP_PROP_FRAME_WIDTH)
        h = self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
        f = self.cap.get(cv2.CAP_PROP_FPS)

        self.get_logger().info(f"Cámara abierta: {w}x{h} @ {f} FPS")

    # ----------------------------------------------------------------------
    # Timer
    # ----------------------------------------------------------------------
    def timer_callback(self):
        if self.cap is None or not self.cap.isOpened():
            self.get_logger().warn("Cámara desconectada, intentando reconectar...")
            self.open_camera()
            return

        ret, frame = self.cap.read()
        if not ret:
            self.get_logger().warn("Error al leer frame, reintentando...")
            return

        # Convertir la imagen
        try:
            msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
        except Exception as e:
            self.get_logger().error(f"Error en cv_bridge: {e}")
            return

        # time stamp exacto
        now = self.get_clock().now().to_msg()
        msg.header.stamp = now
        msg.header.frame_id = self.frame_id

        # Publicar
        self.camera_pub.publish(msg)

    # ----------------------------------------------------------------------
    # Destructor
    # ----------------------------------------------------------------------
    def destroy_node(self):
        if self.cap is not None:
            self.cap.release()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = WebcamImageNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        # rclpy.shutdown()


if __name__ == '__main__':
    main()
