#pragma once

#include "class0_1119_image.h"
#include "class10_906_image.h"
#include "class1_1087_image.h"
#include "class1_926_image.h"

extern const unsigned char class0_1119_image[];
extern const unsigned int class0_1119_image_len;

extern const unsigned char class10_906_image[];
extern const unsigned int class10_906_image_len;

extern const unsigned char class1_1087_image[];
extern const unsigned int class1_1087_image_len;

extern const unsigned char class1_926_image[];
extern const unsigned int class1_926_image_len;

struct ImageBuffer {
    const unsigned char* data;
    const unsigned int length;
};

extern const ImageBuffer all_images[];
extern const unsigned int num_images;
