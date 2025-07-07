#include "gesture_model.hpp"
#include "constants.hpp"
#include <tensorflow/lite/micro/micro_log.h> 
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>

GestureModel::GestureModel() : 
    model_(tflite::GetModel(zephyr_quantized_int8_tflite)), // pairnei ta weights apo to model_data.cc
    interpreter_(nullptr) {}

bool GestureModel::Init() {
    static tflite::MicroMutableOpResolver<5> resolver;  //exei mono merika ops oxi olo to package gia na savarw space.
    resolver.AddConv2D();
    resolver.AddDepthwiseConv2D();
    resolver.AddAveragePool2D();
    resolver.AddReshape();
    resolver.AddSoftmax();

    static tflite::MicroInterpreter interpreter(
        model_, resolver, tensor_arena_, sizeof(tensor_arena_));
    
    interpreter_ = &interpreter;
    
    if (interpreter_->AllocateTensors() != kTfLiteOk) {
        MicroPrintf("Tensor allocation failed");
        return false;
    }

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
    return input_->data.uint8;
}

bool GestureModel::Predict() {
    return interpreter_->Invoke() == kTfLiteOk;
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