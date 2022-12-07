#include "txt3.hpp"

namespace bac::drivers::video::txt3 {

    using namespace ports;
    using namespace math;

    u8 cursor_x, cursor_y;
    u16 entry;
    u16 *mem;

    void init(u8 color) {

        cursor_x = 0;
        cursor_y = 0;
        mem = (u16 *) 0xB8000;
        setcolor(color);
        setcursor(0, 0);
        showcursor(13, 14);
    }

    void clear() {

        for (u16 i = 0; i < 80 * 25; i++)
            mem[i] = entry;
    }

    void setcolor(u8 color) {
        entry = (u16) color << 8;
    }

    void refresh() {

        u8 *cols = (u8 *) mem;
        u8 col = (u8) (entry >> 8);
        for (u16 i = 1; i < 80 * 25 * 2; i += 2)
            cols[i] = col;
    }

    void showcursor(u8 start, u8 end) {

        outb(0x3D4, 0x0A);
        outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

        outb(0x3D4, 0x0B);
        outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
    }

    void hidecursor() {

        outb(0x3D4, 0x0A);
        outb(0x3D5, 0x20);
    }

    CursorPos getcursor() {
        return {cursor_x, cursor_y};
    }

    u16 getcursorIdx() {
        return cursor_x + cursor_y * 80;
    }

    // Private function, doesn't exist in header
    void updatecursor(u8 x, u8 y) {

        u16 pos = x + y * 80;

        outb(0x3D4, 0x0F);
        outb(0x3D5, (u8) (pos & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (u8) ((pos >> 8) & 0xFF));
    }

    void setcursor(u16 idx) {

        cursor_x = idx % 80;
        cursor_y = idx / 80;
        updatecursor(cursor_x, cursor_y);
    }

    void setcursor(u8 x, u8 y) {

        cursor_x = x;
        cursor_y = y;
        updatecursor(x, y);
    }

    void scroll(u8 lines) {

        memory::memcpy((u8 *) mem, (u8 *) mem + 80 * 2, 80 * 24 * 2);

        memory::memset((u8 *) mem + 80 * 24 * 2, entry, 80 * 2);
    }


    void newline() {

        cursor_x = 0;
        if (++cursor_y >= 25) {
            scroll(1);
            cursor_y--;
        }
        updatecursor(cursor_x, cursor_y);
    }

    u16 get(u16 idx) {
        return mem[idx];
    }

    u16 get(u8 x, u8 y) {
        return mem[x + y * 80];
    }

    void plot(char c) {
        mem[cursor_x + cursor_y * 80] = entry | c;
    }

    void plot(u16 idx, char c) {
        mem[idx] = entry | c;
    }

    void plot(u8 x, u8 y, char c) {
        mem[x + y * 80] = entry | c;
    }

    void printc(char c) {

        if (c == '\n') // Enter
            newline();
        else {

            mem[cursor_x + cursor_y * 80] = entry | c;
            if (++cursor_x >= 80)
                newline();
        }

        updatecursor(cursor_x, cursor_y);
    }

    void prints(const char *s, u32 len) {

        while (len--)
            printc(*s++);
    }

    void prints(const char *s) {

        while (*s)
            printc(*s++);
    }


    void printi(i32 num) {

        if (num < 0)
            printc('-');
        else if (num == 0) {
            printc('0');
            return;
        }

        i32 iter = num;
        u8 c = 0;
        while (iter) {
            c++;
            iter /= 10;
        }

        num = abs(num);
        i32 den = pow(10, c - 1);
        while (c--) {
            printc('0' + (num / den));
            num = num % den;
            den /= 10;
        }

    }

    void printx(u32 hexnum) {

        prints("0x");

        bool printed = false;

        for (u8 i = 0; i < 4; i++) {
            u8 n = hexnum >> 24;

            if (n || printed) {

                u8 high = n >> 4, low = n & 0x0F;
                printc(high < 10 ? '0' + high : 'A' - 10 + high);
                printc(low < 10 ? '0' + low : 'A' - 10 + low);
                printed = true;
            }
            hexnum <<= 8;
        }

        if (!printed)
            prints("00");
    }

    void print(const char *format, ...) {

        va_list lst;
        va_start(lst, format);

        bool typeinsert = false;

        while (*format) {

            if (*format == '%') {
                format++;
                typeinsert = true;
                continue;
            }

            if (typeinsert) {
                typeinsert = false;

                switch (*format) {

                    case 's':
                        prints(va_arg(lst, char*));
                        break;
                    case 'd':
                    case 'i':
                        printi(va_arg(lst, i32));
                        break;
                    case 'x':
                        printx(va_arg(lst, u32));

                }
            } else printc(*format);

            format++;
        }

    }


}

