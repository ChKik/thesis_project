#include <zephyr/kernel.h>  //auto to vriskei aytomata apo to zephyrbase poy kaneis source. To evala kai sto sto path gia na to vriskei to vscode.
#include "gesture_model.hpp"
#include "output_handler.hpp"
#include "constants.hpp"
#include "image_buffer.h"



namespace {
    GestureModel model;
}
/*//eprepe na to allaksw gia na min exei conflict me to Zephyr main kai gia na mporei na to vrei to zephyr. 
Epeidh einai C++ file kai ta Zephyr headers kanoyn declare extern int main(void);  gia to   entrypoint
Exei diko toy Zephyr declaration diladi.*/
extern "C" int main(void){  
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