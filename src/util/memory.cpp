#include "memory.hpp"

namespace bac::memory {

    void memset(u8 *ptr, u8 value, size_t n) {

        while (n--)
            *(ptr++) = value;
    }

    void memcpy(u8 *dest, u8 *src, size_t n) {

        while (n--)
            *(dest++) = *(src++);
    }

    void memmove(u8 *dest, u8 *src, size_t n) {

        size_t i;
        u8 temp[n];
        for (i = 0; i < n; i++)
            temp[i] = src[i];
        for (i = 0; i < n; i++)
            dest[i] = temp[i];
    }

    size_t strlen(char *str) {

        size_t len = 0;
        while (*str++)
            len++;
        return len;
    }

    size_t strlen(char *str, size_t max) {

        size_t len = 0;
        while (*str++ && max--)
            len++;
        return len;
    }

    char *strcpy(char *dest, const char *src) {

        char *temp = dest;
        while ((*dest++ = *src++));
        return temp;
    }

    char *strcpy(char *dest, const char *src, size_t len) {

        char *temp = dest;
        while (len--)
            *dest++ = *src++;
        return temp;
    }

    bool streq(const char *str1, const char *str2) {

        while (*str1)
            if (*str1++ != *str2++)
                return false;
        return *str2 == 0;
    }

    bool streq(const char *str1, const char *str2, size_t len) {

        while (len--)
            if (*str1++ != *str2++)
                return false;
        return true;
    }

}
