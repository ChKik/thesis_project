#include "gesture_model.hpp"
#include "constants.hpp"
#include <tensorflow/lite/micro/micro_log.h> 
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>

GestureModel::GestureModel() : 
    model_(tflite::GetModel(zephyr_quantized_int8_tflite)), // pairnei ta weights apo to model_data.cc
    interpreter_(nullptr) {}


bool GestureModel::Init() {
    //verify oti exei perasei to tflite stin flash mnimi
    MicroPrintf("Model flash address: %p ", 
        zephyr_quantized_int8_tflite);
    static tflite::MicroMutableOpResolver<7> resolver;  // Increased to 7 ops
    
    // MobileNetV2 Base
    resolver.AddConv2D();           // Standard convolution
    resolver.AddDepthwiseConv2D();  // Depthwise separable conv
    resolver.AddAveragePool2D();    // For GlobalAveragePooling2D replacement
    
    // Head
    resolver.AddFullyConnected();   // Dense layer
    resolver.AddSoftmax();          // Softmax activation
    
    // Quantization-specific
    resolver.AddQuantize();         // For uint8 input handling
    

    static tflite::MicroInterpreter interpreter(
        model_, resolver, tensor_arena_, sizeof(tensor_arena_));
    
    interpreter_ = &interpreter;
    
    if (interpreter_->AllocateTensors() != kTfLiteOk) {
        MicroPrintf("Tensor allocation failed");
        return false;
    }

    //verify gia to memory usage allocation 
    MicroPrintf("SRAM usage: %zu/%zu bytes (Arena: 0x%p - 0x%p)",
           interpreter_->arena_used_bytes(),
           kTensorArenaSize,  //einai sto constants.hpp
           tensor_arena_,   //einai sto gesture_model.hpp
           tensor_arena_ + kTensorArenaSize);


    input_ = interpreter_->input(0);
    output_ = interpreter_->output(0);

    // Verify input matches our constants
    if (input_->dims->data[1] != kImageWidth || 
        input_->dims->data[2] != kImageHeight ||
        input_->dims->data[3] != kChannels) {
        MicroPrintf("Bad input dimensions");
        return false;
    }

    return true;
}

uint8_t* GestureModel::GetInputBuffer() {
    return input_->data.uint8;  //to input_ kai data einai tflite tensors
     // tha prepei na kanw load tin eikona kai na tin diavasw apo tin sram
    // opws to eixa kanei paliotera. tha thelei quantize prwta omws.
}

bool GestureModel::Predict() {
    //validation gia to memory validation
    size_t pre_invoke_usage = interpreter_->arena_used_bytes();
    if (interpreter_->Invoke() != kTfLiteOk) return false;
    
    MicroPrintf("Peak RAM usage: %zu bytes (Delta: %zu)",
               interpreter_->arena_used_bytes(),
               interpreter_->arena_used_bytes() - pre_invoke_usage);
    return true;
}

int GestureModel::GetPrediction() const {
    uint8_t* scores = output_->data.uint8;
    int max_idx = 0;
    for (int i = 1; i < kGestureCount; i++) {
        if (scores[i] > scores[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}

