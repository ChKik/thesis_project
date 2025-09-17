#!/usr/bin/env bash
set -e  # Stop on errors


python3 image_preprocessing.py \
    --input-dir /home/haris/thesis_project/images_source \
    --out-bin-dir /home/haris/thesis_project/image_bin \
    --out-src-dir /home/haris/thesis_project/images_directory \
    --size 224 224

echo "Preprocessing done"