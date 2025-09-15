import os
"""
Creates a cpp struct that will contain all the header files and cc files so that only one file needs to be included in main.cc to have access to everything.
It allows for a random selection of an image class instead of being declared statically in main.cc
"""


# Sourcde path
images_dir = "./images_directory"

# Output files
all_h_path = os.path.join(images_dir, "all_images.h")
all_cc_path = os.path.join(images_dir, "all_images.cc")

# Collect all image header names (assuming they end with _image.h)
image_headers = sorted(
    [f for f in os.listdir(images_dir) if f.endswith("_image.h")]
)

# Generate all_images.h and include all individual headers
with open(all_h_path, "w") as f_h:
    f_h.write("#pragma once\n\n")

    for header in image_headers:
        f_h.write(f'#include "{header}"\n')
    f_h.write("\n")
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
    for header in image_headers:
        var_name = header.replace(".h", "")
        f_cc.write(f"    {{{var_name}, {var_name}_len}},\n")
    f_cc.write("};\n\n")
    f_cc.write(f"const unsigned int num_images = sizeof(all_images)/sizeof(all_images[0]);\n")

print(f"Generated {all_h_path} and {all_cc_path} with {len(image_headers)} images.")
