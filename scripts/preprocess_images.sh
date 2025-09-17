#!/usr/bin/env bash
set -e  # Stop on errors

echo "Loading the images"
python3 scripts/load_images.py

echo "Necessary preprocessing for the creation of the image header files."
python3 scripts/image_preprocessing.py \
    --input-dir /home/haris/thesis_project/images_source \
    --out-bin-dir /home/haris/thesis_project/image_bin \
    --out-src-dir /home/haris/thesis_project/images_directory \
    --size 224 224

echo "Loading all the header files into a single header"
python3 scripts/all_headers_script.py

echo "Preprocessing done"