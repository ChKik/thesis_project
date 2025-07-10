#include <zephyr/kernel.h>  //auto to vriskei aytomata apo to zephyrbase poy kaneis source. Wstoso tha dokimasw na to valw sto path.
#include "gesture_model.hpp"
#include "output_handler.hpp"
#include "constants.hpp"
#include <scripts/raw_buffer_image_decoder.h>

namespace {
    GestureModel model;
}

void main(void) {
    if (!model.Init()) {
        MicroPrintf("Failed to initialize model");
        return;
    }

    while (true) {
        //kanei decode to JPEG image se raw rgb buffer poy thelei san input to model moy poy prepei na einai 224x224x3.
        struct imgRawImage* img= loadJpegImageFile("/home/haris/thesis_project/image_processed/1_resized.jpg");
        if(!img){
            MicroPrintf("JPEG decoding failed");
            return;
        }

        
         // edw tha prepei na na pairnei san input mia eikona apo to memory 
        uint8_t* input = model.GetInputBuffer();
        memcpy(input, img->lpData, img->width * img->height * img->numComponents);
       

        // free memory if you're done with it
        free(img->lpData);
        free(img);


        // 2. Run inference
        if (!model.Predict()) {
            MicroPrintf("Prediction failed");
            k_msleep(100);
            continue;
        }

        // 3. Handle results
        HandleOutput(model.GetPrediction());
        
        k_msleep(100); 
    }
}