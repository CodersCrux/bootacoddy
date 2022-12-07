#ifndef BOOTACODDY_KERNEL_BAFS_HPP
#define BOOTACODDY_KERNEL_BAFS_HPP

#include "../util/types.h"

namespace bac::kernel::bafs {

    struct FileHeader {

        u32 address, length;
        u8 flags;
        char name[64];
    } __attribute__((packed));

    struct FileTable {

        u8 count;
        FileHeader files[16];
        FileTable *next, *last;
    } __attribute__((packed));

    struct FSHeader {

        u32 count, size;
        FileHeader *firstTable, *lastTable;
    } __attribute__((packed));

}

#endif
