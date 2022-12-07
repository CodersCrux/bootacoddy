#include "util/types.h"
#include "kernel/descriptors.hpp"
#include "kernel/interrupts.hpp"
#include "drivers/input/keyboard.hpp"
#include "kernel/multiboot.hpp"
//#include "kernel/fs.hpp"
//#include "kernel/initrd.hpp"
#include "drivers/video/lfb8.hpp"
#include "paging.hpp"
#include "qemu.hpp"
#include "gui/textscreen.hpp"
#include "acpi.hpp"
#include "drivers/system/pci.hpp"
#include "drivers/system/timer.hpp"
#include "vga.hpp"

using namespace bac;
using namespace bac::kernel;
using namespace bac::drivers::video;
using namespace bac::drivers::system;
using namespace bac::drivers::input;

namespace bac::kernel {

    gui::TextScreen *console;

    void panic(const char* msg, const char* file, u32 line) {

        asm("cli"); // Disable interrupts

        console->print("PANIC! (%s:%i) | %s", file, line, msg);

        // Freeze kernel indefinitely
        for (; ;);
    }

    void panic_assert(const char *file, u32 line, const char *desc) {

        asm("cli");

        console->print("ASSERT PANIC! (%s:%i) | %s", file, line, desc);

        for (; ;);
    }
}

size_t tick = 0;

namespace bac::programs::shell {

    extern int main();

}

extern u32 end;

cname void write_cr3(u32);
cname u32 read_cr3();
cname void write_cr0(u32);
cname u32 read_cr0();

cname int kernel_main(multiboot *mb) {

    // Set up our memory segments (GDT) and interrupt handling (IDT)
    descriptors::init();
    interrupts::init();

    // Set up our screen as soon as possible! Else, we can't display errors.
    lfb8::init(mb);
    gui::TextScreen _(0, 0, mb->fb.width, mb->fb.height, 4, 0x0F, 0x08, 1, 8, 8);
    console = &_;

    // Discover the ACPI tables ASAP, other drivers rely on them
    acpi::init();

    // Read PCI devices
    pci::init();

    // Enable timer
    timer::init(10'000);

    keyboard::init();

    // Enable paging, allowing us to divide and protect memory, as well as utilize it better
    paging::init(mb);

    asm("sti");

    programs::shell::main();

    bac::kernel::console->print("f");

    while (1);

    return 0xDEADBABA;
}

