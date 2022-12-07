#ifndef BOOTACODDY_KERNEL_VGA_HPP
#define BOOTACODDY_KERNEL_VGA_HPP

#include "../util/types.h"
#include "../util/ports.hpp"

#define PORT_VGA_ADDRESS_WRITE 0x3C8
#define PORT_VGA_DATA 0x3C9

#define VGA_COLOR6(hex, ...) (u8)(((double)((hex >> 16) & 0xFF) / 256) * 64), (u8)(((double)((hex >> 8) & 0xFF) / 256) * 64), (u8)(((double)(hex & 0xFF) / 256) * 64)

namespace bac::kernel::vga {

    /**
     * @brief Set the palette of a VGA 256 color.\n
     * R, G, B values range from 0-63 inclusive.
     * @param index
     * @param r
     * @param g
     * @param b
     */
    void set_palette(u8 index, u8 r, u8 g, u8 b);
}

#endif