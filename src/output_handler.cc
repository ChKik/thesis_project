#include "output_handler.hpp"
#include <tensorflow/lite/micro/micro_log.h>

const char* kGestureLabels[kGestureCount] = {
    "Class 0",
    "Class 1",
    "Class 2",
    "Class 3",
    "Class 4",
    "Class 5",
    "Class 6",
    "Class 7",
    "Class 8",
    "Class 9",
    "Class 10",
    "Class 11",
    "Class 12",
    "Class 13",
    "Class 14",
    "Class 15",
    "Class 16",
    "Class 17",
    "Class 18",
    "Class 19"
};


void HandleOutput(int gesture_class) {
    if (gesture_class >= 0 && gesture_class < kGestureCount) {
        MicroPrintf("Detected: %s", kGestureLabels[gesture_class]);
    } else {
        MicroPrintf("Unknown gesture");
    }
}