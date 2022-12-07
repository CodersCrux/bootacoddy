#include "keyboard.hpp"


namespace bac::drivers::input::keyboard {

    enum class Scancodes : u8 {

        NULL = 0x00,
        Escape,
        One_ExclamationMark,
        Two_At,
        Three_Hash,
        Four_Dollar,
        Five_Percent,
        Six_Caret,
        Seven_Ampersand,
        Eight_Asterisk,
        Nine_OpenBracket,
        Zero_CloseBracket,
        Dash_Underscore,
        Equal_Plus,
        Backspace,
        Tab,
        Q,
        W,
        E,
        R,
        T,
        Y,
        U,
        I,
        O,
        P,
        OpenSquareBracket_OpenCurlyBracket,
        CloseSquareBracket_CloseCurlyBracket,
        Enter,
        LeftControl,
        A,
        S,
        D,
        F,
        G,
        H,
        J,
        K,
        L,
        Semicolon_Colon,
        Quote_DoubleQuote,
        Backtick_Tilde,
        LeftShift,
        Backslash_Pipe,
        Z,
        X,
        C,
        V,
        B,
        N,
        M,
        Comma_LessThan,
        Dot_GreaterThan,
        Slash_QuestionMark,
        RightShift,
        KeypadAsterisk,
        LeftAlt,
        Spacebar,
        CapsLock,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        NumLock,
        ScrollLock,
        KeypadSeven_KeypadHome,
        KeypadEight_KeypadUpArrow,
        KeypadNine_KeypadPageUp,
        KeypadDash,
        KeypadFour_KeypadLeftArrow,
        KeypadFive,
        KeypadSix_KeypadRightArrow,
        KeypadPlus,
        KeypadOne_KeypadEnd,
        KeypadTwo_KeypadDownArrow,
        KeypadThree_KeypadPageDown,
        KeypadZero_KeypadInsert,
        KeypadDot_KeypadDelete,
        WORTHLESS_Alt_SysRq,
        WORTHLESS_FunctionKeyOnRandomIrrelevantKeyboards,
        Unlabeled,
        F11,
        F12
    };

    enum class EscapeScancodes : u8 {

        KeypadEnter = 0x1C,
        RightControl,
        WORTHLESS_LeftShift = 0x2A,
        KeypadSlash = 0x35,
        WORTHLESS_RightShift,
        PrintScreen,
        RightAlt,
        Break = 0x46,
        Home,
        UpArrow,
        PageUp,
        LeftArrow = 0x4B,
        RightArrow = 0x4D,
        End = 0x4F,
        DownArrow,
        PageDown,
        Insert,
        Delete,
        LeftWindows = 0x5B,
        RightWindows,
        Menu
    };

    // Maps keyboard scancodes to my own Keycode list
    u8 indexUntilCapsLock[] = {
            0, 49, 28, 29, 30, 31, 32, 33,
            34, 35, 36, 27, 37, 38, 50, 51,
            17, 23, 5, 18, 20, 25, 21, 9,
            15, 16, 39, 40, 52, 53, 1, 19,
            4, 6, 7, 8, 10, 11, 12, 41,
            42, 43, 54, 44, 26, 24, 3, 22,
            2, 14, 13, 45, 46, 47, 55, 56,
            57, 48, 58
    };

    const char *symbols = "0123456789-=[];'`\\,./";
    const char *symbols_alt = ")!@#$%^&*(_+{}:\"~|<>?";


    bool escapeCode = false;
    bool keymap[KEYBOARD_NUM_KEYS];

    bool capsLock = false;

    KeyPressedEvent onKeyPressed = 0;
    KeyReleasedEvent onKeyReleased = 0;

