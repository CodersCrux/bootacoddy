#ifndef _BOOTACODDY_DRIVERS_INPUT_KEYBOARD_HPP
#define _BOOTACODDY_DRIVERS_INPUT_KEYBOARD_HPP

#include "../../util/types.h"
#include "../../kernel/interrupts.hpp"
#include "../../util/ports.hpp"
#include "../video/txt3.hpp"
//#include "util/types/list.hpp"

#define KEYBOARD_NUM_KEYS 105
#define KEYBOARD_INPUT_BUFFER_SIZE 32

namespace bac::drivers::input::keyboard {

    enum class Keycode {

        NULL = 0x0,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Zero_CloseBracket,
        One_ExclamationMark,
        Two_At,
        Three_Hash,
        Four_Dollar,
        Five_Percent,
        Six_Caret,
        Seven_Ampersand,
        Eight_Asterisk,
        Nine_OpenBracket,
        Dash_Underscore,
        Equal_Plus,
        OpenSquareBracket_OpenCurlyBracket,
        CloseSquareBracket_CloseCurlyBracket,
        Semicolon_Colon,
        Quote_DoubleQuote,
        Backtick_Tilde,
        Backslash_Pipe,
        Comma_LessThan,
        Dot_GreaterThan,
        Slash_QuestionMark,
        Spacebar,

        // Non-writable characters
        Escape,
        Backspace,
        Tab,
        Enter,
        LeftControl,
        LeftShift,
        RightShift,
        KeypadAsterisk,
        LeftAlt,
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
        Unlabeled,
        F11,
        F12 = 0x56,

        // Escape characters
        KeypadEnter, // 0x1C
        RightControl,
        KeypadSlash, // 0x35
        PrintScreen,
        RightAlt,
        Break, // 0x46
        Home,
        UpArrow,
        PageUp,
        LeftArrow, // 0x4B
        RightArrow, // 0x4D
        End, // 0x4F
        DownArrow,
        PageDown,
        Insert,
        Delete,
        LeftWindows, // 0x5B
        RightWindows,
        Menu,
    };

    typedef void (*KeyPressedEvent)(Keycode);

    typedef void (*KeyReleasedEvent)(Keycode);

    extern KeyPressedEvent onKeyPressed;
    extern KeyReleasedEvent onKeyReleased;

    void init();

    bool isKeyHeld(Keycode kc);

    bool isShift();

    bool isControl();

    bool isAlt();

    bool isUpArrow();

    bool isDownArrow();

    bool isRightArrow();

    bool isLeftArrow();

    bool isCapsLock();

    namespace text {

        char toAscii(Keycode kc);

        bool isSymbol(Keycode kc);

    }

}

#endif