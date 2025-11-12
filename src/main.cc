#include <zephyr/kernel.h>  //auto to vriskei aytomata apo to zephyrbase poy kaneis source. To evala kai sto sto path gia na to vriskei to vscode.
#include "gesture_model.hpp"
#include "output_handler.hpp"
#include "constants.hpp"

#include  "all_images.h"


unsigned int iteration_counter=0;

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

    while (iteration_counter<num_images) {  //to vazw na trexei mono 3 fores pros to parwn to prediction tis eikonas.
        
        const unsigned char* data = all_images[iteration_counter].data;
        unsigned int len = all_images[iteration_counter].length;

        uint8_t* input = model.GetInputBuffer();
        memcpy(input, data, len);

         /* ---- TIMER START ---- */
        uint32_t start_time = (uint32_t)k_uptime_get_32();
       

        // Run inference
        if (!model.Predict()) {
            MicroPrintf("Prediction failed");
            k_msleep(100);
            continue;
        }

         /* ---- TIMER END ---- */
        uint32_t end_time = (uint32_t)k_uptime_get_32();
        uint32_t elapsed = end_time - start_time;

        MicroPrintf("Inference %u took %u ms", iteration_counter, elapsed);


        // Handle results of the predictions and output on Picocom
        HandleOutput(model.GetPrediction());
        
        iteration_counter++;
        k_msleep(100); 
        
    }
    return 0;
}