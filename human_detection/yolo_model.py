import torch
import cv2
import numpy as np
import os
from ament_index_python.packages import get_package_share_directory

from ultralytics import YOLO

class YoloDetector:

    def __init__(self, model_path="yolo11x-pose.pt", conf_th=0.4, iou_th=0.5):
        """
        YOLO Pose detector (YOLO11s-pose).
        - model_path: archivo del modelo .pt
        - conf_th: umbral de confianza
        - iou_th: umbral de IoU para NMS
        """

        self.device = "cuda" if torch.cuda.is_available() else "cpu"

        # Cargar modelo
        package_path = get_package_share_directory('human_detection')
        model_path = os.path.join(package_path, 'models', model_path)

        self.model = YOLO(model_path)
        self.model.fuse()  # optimización para inferencia

        self.conf = conf_th
        self.iou = iou_th

        print(f"[YoloDetector] Loaded YOLO pose model on {self.device}")

    def infer(self, frame):
        """
        Corre YOLO y regresa una lista de detecciones:
        [
            {
                "box": [x1, y1, x2, y2],
                "score": float,
                "keypoints": np.array shape (17,3)
            },
            ...
        ]
        """

        results = self.model(
            frame,
            conf=self.conf,
            iou=self.iou,
            verbose=False,
            device=self.device
        )

        detections = []

        # Procesar los resultados
        for r in results:
            if r.boxes is None or len(r.boxes) == 0:
                continue

            boxes = r.boxes.xyxy.cpu().numpy()
            scores = r.boxes.conf.cpu().numpy()

            # Keypoints: shape (N, 17, 3)
            if r.keypoints is not None:
                kpts = r.keypoints.data.cpu().numpy()
            else:
                kpts = None

            for i in range(len(boxes)):
                box = boxes[i].astype(int).tolist()
                score = float(scores[i])
                kp = kpts[i] if kpts is not None else None

                detections.append({
                    "box": box,             # [x1, y1, x2, y2]
                    "score": score,
                    "keypoints": kp         # shape (17,3)
                })
            
            detections.sort(key=lambda x: x["score"], reverse=True)

        return detections
    
    def destroy(self):
        """
        Libera recursos del modelo
        """
        del self.model
        torch.cuda.empty_cache()
        print("[YoloDetector] Model resources released")