#include "raw_buffer_image_decoder.h"
#include <stdio.h>
#include <stdlib.h>

void execute_image_decoding(){

struct imgRawImage* img = loadJpegImageFile("/home/haris/thesis_project/image_processed/1_resized.jpg"); //stin c dne mporeis na exeis se global var assigned sunartisi.
FILE* out = fopen("image_buffer.bin", "wb"); //tha ftiaksei to bin mesa sto scripts file kai meta me to xxd tha to metaferw sto src.
fwrite(img->lpData, 1, img->width * img->height * img->numComponents, out);
fclose(out);
free(img->lpData);
free(img);

}
