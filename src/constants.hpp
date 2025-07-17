#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define KILOBYTE_NUM 120
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
//TESTS
//  kb size  |   RAM Overflow
//  800      |   600 kb
//  600      |   420 kb
//  512      |   330 kb
//  450      |   266 kb
//  300      |   113 kb
//  224      |   35kb
//  200      |   10,2kb
//  180      |   compiled alla den exei arketh ram gia tis prakseis
//  170      |   >>
//  120      |      >>


#endif // CONSTANTS_H