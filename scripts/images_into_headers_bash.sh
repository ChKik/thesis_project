#!/bin/bash

# Directory containing images
IMAGE_DIR=~/thesis_project/images
# Output directory for header files
OUTPUT_DIR=~/thesis_project/image_headers

# Create output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"

# Loop through each file in the image directory
for f in "$IMAGE_DIR"/*
do
    echo "Processing $f..."

    # Extract the base filename (without extension)
    BASENAME=$(basename "$f")
    NAME="${BASENAME%.*}"

    # Output .h file path
    HEADER_FILE="$OUTPUT_DIR/$NAME.h"

    # Create .h file from binary using xxd
    xxd -i -n "$NAME" "$f" > "$HEADER_FILE"

    echo "Created header file: $HEADER_FILE"
done

echo "All images converted to header files successfully."
