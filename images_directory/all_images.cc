#include "all_images.h"

const ImageBuffer all_images[] = {
    {class000_image, class000_image_len},
    {class100_image, class100_image_len},
    {class120_image, class120_image_len},
};

const unsigned int num_images = sizeof(all_images)/sizeof(all_images[0]);
