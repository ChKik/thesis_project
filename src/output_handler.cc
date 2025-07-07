#include "output_handler.hpp"
#include <tensorflow/lite/micro/micro_log.h>

const char* kGestureLabels[kGestureCount] = {
    "Circle Hand",
    "Pointer Finger",
    "Two Fingers Lifted",
    "Three Fingers Lifted",
    "Five Fingers Lifted",
    "Three Fingers Fist",
    "Pointer Middle Pinky Lifted",
    "Thumb Ring Pinky  Lifted",
    "Middle Ring Pinky Lifted",
    "Loser Sign",
    "Closed Fist",
    "Small Indicator",
    "Fingers Crossed",
    "Closed Fist Upwards",
    "Ok sign sideways",
    "Hook finger",
    "Helicopter sign",
    "British Pinky",
    "Okay sign upwards"
};

void HandleOutput(int gesture_class) {
    if (gesture_class >= 0 && gesture_class < kGestureCount) {
        MicroPrintf("Detected: %s", kGestureLabels[gesture_class]);
    } else {
        MicroPrintf("Unknown gesture");
    }
}