#pragma once

#include "class17_1183_image.h"
#include "class5_1066_image.h"
#include "class5_1080_image.h"
#include "class6_904_image.h"

extern const unsigned char class17_1183_image[];
extern const unsigned int class17_1183_image_len;

extern const unsigned char class5_1066_image[];
extern const unsigned int class5_1066_image_len;

extern const unsigned char class5_1080_image[];
extern const unsigned int class5_1080_image_len;

extern const unsigned char class6_904_image[];
extern const unsigned int class6_904_image_len;

struct ImageBuffer {
    const unsigned char* data;
    const unsigned int length;
};

extern const ImageBuffer all_images[];
extern const unsigned int num_images;
