#ifndef BOOTACODDY_KERNEL_PAGING_HPP
#define BOOTACODDY_KERNEL_PAGING_HPP

#include "kernel/multiboot.hpp"
#include "util/types/list.hpp"

namespace bac::kernel::paging {

    struct PageMapping {
        u32 start, end;
        u32 virtualAddr;
    };

    extern types::List<PageMapping *> map;

    extern u32 dumb_placement;

    void *malloc(u32 size);

    void free(void *ptr);

    void *zalloc(size_t size);

    void init(multiboot *mb);

//    void map_page(u32 physicalAddress, u32 virtualAddress, u8 flags);

//    void map_table(u16 idx, u32 physicalAddress, u8 flags);

}

#endif
