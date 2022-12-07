#ifndef _BOOTACODDY_DRIVERS_TXT3_HPP
#define _BOOTACODDY_DRIVERS_TXT3_HPP

#include "util/types.h"
#include "util/stdarg.h"
#include "util/ports.hpp"
#include "util/math.hpp"
#include "util/memory.hpp"

namespace bac::drivers::video::txt3 {

    struct CursorPos {
        u8 x, y;
    };

    extern u16 *mem;

    /**
     * @brief Initializes TXT3 video driver.
     * 
     * @param color initial terminal color
     */
    void init(u8 color = 0x07);


    /**
     * @brief Wipes the screen to blank with screen color
     */
    void clear();


    /**
     * @brief Sets the terminal color.
     * NOTE: Only applies to characters written afterwards.
     * To refresh the screen with new colors, use refresh().
     * 
     * @param color Colorf to be set
     */
    void setcolor(u8 color);


    /**
     * @brief Updates the terminal colors to be the currently set one.
     */
    void refresh();

    /**
     * @brief Shows hardware cursor, as well as setting it's start and end.
     * The start and end depict the top/bottom span of the cursor across a text cell.
     * The cursor is horizontal only.
     * 
     * @param start cursor start
     * @param end cursor end
     */
    void showcursor(u8 start, u8 end);

    /**
     * @brief Hides the cursor. nothing to it.
     */
    void hidecursor();

    void setcursor(u16 idx);

    /**
     * @brief Sets hardware cursor position. Useful for writing "floating" text which doesn't follow
     * the current text stream.
     * 
     * @param x 
     * @param y 
     */
    void setcursor(u8 x, u8 y);

    /**
     * @brief Returns cursor position as a struct.
     * 
     */
    CursorPos getcursor();

    u16 getcursorIdx();


    void scroll(u8 lines);

    /**
     * @brief Goes down a line.
     * Same as printing '\\n'.
     * If the cursor's at the last row, the entire console will be scrolled, and the top row
     * will be discarded.
     * 
     */
    void newline();

    u16 get(u16 idx);

    u16 get(u8 x, u8 y);

    /**
     * @brief Places a character at the cursor position without advancing the cursor.
     * @param c Character
     */
//    void plot(char c);

    void plot(u16 idx, char c);

    /**
     * @brief Places a character at the specified x, y position
     * @param x X position (maximum 79 inc.)
     * @param y Y position (maximum 24 inc.)
     * @param c Character
     */
    void plot(u8 x, u8 y, char c);

    /**
     * @brief Prints a character.
     * 
     * @param c character
     */
    void printc(char c);

    /**
     * @brief Prints a decimal int32.
     * 
     * @param num int32
     */
    void printi(i32 num);

    /**
     * @brief Prints a hexadecimal int32.
     * 
     * @param hexnum int32
     */
    void printx(u32 hexnum);

    /**
     * @brief Prints a null-terminated string of characters.
     * 
     * @param s string
     */
    void prints(const char *s);

    /**
     * @brief Prints a string of characters until the _length specified.
     * 
     * @param s string
     * @param len _length
     */
    void prints(const char *s, u32 len);

    /**
     * @brief Prints a formatted string similar to C's printf().\n
     * '%i': Print int32.\n
     * '%x': Print int32 as hexadecimal.\n
     * '%s': Print string.\n
     * 
     * @param format string with formatting
     * @param ... variable args
     */
    void print(const char *format, ...);


}


#endif