#ifndef BOOTACODDY_DRIVERS_VIDEO_LFB_HPP
#define BOOTACODDY_DRIVERS_VIDEO_LFB_HPP

#include "../../kernel/multiboot.hpp"
#include "../../kernel/vga.hpp"
#include "../../kernel/fonts.hpp"
#include "../../util/types/list.hpp"
#include "../../kernel/paging.hpp"

namespace bac::drivers::video::lfb8 {

    using namespace kernel::vga;

    extern size_t W, H, ADDR;
    extern fonts::Font8 *FONT;

    void rect(size_t x1, size_t y1, size_t x2, size_t y2, u8 color);

    void rectf(size_t x1, size_t y1, size_t x2, size_t y2, u8 color);
    
    void hline(size_t x1, size_t y, size_t x2, u8 color);

    void vline(size_t x, size_t y1, size_t y2, u8 color);

    void clear(u8 color);

    void letter(size_t x, size_t y, char c, u8 color, size_t scale = 1);

    void text(size_t x, size_t y, char *text, u8 color, size_t scale = 1);

    void init(multiboot *mb);

}

#endif