#pragma once

#include "class000_image.h"
#include "class100_image.h"
#include "class120_image.h"


// Forward declarations
extern const unsigned char class000_image[];
extern const unsigned int class000_image_len;

extern const unsigned char class100_image[];
extern const unsigned int class100_image_len;

extern const unsigned char class120_image[];
extern const unsigned int class120_image_len;



struct ImageBuffer {
    const unsigned char* data;
    const unsigned int length;
};

extern const ImageBuffer all_images[];
extern const unsigned int num_images;
