#include "vga.hpp"
#define PORT_VGA_ADDRESS_WRITE 0x3C8
#define PORT_VGA_DATA 0x3C9

namespace bac::kernel::vga {

    /**
     * @brief Set the palette of a VGA 256 color.\n
     * R, G, B values range from 0-63 inclusive.
     * @param index
     * @param r
     * @param g
     * @param b
     */
    void set_palette(u8 index, u8 r, u8 g, u8 b) {

        ports::outb(PORT_VGA_ADDRESS_WRITE, index);
        ports::outb(PORT_VGA_DATA, r);
        ports::outb(PORT_VGA_DATA, g);
        ports::outb(PORT_VGA_DATA, b);
    }
}