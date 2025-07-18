#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define KILOBYTE_NUM 850
//constexpr giati everything is provided at compile time the function can be evaluated at compile time. 
namespace {
    constexpr int kGestureCount = 20;
    constexpr int kImageWidth = 224;
    constexpr int kImageHeight = 224;
    constexpr int kChannels = 3;
    // edw einai to thema , pws tha ginei to allocate toy arena gia to model.
    constexpr int kTensorArenaSize = KILOBYTE_NUM * 1024; // global static buffer ginetai allocated sto link time oxi dynamically.
}

// na checkarw to max megethos poy mporei na exei o tensoras , mesw toy compile.


// META TIS ALLAGES TIS CONST EIKONAS/BUFFER ME TIN RAM
//800       | thelei parapanw to arena
//850       | compiled kai doulevei to model


#endif // CONSTANTS_H