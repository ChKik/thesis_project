#!/usr/bin/env bash
set -e  # Stop on errors

echo "Changing directory to thesis_project"
cd ~/thesis_project

echo "Removing previous images from directory"
rm -rf /home/haris/thesis_project/images_directory/*
rm -rf /home/haris/thesis_project/images_source/*
rm -rf /home/haris/thesis_project/image_bin/*

echo "Loading and processing images and finally creating the header files."
bash /home/haris/thesis_project/scripts/preprocess_images.sh

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
