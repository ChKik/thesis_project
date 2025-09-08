#include "raw_buffer_image_decoder.h"
#include <stdio.h>
#include <stdlib.h>

/* This function takes as argument the path of a resized image and turns it into a binary file. The binary file will be turned into .bin and then into a .h file inside src to be used.
For example here 1_resized is turned into decode_image_binary and then into image_buffer.bin , which with xdd gets turned into a image_buffer.h to be used by src and the model for prediction */
void execute_image_decoding(){

struct imgRawImage* img = loadJpegImageFile("/home/haris/thesis_project/image_processed/1_resized.jpg"); //stin c dne mporeis na exeis se global var assigned sunartisi.
FILE* out = fopen("image_buffer.bin", "wb"); //tha ftiaksei to bin mesa sto scripts file kai meta me to xxd tha to metaferw sto src.
fwrite(img->lpData, 1, img->width * img->height * img->numComponents, out);
fclose(out);
free(img->lpData);
free(img);

}
