
#include "../util/types.h"
#include "../drivers/video/lfb8.hpp"
#include "../kernel/gui/textscreen.hpp"
#include "../drivers/input/keyboard.hpp"
#include "../drivers/system/timer.hpp"

#define CURSOR_FREQUENCY 2

namespace bac::programs::shell {

    using namespace drivers::video;
    using namespace drivers::input;
    using namespace drivers::system;

    kernel::gui::TextScreen *screen;

    size_t cursorTimer = 0;
    bool cursor_toggle = false;

    size_t startCursor = 0, endCursor = 0;

    size_t lastCursor = 0;

    void cursorOff() {
        vec2d curs2D = screen->to2D(lastCursor);
        vec2d pos = screen->posOf(curs2D.x, curs2D.y);
        lfb8::rectf(pos.x, pos.y - 4, pos.x + 5, pos.y + screen->scale() * 8 + 4, screen->BG);
        screen->redrawLetter(lastCursor);
    }

    void cursorOn() {

        cursorOff();
        vec2d curs2D = screen->cursor2D();
        vec2d pos = screen->posOf(curs2D.x, curs2D.y);
        lfb8::rectf(pos.x, pos.y - 4, pos.x + 5, pos.y + screen->scale() * 8 + 4, screen->FG);
        lastCursor = screen->cursor();
    }

    void updateCursor(bool on) {

        cursor_toggle = on;

        if (on)
            cursorOn();
        else cursorOff();
    }

    int main() {

        kernel::gui::TextScreen _ = kernel::gui::TextScreen(0, 0, lfb8::W, lfb8::H, 4, 0x14, 0x15, 1, 8, 8);
        screen = &_;

        updateCursor(true);

        timer::onTimerTick = []() {

            cursorTimer++;

            if (cursorTimer >= timer::TIMER_FREQUENCY / CURSOR_FREQUENCY) {

                updateCursor(!cursor_toggle);
                cursorTimer = 0;
            }
        };

        keyboard::onKeyPressed = [](auto key) {

            if (key == keyboard::Keycode::Backspace) {
                if (screen->cursor() > startCursor && screen->backspace())
                    endCursor--;
            }

            else if (key == keyboard::Keycode::Enter || key == keyboard::Keycode::KeypadEnter) {
                screen->printc('\n');
            }

            else if (key == keyboard::Keycode::End || key == keyboard::Keycode::KeypadOne_KeypadEnd) {
                screen->end();
            }

            else if (key == keyboard::Keycode::Home || key == keyboard::Keycode::KeypadSeven_KeypadHome) {
                screen->home();
            }

            else if (key == keyboard::Keycode::LeftArrow || key == keyboard::Keycode::KeypadFour_KeypadLeftArrow) {
                if (screen->cursor() > startCursor)
                    screen->cursorLeft();
            }
            else if (key == keyboard::Keycode::RightArrow || key == keyboard::Keycode::KeypadSix_KeypadRightArrow) {
                if (screen->cursor() < endCursor)
                    screen->cursorRight();
            }
            else if (keyboard::text::isSymbol(key)) {

                char c = keyboard::text::toAscii(key);

                screen->printc(c);
                endCursor++;
            }

            updateCursor(true);
            cursorTimer = 0;
        };

        while (1);

        return 0;
    }

}