    static void irq_handler(bac::kernel::interrupts::Registers regs) {

        u8 sc = ports::inb(0x60);

        u8 c = sc >= 0x80 ? sc - 0x80 : sc;
        bool pressed = sc < 0x80;

        u8 key = 0;

        // Map the received key to our own Keycode structure
        if (!escapeCode) {

            if (c == 0xE0) { // Escape code

                escapeCode = true;
                return;
            }

            if (c <= (u8) Scancodes::CapsLock)
                key = indexUntilCapsLock[c];
            else if (c <= (u8) Scancodes::F12)
                key = (u8) Keycode::F1 + c - (u8) Scancodes::F1;

        } else {

            if (c >= (u8) EscapeScancodes::KeypadEnter && c <= (u8) EscapeScancodes::RightControl)
                key = (u8) Keycode::KeypadEnter + c - (u8) EscapeScancodes::KeypadEnter;
            else if (c >= (u8) EscapeScancodes::KeypadSlash && c <= (u8) EscapeScancodes::RightAlt)
                key = (u8) Keycode::KeypadSlash + c - (u8) EscapeScancodes::KeypadSlash;
            else if (c >= (u8) EscapeScancodes::Break && c <= (u8) EscapeScancodes::PageUp)
                key = (u8) Keycode::Break + c - (u8) EscapeScancodes::Break;
            else if (c == (u8) EscapeScancodes::LeftArrow)
                key = (u8) Keycode::LeftArrow;
            else if (c == (u8) EscapeScancodes::RightArrow)
                key = (u8) Keycode::RightArrow;
            else if (c == (u8) EscapeScancodes::End)
                key = (u8) Keycode::End;
            else if (c >= (u8) EscapeScancodes::DownArrow && c <= (u8) EscapeScancodes::Delete)
                key = (u8) Keycode::DownArrow + c - (u8) EscapeScancodes::DownArrow;
            else if (c >= (u8) EscapeScancodes::LeftWindows && c <= (u8) EscapeScancodes::Menu)
                key = (u8) Keycode::LeftWindows + c - (u8) EscapeScancodes::LeftWindows;

            escapeCode = false;
        }

        // Turn on/off pressed/released key
        keymap[key] = pressed;

        // Special keys
        if (key == (u8) Keycode::CapsLock && pressed) { // Caps lock pressed
            capsLock = !capsLock; // Toggle caps lock
        }

        // Call events
        if (pressed) {
            if (onKeyPressed)
                onKeyPressed((Keycode) key);
        }
        else if (onKeyReleased)
            onKeyReleased((Keycode) key);
    }

    void init() {

        kernel::interrupts::install_handler(IRQ1, irq_handler);
    }

    bool isKeyHeld(Keycode kc) {
        return keymap[(u8) kc];
    }

    bool isShift() {
        return isKeyHeld(Keycode::LeftShift) || isKeyHeld(Keycode::RightShift);
    }

    bool isControl() {
        return isKeyHeld(Keycode::LeftControl) || isKeyHeld(Keycode::RightControl);
    }

    bool isAlt() {
        return isKeyHeld(Keycode::LeftAlt) || isKeyHeld(Keycode::RightAlt);
    }

    bool isUpArrow() {
        return isKeyHeld(Keycode::UpArrow) || isKeyHeld(Keycode::KeypadEight_KeypadUpArrow);
    }

    bool isDownArrow() {
        return isKeyHeld(Keycode::DownArrow) || isKeyHeld(Keycode::KeypadTwo_KeypadDownArrow);
    }

    bool isRightArrow() {
        return isKeyHeld(Keycode::RightArrow) || isKeyHeld(Keycode::KeypadSix_KeypadRightArrow);
    }

    bool isLeftArrow() {
        return isKeyHeld(Keycode::LeftArrow) || isKeyHeld(Keycode::KeypadFour_KeypadLeftArrow);
    }

    bool isCapsLock() {
        return capsLock;
    }


    namespace text {

        bool isSymbol(Keycode kc) {
            return (kc >= Keycode::A && kc <= Keycode::Z) ||
                   (kc >= Keycode::Zero_CloseBracket && kc <= Keycode::Spacebar);
        }

        char toAscii(Keycode kc) {

            bool shift = isShift();
            bool uppercase = (capsLock + shift) & 1;

            if (kc >= Keycode::A && kc <= Keycode::Z)
                return 'a' + (u8) kc - (u8) Keycode::A - (uppercase ? 0x20 : 0);

            if (kc >= Keycode::Zero_CloseBracket && kc <= Keycode::Slash_QuestionMark)
                return (shift ? symbols_alt : symbols)[(u8) kc - (u8) Keycode::Zero_CloseBracket];

            if (kc == Keycode::Spacebar)
                return ' ';
            if (kc == Keycode::Escape)
                return 0x1B;
            if (kc == Keycode::Backspace)
                return '\b';
            if (kc == Keycode::Tab)
                return '\t';
            if (kc == Keycode::Enter)
                return '\n';
            if (kc == Keycode::Delete)
                return 0x7F;

            return 0;
        }

    }

}
