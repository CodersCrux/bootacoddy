#include "paging.hpp"
#include "kernel/kernel.hpp"
#include "kernel/interrupts.hpp"
#include "util/types.h"
#include "qemu.hpp"

void *operator new(size_t size) {
    return bac::kernel::paging::malloc(size);
}

void operator delete(void *ptr, size_t size) {
    bac::kernel::paging::free(ptr);
}

extern u32 end;

cname void write_cr3(u32);
cname u32 read_cr3();
cname void write_cr0(u32);
cname u32 read_cr0();

#define TABLE_MEMORY_ZONE 0x400000

namespace bac::drivers::video::lfb8 {
    extern size_t ADDR;
}

namespace bac::kernel::paging {

    types::List<PageMapping *> map;

    u32 **directory;
    u32 *tables[1024];

    u32 *frame_bitmap;
    u32 num_frames;
    u32 first_free_frame = 0;

    u64 TOTAL_MEMORY_U64 = 0;

    u32 dumb_placement;

    void *malloc(size_t size) {

        if (0x400000 - dumb_placement < size)
            PANIC("OUT OF MEMORY, DUMB MALLOC REACHED 4MiB MARK! ono thas not good");

        u32 ret = dumb_placement;
        dumb_placement += size;

        return (void *) ret;
    }

    void free(void *ptr) {
        // TODO: MAKE A GOSH DARN HEAP
    }

    void *zalloc(size_t size) {

        void *res = malloc(size);
        memory::memset((u8 *) res, 0, size);
        return res;
    }

    void page_fault(interrupts::Registers regs) {

        PANIC("YOUR FAULT");

    }

    void set_frame(u32 addr) {
        addr /= 0x1000;
        frame_bitmap[addr / 32] |= (1 << (addr % 32));
    }

    void clear_frame(u32 addr) {
        addr /= 0x1000;
        frame_bitmap[addr / 32] &= -(1 << (addr % 32));
    }

    void map_page(u32 physicalAddress, u32 virtualAddress, u8 flags) {

        physicalAddress &= 0xFFFFF000;

        u32 page_addr = virtualAddress / 0x1000;
        tables[page_addr / 1024][page_addr % 1024] = physicalAddress | flags;

        if (flags & 1)
            set_frame(physicalAddress);
        else clear_frame(physicalAddress);
    }

    void map_table(u16 idx, u32 physicalAddress, u8 flags) {

        physicalAddress &= 0xFFFFF000;

        // Map all physical pages taken in our frame bitmap
        if (physicalAddress < TOTAL_MEMORY_U64)
            for (size_t i = physicalAddress / 0x20000; i < physicalAddress / 0x20000 + 32; i++) {
                if (i * 0x20000 > TOTAL_MEMORY_U64)
                    break;
                frame_bitmap[i] = 0xFFFFFFFF;
            }

        for (size_t i = 0; i < 1024; i++, physicalAddress += 0x1000)
            tables[idx][i] = physicalAddress | flags;
        directory[idx] = (u32 *) ((u32) directory[idx] | flags);
    }

    u32 first_frame() {

        for (u32 i = 0, j, block; i < num_frames / 32; i++) {

            block = frame_bitmap[i];
            // Whole frame block already taken, skip
            if (block == 0xFFFFFFFF)
                continue;

            for (j = 0; j < 32; j++, block >>= 1)
                if (!(block & 1)) // This frame is free
                    return i * 32 + j;
        }

        return 0;
    }

    u32 alloc_page() {
        return 0;
    }

    void init(multiboot *mb) {

        {
            if ((u32) &end > 0x400000) // Our kernel took too much memory!
                PANIC("Kernel memory has exceeded 4MiB!");

            if (!(mb->flags >> 6 & 1)) {
                PANIC("Invalid memory map from GRUB!");
            }

            TOTAL_MEMORY_U64 = 0;

            for (size_t i = 0; i < mb->mmap_length; i += sizeof(MemoryMapEntry)) {

                MemoryMapEntry *entry = (MemoryMapEntry *) (mb->mmap_addr + i);

                if (0x100000000 - TOTAL_MEMORY_U64 >= entry->len)
                    TOTAL_MEMORY_U64 += entry->len;
                else TOTAL_MEMORY_U64 = 0x100000000;
            }

            if ((TOTAL_MEMORY_U64 & 0x10000) > 0)
                TOTAL_MEMORY_U64 += 0x10000 - (TOTAL_MEMORY_U64 & 0xFFFF);

            if (TOTAL_MEMORY_U64 < 0x1000000) // Kernel must have at least 16MB
                PANIC("Kernel must have at least 16MiB of memory!");

        }

//        console->print("Total mem: %x\n", (u32) TOTAL_MEMORY_U64);

        // Place our dumb memory allocation at the end of the kernel
        dumb_placement = (u32) &end;

        num_frames = TOTAL_MEMORY_U64 / 0x1000;
        frame_bitmap = (u32 *) zalloc(num_frames / 8);

//        console->print("size: %i\n", num_frames / 8);

        // Directory is placed in a general free space
        directory = (u32 **) 0x9C000;

        // Set up every page table's address
        for (size_t i = 0; i < 1024; i++) {
            tables[i] = (u32 *) TABLE_MEMORY_ZONE + i * 0x1000;
            directory[i] = (u32 *) ((u32) tables[i] | 0b010);
        }

        for (PageMapping *pm : map) {

            for (size_t addr = 0; addr < (pm->end - pm->start); addr += 0x1000)
                map_page(pm->start + addr, pm->virtualAddr + addr, 0b011);
        }

        // Map first four megabytes of our kernel
        map_table(0, 0, 0b011);
        map_table(1, TABLE_MEMORY_ZONE, 0b011);
        map_table(2, mb->fb.addr, 0b011);

        interrupts::install_handler(14, page_fault);

        // Enable paging
        write_cr3((u32) directory);
        write_cr0(read_cr0() | 0x80000000);

        drivers::video::lfb8::ADDR = 0x800000;

    }

}

