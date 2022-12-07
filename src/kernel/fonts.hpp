#ifndef BOOTACODDY_KERNEL_FONTS_HPP
#define BOOTACODDY_KERNEL_FONTS_HPP

#include "../util/types.h"

namespace bac::fonts {

    struct Font8 {
        bool invert = false;
        u8 letters[128][8];
    };

    extern Font8 font8x8;
    extern Font8 vincent8x8;

}

#endif