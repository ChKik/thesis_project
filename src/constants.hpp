#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace {
    constexpr int kGestureCount = 20;
    constexpr int kImageWidth = 224;
    constexpr int kImageHeight = 224;
    constexpr int kChannels = 3;
    // edw einai to thema , pws tha ginei to allocate toy arena gia to model.
    constexpr int kTensorArenaSize = 700 * 1024; // Adjusted for your model, mporw na to valw 700kb kai na to kanei mono toy memory assign isws?
}

#endif // CONSTANTS_H