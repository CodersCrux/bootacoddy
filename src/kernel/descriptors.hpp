#ifndef _BOOTACODDY_KERNEL_DESCRIPTORS_HPP
#define _BOOTACODDY_KERNEL_DESCRIPTORS_HPP

#include "util/types.h"
#include "util/memory.hpp"
#include "util/ports.hpp"

namespace bac::kernel::descriptors {


    typedef struct GDTEntry {

        u16 limit_low;
        u16 base_low;
        u8 base_middle;
        u8 access;
        u8 granularity;
        u8 base_high;
    } __attribute__((packed)) GDTEntry;

    typedef struct IDTEntry {
        
        u16 base_low;
        u16 sel;
        u8 always0;
        u8 flags;
        u16 base_high;
    } __attribute__((packed)) IDTEntry;

    typedef struct TablePtr {

        u16 limit;
        u32 base;
    } __attribute__((packed)) TablePtr;


    void init();


    extern "C" void isr0();
    extern "C" void isr1();
    extern "C" void isr2();
    extern "C" void isr3();
    extern "C" void isr4();
    extern "C" void isr5();
    extern "C" void isr6();
    extern "C" void isr7();
    extern "C" void isr8();
    extern "C" void isr9();
    extern "C" void isr10();
    extern "C" void isr11();
    extern "C" void isr12();
    extern "C" void isr13();
    extern "C" void isr14();
    extern "C" void isr15();
    extern "C" void isr16();
    extern "C" void isr17();
    extern "C" void isr18();
    extern "C" void isr19();
    extern "C" void isr20();
    extern "C" void isr21();
    extern "C" void isr22();
    extern "C" void isr23();
    extern "C" void isr24();
    extern "C" void isr25();
    extern "C" void isr26();
    extern "C" void isr27();
    extern "C" void isr28();
    extern "C" void isr29();
    extern "C" void isr30();
    extern "C" void isr31();
    extern "C" void irq0();
    extern "C" void irq1();
    extern "C" void irq2();
    extern "C" void irq3();
    extern "C" void irq4();
    extern "C" void irq5();
    extern "C" void irq6();
    extern "C" void irq7();
    extern "C" void irq8();
    extern "C" void irq9();
    extern "C" void irq10();
    extern "C" void irq11();
    extern "C" void irq12();
    extern "C" void irq13();
    extern "C" void irq14();
    extern "C" void irq15();


}

#endif