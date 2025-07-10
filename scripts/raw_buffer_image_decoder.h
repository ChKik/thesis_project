#ifndef RAW_BUFFER_IMAGE_DECODER_H
#define RAW_BUFFER_IMAGE_DECODER_H

// Source code provided by https://www.tspi.at/2020/03/20/libjpegexample.html?utm_source=chatgpt.com#gsc.tab=0 , all credits go to the author.

#ifdef __cplusplus
extern "C" {
#endif

struct imgRawImage {
    unsigned int numComponents;
    unsigned long width, height;
    unsigned char* lpData;
};

struct imgRawImage* loadJpegImageFile(const char* filename);

#ifdef __cplusplus
}
#endif

#endif // RAW_BUFFER_IMAGE_DECODER_H