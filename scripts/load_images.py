import glob
from random import randrange
import shutil
import os

NUM_CLASSES=20
FIRST_IMG_NUM=901
LAST_IMG_NUM=1200
input_dir="/home/haris/dataset/hand_gesture_dataset_resized/test"
output_dir="/home/haris/thesis_project/images_source"

patterns_saved= set() #no duplicates allowed in the set, so could be faster for bigger dataset.

os.makedirs(output_dir, exist_ok=True) #checks if dir exists firstly

count = 0
while count < 4:  # we want 4 unique images but I make sure that an image is not repeated.
    selected_class = randrange(0, NUM_CLASSES)
    selected_file = randrange(FIRST_IMG_NUM, LAST_IMG_NUM + 1)

    pattern = os.path.join(input_dir, str(selected_class), f"{selected_file}.jpg")

    if pattern in patterns_saved:
        continue  #  #We do a repetition of this procedure because the image selected is the same as ebfore

    image_match = glob.glob(pattern)
    if image_match:
        src = image_match[0]
        dst = os.path.join(output_dir, f"class{selected_class}_{selected_file}.jpg")
        shutil.copyfile(src, dst)
        patterns_saved.add(pattern)  #save the results in a set to ensure that we have no duplicates
        count += 1
        print(f"Copied {src} -> {dst}")
    else:
        print(f"Image not found: {pattern}")
        break

