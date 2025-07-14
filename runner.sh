#!/usr/bin/env bash
set -e  # Stop on errors

echo "Changing directory to thesis_project"
cd ~/thesis_project

echo "Starting decoding of image into raw bytes."
gcc scripts/raw_buffer_image_decoder.c \
    scripts/raw_buffer_creation.c \
    scripts/main.c \
    -o scripts/decode_image_binary -ljpeg

./scripts/decode_image_binary


echo "Creating the header file with xxd"
xxd -i -n image_buffer image_buffer.bin > src/image_buffer.h #vazw kai custom onoma sto image_buffer.


echo "Removing image_buffer.bin from thesis_project"
rm image_buffer.bin



echo "Starting up virtual env and setting zephyr_base"
source ~/zephyrproject/zephyr/zephyr-env.sh         #$ZEPHYR_BASE SETUP
source ~/zephyrproject/.venv/bin/activate    #virtual environment setup.

#Include to tflite module sto build.
west config manifest.project-filter -- +tflite-micro
west update


echo "Starting building process for EK_RA8D1 board"
west build -b ek_ra8d1 -p

echo "Starting flashing process"
west flash
