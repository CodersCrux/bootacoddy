#ifndef _BOOTACODDY_UTIL_PORTS_H
#define _BOOTACODDY_UTIL_PORTS_H

#include "util/types.h"

#ifndef asm
#define asm __asm__ volatile
#endif

#define PORT_PIC1_COMMAND 0x20
#define PORT_PIC1_DATA 0x21
#define PORT_PIC2_COMMAND 0xA0
#define PORT_PIC2_DATA 0xA1

#define ICW1_ICW4    0x01        /* ICW4 (not) needed */
#define ICW1_SINGLE    0x02        /* Single (cascade) mode */
#define ICW1_INTERVAL4    0x04        /* Call address interval 4 (8) */
#define ICW1_LEVEL    0x08        /* Level triggered (edge) mode */
#define ICW1_INIT    0x10        /* Initialization - required! */

#define ICW4_8086    0x01        /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO    0x02        /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE    0x08        /* Buffered mode/slave */
#define ICW4_BUF_MASTER    0x0C        /* Buffered mode/master */
#define ICW4_SFNM    0x10        /* Special fully nested (not) */

#define PORT_PS2_DATA 0x60
#define PORT_PS2_STATUS 0x64
#define PORT_PS2_COMMAND 0x64

#define PORT_PCI_CONFIG_ADDRESS 0xCF8
#define PORT_PCI_CONFIG_DATA 0xCFC

namespace bac::ports {

    void outb(u16 port, u8 value);

    u8 inb(u16 port);

    void outw(u16 port, u16 value);

    u16 inw(u16 port);

    /**
     * @brief Executes a pointless IO function, generally taking 1-4 microseconds.
     * Useful for having a small delay between IO instructions on older hardware
     *
     */
    void io_wait();

    void outl(u16 port, u32 value);

    u32 inl(u16 port);

}


#endif
