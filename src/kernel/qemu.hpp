#ifndef BOOTACODDY_KERNEL_QEMU_HPP
#define BOOTACODDY_KERNEL_QEMU_HPP

#include "../util/ports.hpp"
#include "../util/types.h"
#include "../util/math.hpp"
#include "../util/stdarg.h"

namespace bac::kernel::qemu {

    void printc(char c);

    void prints(const char *s, u32 len);

    void prints(const char *s);

    void printi(i32 num);

    void printx(u32 hexnum);

    void print(const char *format, ...);

}

#endif