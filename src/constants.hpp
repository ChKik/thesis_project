#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define KILOBYTE_NUM 880
//constexpr giati everything is provided at compile time the function can be evaluated at compile time. 
namespace {
    constexpr int kGestureCount = 20;
    constexpr int kImageWidth = 224;
    constexpr int kImageHeight = 224;
    constexpr int kChannels = 3;
    constexpr int kTensorArenaSize = KILOBYTE_NUM * 1024; // global static buffer ginetai allocated sto link time oxi dynamically.
}

// na checkarw to max megethos poy mporei na exei o tensoras , mesw toy compile.


// META TIS ALLAGES TIS CONST EIKONAS/BUFFER ME TIN RAM
//800       | thelei parapanw to arena
//850       | compiled kai doulevei to model <-- To palio model nai to new oxi
//860       | test gia to new model. Oxi den mporei
//880       | kanei build oriaka


#endif // CONSTANTS_H