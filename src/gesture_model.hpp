#ifndef GESTURE_MODEL_HPP
#define GESTURE_MODEL_HPP

#include "constants.hpp"
#include <tensorflow/lite/micro/micro_interpreter.h>

extern const unsigned char zephyr_quantized_int8_tflite[];  //me to extern tha koitaksei sto model_data.cc package gia na vrei ta variables.
extern const int zephyr_quantized_int8_tflite_len;

class GestureModel {
public:
    GestureModel();
    bool Init();
    uint8_t* GetInputBuffer();
    bool Predict();
    int GetPrediction() const;

private:
    alignas(16) uint8_t tensor_arena_[kTensorArenaSize];
    const tflite::Model* model_;
    tflite::MicroInterpreter* interpreter_;
    TfLiteTensor* input_;
    TfLiteTensor* output_;
};

#endif // GESTURE_MODEL_H