#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//constexpr giati everything is provided at compile time the function can be evaluated at compile time. 
namespace {
    constexpr int kGestureCount = 20;
    constexpr int kImageWidth = 224;
    constexpr int kImageHeight = 224;
    constexpr int kChannels = 3;
    // edw einai to thema , pws tha ginei to allocate toy arena gia to model.
    constexpr int kTensorArenaSize = 800 * 1024; // Adjusted for your model, mporw na to valw 800kb kai na to kanei mono toy memory assign isws?
}

// na checkarw to max megethos poy mporei na exei o tensoras , mesw toy compile.

#endif // CONSTANTS_H