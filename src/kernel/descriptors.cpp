
#include "descriptors.hpp"

extern "C" void gdt_flush(u32);
extern "C" void idt_flush(u32);

namespace bac::kernel::descriptors {

    using namespace memory;
    using namespace ports;

    GDTEntry gdt[5];
    TablePtr gdt_ptr;
    IDTEntry idt[256];
    TablePtr idt_ptr;

    static void gdt_set_gate(i32 num, u32 base, u32 limit, u8 access, u8 gran) {

        gdt[num].base_low = base & 0xFFFF;
        gdt[num].base_middle = (base >> 16) & 0xFF;
        gdt[num].base_high = (base >> 24) & 0xFF;

        gdt[num].limit_low = (limit & 0xFFFF);
        gdt[num].granularity = (limit >> 16) & 0x0F;

        gdt[num].granularity |= gran & 0xF0;
        gdt[num].access = access;
    }

    static void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags) {

        idt[num].base_low = base & 0xFFFF;
        idt[num].base_high = (base >> 16) & 0xFFFF;

        idt[num].sel = sel;
        idt[num].always0 = 0;

        idt[num].flags = flags;

    }

    static void init_gdt() {

        gdt_ptr.limit = (sizeof(GDTEntry) * 5) - 1;
        gdt_ptr.base  = (u32)&gdt;

        gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
        gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode types segment

        gdt_flush((u32)&gdt_ptr);

    }

    static void init_idt() {

        idt_ptr.limit = sizeof(IDTEntry) * 256 - 1;
        idt_ptr.base = (u32)&idt;

        memset((u8*)&idt, 0, sizeof(IDTEntry) * 256);

        idt_set_gate(0, (u32)isr0, 0x08, 0x8E);
        idt_set_gate(1, (u32)isr1, 0x08, 0x8E);
        idt_set_gate(2, (u32)isr2, 0x08, 0x8E);
        idt_set_gate(3, (u32)isr3, 0x08, 0x8E);
        idt_set_gate(4, (u32)isr4, 0x08, 0x8E);
        idt_set_gate(5, (u32)isr5, 0x08, 0x8E);
        idt_set_gate(6, (u32)isr6, 0x08, 0x8E);
        idt_set_gate(7, (u32)isr7, 0x08, 0x8E);
        idt_set_gate(8, (u32)isr8, 0x08, 0x8E);
        idt_set_gate(9, (u32)isr9, 0x08, 0x8E);
        idt_set_gate(10, (u32)isr10, 0x08, 0x8E);
        idt_set_gate(11, (u32)isr11, 0x08, 0x8E);
        idt_set_gate(12, (u32)isr12, 0x08, 0x8E);
        idt_set_gate(13, (u32)isr13, 0x08, 0x8E);
        idt_set_gate(14, (u32)isr14, 0x08, 0x8E);
        idt_set_gate(15, (u32)isr15, 0x08, 0x8E);
        idt_set_gate(16, (u32)isr16, 0x08, 0x8E);
        idt_set_gate(17, (u32)isr17, 0x08, 0x8E);
        idt_set_gate(18, (u32)isr18, 0x08, 0x8E);
        idt_set_gate(19, (u32)isr19, 0x08, 0x8E);
        idt_set_gate(20, (u32)isr20, 0x08, 0x8E);
        idt_set_gate(21, (u32)isr21, 0x08, 0x8E);
        idt_set_gate(22, (u32)isr22, 0x08, 0x8E);
        idt_set_gate(23, (u32)isr23, 0x08, 0x8E);
        idt_set_gate(24, (u32)isr24, 0x08, 0x8E);
        idt_set_gate(25, (u32)isr25, 0x08, 0x8E);
        idt_set_gate(26, (u32)isr26, 0x08, 0x8E);
        idt_set_gate(27, (u32)isr27, 0x08, 0x8E);
        idt_set_gate(28, (u32)isr28, 0x08, 0x8E);
        idt_set_gate(29, (u32)isr29, 0x08, 0x8E);
        idt_set_gate(30, (u32)isr30, 0x08, 0x8E);
        idt_set_gate(31, (u32)isr31, 0x08, 0x8E);

        outb(0x20, 0x11);
        outb(0xA0, 0x11);
        outb(0x21, 0x20);
        outb(0xA1, 0x28);
        outb(0x21, 0x04);
        outb(0xA1, 0x02);
        outb(0x21, 0x01);
        outb(0xA1, 0x01);
        outb(0x21, 0x0);
        outb(0xA1, 0x0);

        idt_set_gate(32, (u32)irq0, 0x08, 0x8E);
        idt_set_gate(33, (u32)irq1, 0x08, 0x8E);
        idt_set_gate(34, (u32)irq2, 0x08, 0x8E);
        idt_set_gate(35, (u32)irq3, 0x08, 0x8E);
        idt_set_gate(36, (u32)irq4, 0x08, 0x8E);
        idt_set_gate(37, (u32)irq5, 0x08, 0x8E);
        idt_set_gate(38, (u32)irq6, 0x08, 0x8E);
        idt_set_gate(39, (u32)irq7, 0x08, 0x8E);
        idt_set_gate(40, (u32)irq8, 0x08, 0x8E);
        idt_set_gate(41, (u32)irq9, 0x08, 0x8E);
        idt_set_gate(42, (u32)irq10, 0x08, 0x8E);
        idt_set_gate(43, (u32)irq11, 0x08, 0x8E);
        idt_set_gate(44, (u32)irq12, 0x08, 0x8E);
        idt_set_gate(45, (u32)irq13, 0x08, 0x8E);
        idt_set_gate(46, (u32)irq14, 0x08, 0x8E);
        idt_set_gate(47, (u32)irq15, 0x08, 0x8E);


        idt_flush((u32)&idt_ptr);

    }


    void init() {

        init_gdt();
        init_idt();

    }



}
