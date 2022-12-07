#include "ports.hpp"

namespace bac::ports {

    void outb(u16 port, u8 value) {
        asm("outb %1, %0" : : "dN" (port), "a" (value));
    }

    u8 inb(u16 port) {

        u8 val;
        asm("inb %1, %0" : "=a" (val) : "dN" (port));
        return val;
    }

    void outw(u16 port, u16 value) {
        asm("outw %1, %0" : : "dN" (port), "a" (value));
    }

    u16 inw(u16 port) {

        u16 val;
        asm("inw %1, %0" : "=a" (val) : "dN" (port));
        return val;
    }

    void outl(u16 port, u32 value) {
        asm("outl %1, %0" : : "dN" (port), "a" (value));
    }

    u32 inl(u16 port) {

        u32 val;
        asm("inl %1, %0" : "=a" (val) : "dN" (port));
        return val;
    }

    void io_wait() {
        outb(0x80, 0);
    }
}
