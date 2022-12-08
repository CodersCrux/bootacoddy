#include "textscreen.hpp"
#include "../../drivers/video/lfb8.hpp"
#include "../qemu.hpp"

namespace bac::kernel::gui {

    using namespace bac::drivers::video;

    TextScreen::TextScreen(size_t x, size_t y, size_t width, size_t height, u8 scale, u8 foreground,
                           u8 background, size_t pages, size_t padding, size_t line_spacing)
            : X(x), Y(y), FG(foreground), BG(background), SCALE(scale), WIDTH(width), HEIGHT(height),
              PADDING(padding), LINE_SPACING(line_spacing),
              TextBuffer(
                      (width - padding) / (8 * scale)
                      * (height - padding) / (8 * scale + line_spacing)
                      * pages
              ) {

        COLS = (width - padding) / (8 * scale);
        ROWS = (height - padding) / (8 * scale + line_spacing);

        redraw();
    }

    void TextScreen::redraw() {

        lfb8::rectf(X, Y, X + WIDTH, Y + HEIGHT, BG);

        size_t line = 0;
        size_t len = 0;

        for (size_t i = 0; i < length; i++)
            if (data[i] == '\n') {
                line++;
                len = 0;
            } else {

                if (++len >= WIDTH) {
                    line++;
                    len = 0;
                }

                drawLetter(data[i], len, line);
            }
    }

    void TextScreen::redrawLetter(size_t curs) {
        vec2d pos = to2D(curs);
        drawLetter(data[curs], pos.x, pos.y);
    }

    size_t TextScreen::cols() {
        return COLS;
    }

    size_t TextScreen::rows() {
        return ROWS;
    }

    size_t TextScreen::scale() {
        return SCALE;
    }

    size_t TextScreen::cursor() {
        return CURSOR;
    }

    vec2d TextScreen::cursor2D() {
        return to2D(CURSOR);
    }

    vec2d TextScreen::posOf(size_t col, size_t row) {
        size_t span = SCALE * 8;
        return {X + PADDING + col * span, Y + PADDING + row * (span + LINE_SPACING)};
    }

    char TextScreen::charAt(size_t curs) {

        if (curs >= length)
            return 0;
        return data[curs];
    }

    vec2d TextScreen::to2D(size_t curs) {
        vec2d c = {0, 0};
        for (size_t i = 0; i < curs; i++)
            if (data[i] == '\n' || c.x >= COLS) {
                c.x = 0;
                c.y++;
            } else c.x++;
        return c;
    }

    void TextScreen::cursorLeft() {

        if (CURSOR)
            CURSOR--;
    }

    void TextScreen::cursorRight() {

        if (CURSOR < length)
            CURSOR++;
    }

    void TextScreen::end() {
        for (; CURSOR < length && data[CURSOR] != '\n'; CURSOR++);
    }

    void TextScreen::home() {
        for (; CURSOR > 0; CURSOR--)
            if (data[CURSOR] == '\n') {
                CURSOR++;
                break;
            }
    }

    void TextScreen::drawLetter(char l, size_t col, size_t row) {

        vec2d pos = posOf(col, row);
        lfb8::rectf(pos.x, pos.y, pos.x + SCALE * 8, pos.y + SCALE * 8, BG);
        if (l && l != ' ')
            lfb8::letter(pos.x, pos.y, l, FG, SCALE);
    }

    void TextScreen::placeChar(char ch, size_t curs) {

        vec2d pos = to2D(curs);
        drawLetter(ch, pos.x, pos.y);
    }

    void TextScreen::updateForwards(size_t curs) {

        for (size_t i = curs; i <= length; i++)
            placeChar(data[i], i);
    }
}