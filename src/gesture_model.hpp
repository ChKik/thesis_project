#ifndef GESTURE_MODEL_HPP
#define GESTURE_MODEL_HPP

#include "constants.hpp"
#include <tensorflow/lite/micro/micro_interpreter.h>



class GestureModel {
public:
    GestureModel();
    bool Init();
    uint8_t* GetInputBuffer();
    bool Predict();
    int GetPrediction() const;

private:
    alignas(16) uint8_t tensor_arena_[kTensorArenaSize];  //CMSIS-NN  requires 16-byte alignmen
    const tflite::Model* model_;
    tflite::MicroInterpreter* interpreter_;
    TfLiteTensor* input_;
    TfLiteTensor* output_;
};

#endif // GESTURE_MODEL_H