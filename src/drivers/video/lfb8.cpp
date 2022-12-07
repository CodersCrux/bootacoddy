#include "lfb8.hpp"

namespace bac::drivers::video::lfb8 {

    using namespace kernel::vga;

    size_t W, H, P, ADDR;

    fonts::Font8 *FONT = &fonts::font8x8;

    void rect(size_t x1, size_t y1, size_t x2, size_t y2, u8 color) {

        u8 *ptr = (u8 *) ADDR + x1 + y1 * P;
        size_t x, y;
        for (x = x1; x < x2; x++, ptr++)
            *ptr = color;
        for (y = y1; y <= y2; y++, ptr += P)
            *ptr = color;
        ptr -= x2 - x1 + (y2 - y1) * P;
        for (y = y1 + 1; y < y2; y++, ptr += P)
            *ptr = color;
        for (x = x1; x < x2; x++, ptr++)
            *ptr = color;
    }

    void rectf(size_t x1, size_t y1, size_t x2, size_t y2, u8 color) {

        u8 *ptr = (u8 *) ADDR + x1 + y1 * P;
        size_t x;
        while (y1++ <= y2) {

            for (x = x1; x <= x2; x++, ptr++)
                *ptr = color;
            ptr += P + x1 - x2 - 1;
        }
    }

    void hline(size_t x1, size_t y, size_t x2, u8 color) {

        u8 *ptr = (u8 *) ADDR + x1 + y * P;
        while (x1++ <= x2)
            *ptr++ = color;
    }

    void vline(size_t x, size_t y1, size_t y2, u8 color) {

        u8 *ptr = (u8 *) ADDR + x + y1 * P;
        while (y1++ <= y2) {
            *ptr = color;
            ptr += P;
        }
    }

    void clear(u8 color) {
        rectf(0, 0, W, H, color);
    }

    void letter(size_t x, size_t y, char c, u8 color, size_t scale) {

        u8 *l = FONT->letters[c];
        for (size_t ly = 0, lx; ly < 8; ly++) {
            u8 line = l[ly];
            for (lx = 0; lx < 8; lx++, line >>= 1)
                if (line & 1) {
                    if (FONT->invert)
                        rectf(x + (7 - lx) * scale, y + ly * scale, x + (8 - lx) * scale, y + (ly + 1) * scale, color);
                    else rectf(x + lx * scale, y + ly * scale, x + (lx + 1) * scale, y + (ly + 1) * scale, color);
                }
        }
    }

    void text(size_t x, size_t y, char *text, u8 color, size_t scale) {

        while (*text) {
            letter(x, y, *text++, color, scale);
            x += scale * 8;
        }
    }

    void init(multiboot *mb) {
        ADDR = mb->fb.addr;
        W = mb->fb.width;
        H = mb->fb.height;
        P = mb->fb.pitch;

        // Set palette
        {
//             0x55: 15, 0xAA: 42
            set_palette(0x0, 0, 0, 0);
            set_palette(0x1, 0, 0, 42);
            set_palette(0x2, 0, 42, 0);
            set_palette(0x3, 0, 42, 42);
            set_palette(0x4, 42, 0, 0);
            set_palette(0x5, 42, 0, 42);
            set_palette(0x6, 42, 15, 0);
            set_palette(0x7, 42, 42, 42);
            set_palette(0x8, 15, 15, 15);
            set_palette(0x9, 15, 15, 63);
            set_palette(0xA, 15, 63, 63);
            set_palette(0xB, 15, 63, 63);
            set_palette(0xC, 63, 15, 15);
            set_palette(0xD, 63, 15, 63);
            set_palette(0xE, 63, 63, 15);
            set_palette(0xF, 63, 63, 63);

            // Custom colors
            set_palette(0x10, VGA_COLOR6(0xDA01B2, "#DA01B2"));
            set_palette(0x11, VGA_COLOR6(0x96DE37, "#96DE37"));
            set_palette(0x12, VGA_COLOR6(0x9AA611, "#9AA611"));
            set_palette(0x13, VGA_COLOR6(0x73322E, "#73322E"));
            set_palette(0x14, VGA_COLOR6(0xA61911, "#A61911"));
            set_palette(0x15, VGA_COLOR6(0xfdf6e3, "#fdf6e3"));

        }

    }
}