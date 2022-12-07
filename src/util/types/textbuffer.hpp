#ifndef BOOTACODDY_UTIL_TYPES_TEXTBUFFER_HPP
#define BOOTACODDY_UTIL_TYPES_TEXTBUFFER_HPP

#include "../types.h"
#include "../memory.hpp"
#include "../math.hpp"
#include "../stdarg.h"
#include "../../kernel/qemu.hpp"

namespace bac::kernel::paging {
    void *zalloc(size_t size);
}

namespace bac::types {

    using namespace bac::kernel;

    class TextBuffer {
    public:

        bool insertMode = false;

        TextBuffer(size_t size)
                : SIZE(size), CURSOR(0), length(0),
                  data((char *) paging::zalloc(size)) {}


        void carriage() {

            while (CURSOR && data[CURSOR - 1] != '\n')
                CURSOR--;
        }

        void printc(char c) {

            if (length >= SIZE)
                return;

            if (c == '\r')
                carriage();
            else {

                // TODO: Maybe scroll, or do something besides ignoring input
                if (CURSOR >= SIZE - 1 || length >= SIZE)
                    return;

                if (insertMode) {

                    data[CURSOR] = c;
                    if (CURSOR++ == length)
                        length++;

                    placeChar(c, CURSOR);


                } else {

                    memory::memmove((u8 * ) & data[CURSOR + 1], (u8 * ) & data[CURSOR], length - CURSOR);
                    data[CURSOR] = c;
                    length++;
                    updateForwards(CURSOR);
                    CURSOR++;
                }

                qemu::prints(data, length);
                qemu::printc('\n');

            }
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
                num %= den;
                den /= 10;
            }
        }

        void printx(u32 hex) {

            prints("0x");
            bool printed = false;

            for (u8 i = 0; i < 4; i++) {

                u8 n = hex >> 24;

                if (n || printed) {

                    u8 high = n >> 4, low = n & 0x0F;
                    printc(high < 10 ? '0' + high : 'A' - 10 + high);
                    printc(low < 10 ? '0' + low : 'A' - 10 + low);
                    printed = true;
                }
                hex <<= 8;
            }

            if (!printed)
                prints("00");
        }

        void print(const char *format, ...) {

            va_list lst;
            va_start(lst, format);

            bool type = false;

            while (*format) {

                if (*format == '%') {
                    type = true;
                    format++;
                    continue;
                }

                if (type) {
                    type = false;

                    switch (*format) {

                        case 's':
                            prints(va_arg(lst, char*));
                            break;
                        case 'i':
                        case 'd':
                            printi(va_arg(lst, i32));
                            break;
                        case 'x':
                            printx(va_arg(lst, u32));
                            break;

//                        case 'l':
//                            format++;
//                            switch (*format) {
//
//                                case 'i':
//                                case 'd':
//                                    print
//
//                            }

                        case '%':
                            printc('%');
                            break;

                    }
                } else printc(*format);

                format++;
            }
        }

        /**
         * @brief Backspaces a character from the current cursor.
         * Returns false if nothing changed, true if a character was deleted.
         * @return
         */
        bool backspace() {

            if (length == 0 || CURSOR == 0)
                return false;

            memory::memmove((u8 * ) & data[CURSOR], (u8 * ) & data[CURSOR + 1], length - CURSOR);
            data[--length] = 0;
            updateForwards(--CURSOR);

            qemu::print("%s\n", data);

            return true;
        }

    protected:
        size_t CURSOR;
        const size_t SIZE;

        /**
         * @brief An event requiring the tool to place 'ch' at the specified 'curs'.
         * @param ch
         * @param curs
         */
        virtual void placeChar(char ch, size_t curs) {}

        /**
         * @brief An event requiring the tool to simply update all characters following 'curs'.
         * @param curs
         */
        virtual void updateForwards(size_t curs) {}

        char *data;
        size_t length;

    };

}


#endif