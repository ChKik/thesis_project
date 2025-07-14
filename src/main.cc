#include <zephyr/kernel.h>  //auto to vriskei aytomata apo to zephyrbase poy kaneis source. Wstoso tha dokimasw na to valw sto path.
#include "gesture_model.hpp"
#include "output_handler.hpp"
#include "constants.hpp"
#include "image_buffer.h"


namespace {
    GestureModel model;
}

int main(int argc,char *argv[]) {
    if (!model.Init()) {
        MicroPrintf("Failed to initialize model");
        return -1;
    }

    while (true) {
        
         // edw tha prepei na na pairnei san input mia eikona apo to memory , prepei na to testarw ama doulevei twra.
        uint8_t* input = model.GetInputBuffer();
        memcpy(input, image_buffer, image_buffer_len);


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
    return 0;
}