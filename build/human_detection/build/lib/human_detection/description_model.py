#!/usr/bin/env python3
from transformers import AutoProcessor, AutoModelForVision2Seq
import torch
import cv2

class DescripModel:
    def __init__(self):
        self.model_id = "Qwen/Qwen2-VL-2B-Instruct"

        print("Loading Qwen2-VL model... (first time will download ~4GB)")

        self.processor = AutoProcessor.from_pretrained(self.model_id)

        self.model = AutoModelForVision2Seq.from_pretrained(
            self.model_id,
            torch_dtype=torch.float16,
            device_map="auto"
        ).eval()

    def describe(self, cv_img, prompt="Describe the image"):
        # OpenCV BGR -> RGB
        img_rgb = cv2.cvtColor(cv_img, cv2.COLOR_BGR2RGB)

        messages = [
            {
                "role": "user",
                "content": [
                    {"type": "image"},
                    {"type": "text", "text": prompt}
                ]
            }
        ]

        inputs = self.processor.apply_chat_template(
            messages,
            add_generation_prompt=True,
            return_tensors="pt"
        ).to(self.model.device)

        inputs["pixel_values"] = self.processor(
            images=img_rgb,
            return_tensors="pt"
        ).pixel_values.to(self.model.device)

        with torch.no_grad():
            output = self.model.generate(
                **inputs,
                max_new_tokens=120,
                do_sample=False
            )

        result = self.processor.decode(output[0], skip_special_tokens=True)
        return result



