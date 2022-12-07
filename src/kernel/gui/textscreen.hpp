#ifndef BOOTACODDY_KERNEL_TEXTSCREEN_HPP
#define BOOTACODDY_KERNEL_TEXTSCREEN_HPP

#include "../../util/types.h"
#include "../../util/types/textbuffer.hpp"

namespace bac::kernel::gui {

    class TextScreen : public types::TextBuffer {
    public:

        TextScreen(size_t x, size_t y, size_t width, size_t height, u8 scale = 1, u8 foreground = 0x0F,
                   u8 background = 0x08, size_t pages = 1, size_t padding = 0, size_t line_spacing = 0);

        u8 FG, BG;
        bool enabled = true;

        void redraw();

        void redrawLetter(size_t curs);

        size_t cols();

        size_t rows();

        size_t scale();

        size_t cursor();

        vec2d cursor2D();

        vec2d posOf(size_t col, size_t row);

        vec2d to2D(size_t curs);

        char charAt(size_t curs);

        void cursorLeft();

        void cursorRight();

        void end();

        void home();


    protected:

        size_t scroll = 0;
        size_t SCALE, WIDTH, HEIGHT, X, Y, PADDING, COLS, ROWS, LINE_SPACING;

        void drawLetter(char l, size_t col, size_t row);

        void placeChar(char ch, size_t curs);

        void updateForwards(size_t curs);

    };


}


#endif