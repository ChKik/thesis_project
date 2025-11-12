#pragma once

#include "class10_923_image.h"
#include "class13_1112_image.h"
#include "class16_1014_image.h"
#include "class19_976_image.h"

extern const unsigned char class10_923_image[];
extern const unsigned int class10_923_image_len;

extern const unsigned char class13_1112_image[];
extern const unsigned int class13_1112_image_len;

extern const unsigned char class16_1014_image[];
extern const unsigned int class16_1014_image_len;

extern const unsigned char class19_976_image[];
extern const unsigned int class19_976_image_len;

struct ImageBuffer {
    const unsigned char* data;
    const unsigned int length;
};

extern const ImageBuffer all_images[];
extern const unsigned int num_images;
