#ifndef BOOTACODDY_UTIL_TYPES_STRING_HPP
#define BOOTACODDY_UTIL_TYPES_STRING_HPP

#include "../types.h"
#include "../memory.hpp"
#include "../../kernel/paging.hpp"

namespace bac::types {

    class String {
    public:

        String() {}

        String(char *str) { init(str); }

        String(char *str, size_t len) { init(str, len); }

        String &operator=(const char *str) {
            init((char *) str);
            return *this;
        }

        bool operator==(const char *other) {
            return memory::streq(str(), other);
        }

        bool operator==(String &other) {
            return memory::streq(str(), other.str());
        }

        char &operator[](size_t index) {

            if (_length < index)
                PANIC("Index bigger than string _length!");

            return data[index];
        }

        const char *str() {
            return (const char *) data;
        }

        size_t length() {
            return _length;
        }

//        List<String> split(char delim = ' ') {
//
//            List<String> args;
//
//            if (isEmpty())
//                return args;
//
//            u8 last = 0;
//            for (u8 i = 0; i < _length; i++) {
//
//                if (data[i] == delim) {
//
//                    args += String(&data[last], i - last);
//                    last = i + 1;
//                }
//            }
//
//            args += String(&data[last], _length - last);
//
//            return args;
//        }

        bool isEmpty() {
            return _length == 0 || data == 0 || *data == 0;
        }

        bool isDecimal() {

            if (_length == 0)
                return false;

            char *iter = data;
            if (*iter == '-')
                if (*iter++ == 0) // If there is ONLY a minus, it's not a number
                    return false;
            while (*iter) {
                if (*iter < '0' || *iter > '9')
                    return false;
                iter++;
            }
            return true;
        }

        int toInt() {

            if (isEmpty())
                PANIC("Empty string cannot be converted to int.");

            int res = 0, idx = 0, mult;

            if (data[0] == '-') {
                mult = -math::pow(10, _length - 2);
                idx = 1;
            } else mult = math::pow(10, _length - 1);

            while (mult) {

                if (data[idx] < '0' || data[idx] > '9')
                    PANIC("String cannot be converted to int.");

                res += (data[idx] - '0') * mult;
                idx++;
                mult /= 10;
            }

            return res;
        }

        ~String() {
            delete data;
        }

    private:
        size_t _length = 0;
        char *data = 0;

        void init(char *str) {
            init(str, memory::strlen(str));
        }

        void init(char *str, size_t len) {

            _length = len;
            delete data;
            data = (char *) kernel::paging::malloc(_length + 1);
            memory::strcpy(data, str);
            data[_length] = 0;
        }

    };

}


#endif