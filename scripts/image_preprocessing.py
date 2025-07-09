from PIL import Image
import os, os.path
import numpy as np

resize_width=224
resize_height=224


input_dir = '/home/haris/thesis_project/images/'
output_dir='/home/haris/thesis_project/image_processed/'

# Loop over each image in the directory and output the 224x224 in the image_processed file.
for x in range(1, len(os.listdir(input_dir)) + 1):
    image_path = os.path.join(input_dir, f"{x}.jpg")
    
    if os.path.exists(image_path):
        with Image.open(image_path) as img:
            img = img.resize((resize_width, resize_height), Image.LANCZOS)
            print(f"Resized image at: {image_path}")
            
            #Quantification image process. If it a jpeg its already in uint8 format ranging from 0-255
            img_array = np.array(img)
            if img_array.dtype != np.uint8:
                img_array = (img_array * 255).astype(np.uint8)
            quantified_image = Image.fromarray(img_array)

            # Save in different file for the processed image , in image_processed.
            base_name = os.path.splitext(f"{x}.jpg")[0]
            save_path = os.path.join(output_dir, f"{base_name}_resized.jpg")
            quantified_image.save(save_path, format='JPEG')
    else:
        print(f"Image {image_path} not found.")