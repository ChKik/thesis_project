#pragma once

#include "class12_935_image.h"
#include "class16_1132_image.h"
#include "class19_939_image.h"
#include "class1_1173_image.h"

extern const unsigned char class12_935_image[];
extern const unsigned int class12_935_image_len;

extern const unsigned char class16_1132_image[];
extern const unsigned int class16_1132_image_len;

extern const unsigned char class19_939_image[];
extern const unsigned int class19_939_image_len;

extern const unsigned char class1_1173_image[];
extern const unsigned int class1_1173_image_len;

struct ImageBuffer {
    const unsigned char* data;
    const unsigned int length;
};

extern const ImageBuffer all_images[];
extern const unsigned int num_images;
