
#include "interrupts.hpp"
#include "qemu.hpp"

namespace bac::kernel::interrupts {

    using namespace ports;

    ISR handlers[256];

    void init() {

        outb(PORT_PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
        io_wait();
        outb(PORT_PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
        io_wait();
        outb(PORT_PIC1_DATA, 0x20);
        io_wait();
        outb(PORT_PIC2_DATA, 0x28);
        io_wait();
        outb(PORT_PIC1_DATA, 4);
        io_wait();
        outb(PORT_PIC2_DATA, 2);
        io_wait();

        outb(PORT_PIC1_DATA, ICW4_8086);
        io_wait();
        outb(PORT_PIC2_DATA, ICW4_8086);
        io_wait();

        outb(PORT_PIC1_DATA, 0x0);
        outb(PORT_PIC2_DATA, 0x0);
    }



    void install_handler(u8 n, ISR handler) {
        handlers[n] = handler;
    }


    cname void isr_handler(Registers regs) {

        qemu::print("ISR %i\n", regs.int_no);

        if (handlers[regs.int_no] != 0)
            handlers[regs.int_no](regs);

    }

    cname void irq_handler(Registers regs) {

        if (regs.int_no >= 40)
            outb(0xA0, 0x20);
        
        outb(0x20, 0x20);

        if (handlers[regs.int_no] != 0) {

            ISR handler = handlers[regs.int_no];
            handler(regs);
        }

    }
}