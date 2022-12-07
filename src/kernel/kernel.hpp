#ifndef BOOTACODDY_KERNEL_KERNEL_HPP
#define BOOTACODDY_KERNEL_KERNEL_HPP

#include "gui/textscreen.hpp"

#define PANIC(msg) bac::kernel::panic(msg, __FILE__, __LINE__)
#define ASSERT(b) ((b) ? (void)0 : bac::kernel::panic_assert(__FILE__, __LINE__, #b))

namespace bac::kernel {

    void panic(const char *msg, const char *file, u32 line);

    void panic_assert(const char *file, u32 line, const char *desc);

    extern gui::TextScreen *console;
}

#endif