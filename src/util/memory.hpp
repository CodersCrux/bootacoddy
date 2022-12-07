
#ifndef _BOOTACODDY_UTIL_MEMORY_H
#define _BOOTACODDY_UTIL_MEMORY_H

#include "util/types.h"

namespace bac::memory {

    void memset(u8 *ptr, u8 value, u32 n);

    void memcpy(u8 *dest, u8 *src, size_t n);

    void memmove(u8 *dest, u8 *src, size_t n);

    size_t strlen(char *str);

    size_t strlen(char *str, size_t max);

    char *strcpy(char *dest, const char *src);

    char *strcpy(char *dest, const char *src, size_t len);

    bool streq(const char *str1, const char *str2);

    bool streq(const char *str1, const char *str2, size_t len);

}


#endif