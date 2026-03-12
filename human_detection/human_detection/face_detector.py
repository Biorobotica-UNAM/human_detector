#!/usr/bin/env python3
import cv2
import numpy as np
import insightface

class FaceDetector:
    def __init__(self, expand_scale=1.4, use_gpu=True):
        self.expand_scale = expand_scale
        
        # Cargar el detector RetinaFace
        self.face_app = insightface.app.FaceAnalysis(
            name="buffalo_l" 
        )
        
        #ctx_id = 0 => GPU, ctx_id = -1 => CPU
        ctx_id = 0 if use_gpu else -1
        self.face_app.prepare(ctx_id=ctx_id)

    def _expand_bbox(self, x1, y1, x2, y2, img_width, img_height):
        # Bounding box original
        w = x2 - x1
        h = y2 - y1

        # Centro
        cx = x1 + w // 2
        cy = y1 + h // 2

        # Nuevo tamaño
        new_w = int(w * self.expand_scale)
        new_h = int(h * self.expand_scale)

        # Nueva esquina superior izquierda
        new_x1 = max(0, cx - new_w // 2)
        new_y1 = max(0, cy - new_h // 2)

        # Nueva esquina inferior derecha
        new_x2 = min(img_width, new_x1 + new_w)
        new_y2 = min(img_height, new_y1 + new_h)

        return new_x1, new_y1, new_x2, new_y2

    def detect_face(self, image):
        # RetinaFace usa RGB
        img_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

        # Detectar rostros
        faces = self.face_app.get(img_rgb)

        if len(faces) == 0:
            return None

        # Tomar el rostro más grande
        best = max(faces, key=lambda f: (f.bbox[2] - f.bbox[0]) * (f.bbox[3] - f.bbox[1]))

        x1, y1, x2, y2 = best.bbox.astype(int)

        # Expandir bounding box
        img_h, img_w = image.shape[:2]
        ex1, ey1, ex2, ey2 = self._expand_bbox(x1, y1, x2, y2, img_w, img_h)

        # Recorte ampliado
        expanded_face = image[ey1:ey2, ex1:ex2]

        return expanded_face
