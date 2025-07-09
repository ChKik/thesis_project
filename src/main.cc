#include <zephyr/kernel.h>  //auto to vriskei aytomata apo to zephyrbase poy kaneis source. Wstoso tha dokimasw na to valw sto path.
#include "gesture_model.hpp"
#include "output_handler.hpp"
#include "constants.hpp"

namespace {
    GestureModel model;
}

void main(void) {
    if (!model.Init()) {
        MicroPrintf("Failed to initialize model");
        return;
    }

    while (true) {
        
      
        uint8_t* input = model.GetInputBuffer();
        // edw tha prepei na ftiaksw na pairnei san input mia eikona apo to memory 

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