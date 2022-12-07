#include "qemu.hpp"

namespace bac::kernel::qemu {

    void printc(char c) {
        ports::outb(0x3F8, c);
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

        num = math::abs(num);
        i32 den = math::pow(10, c - 1);
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