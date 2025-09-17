import os

"""
Creates all_images.h and all_images.cc that aggregate all image headers.
Also generates forward declarations for each image array and its length.
"""

# Source path
images_dir = "./images_directory"

# Output files
all_h_path = os.path.join(images_dir, "all_images.h")
all_cc_path = os.path.join(images_dir, "all_images.cc")

# Collect all image headers (assuming *_image.h)
image_headers = sorted(
    [f for f in os.listdir(images_dir) if f.endswith("_image.h")]
)

# Derive variable names (strip ".h")
image_vars = [h.replace(".h", "") for h in image_headers]

# Generate all_images.h
with open(all_h_path, "w") as f_h:
    f_h.write("#pragma once\n\n")

    # Include each header
    for header in image_headers:
        f_h.write(f'#include "{header}"\n')
    f_h.write("\n")

    # Forward declarations
    for var in image_vars:
        f_h.write(f"extern const unsigned char {var}[];\n")
        f_h.write(f"extern const unsigned int {var}_len;\n\n")

    # Struct and extern declarations
    f_h.write("struct ImageBuffer {\n")
    f_h.write("    const unsigned char* data;\n")
    f_h.write("    const unsigned int length;\n")
    f_h.write("};\n\n")
    f_h.write("extern const ImageBuffer all_images[];\n")
    f_h.write("extern const unsigned int num_images;\n")

# Generate all_images.cc
with open(all_cc_path, "w") as f_cc:
    f_cc.write('#include "all_images.h"\n\n')
    f_cc.write("const ImageBuffer all_images[] = {\n")
    for var in image_vars:
        f_cc.write(f"    {{{var}, {var}_len}},\n")
    f_cc.write("};\n\n")
    f_cc.write("const unsigned int num_images = sizeof(all_images)/sizeof(all_images[0]);\n")

print(f"Generated {all_h_path} and {all_cc_path} with {len(image_headers)} images.")
