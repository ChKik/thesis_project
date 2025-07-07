import numpy as np
from PIL import Image
import os


# 1. Load and process image
img = Image.open("image.jpeg").resize((224, 224))
img_array = np.array(img)
print("Image shape:", img_array.shape)  # Should output (224, 224, 3)

# 2 Normalize and quantize (if model is quantized)
img_array = (img_array / 255.0).astype(np.float32)  # Normalize to [0, 1] (float32)
img_quantized = (img_array).astype(np.uint8)   # Quantize to 8-bit (uint8)
print("After quant image shape:", img_quantized)

img_quantized.tofile("assets")

#Den eimai sigouros ama einai swsto giati mporei na min xreiazetai quantification sto input.