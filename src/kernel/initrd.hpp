#ifndef BOOTACODDY_KERNEL_INITRD_HPP
#define BOOTACODDY_KERNEL_INITRD_HPP

#include "../util/types.h"
#include "../kernel/fs.hpp"
#include "../util/memory.hpp"
#include "../kernel/paging.hpp"

namespace bac::kernel::initrd {

    struct BAFSFileHeader {

        u32 size;
        u32 address;
        char name[64];
    };

    struct BAFSHeader {

       u32 num_files = 0;
       BAFSFileHeader files[16];
    };

    extern fs::FileNode *root;

    void init(u32 location);

    u32 read(fs::FileNode *node, u32 offset, u32 size, u8 *buffer);

    fs::DirEntry *readdir(fs::FileNode *node, u32 index);

    fs::FileNode *finddir(fs::FileNode *node, char *name);



}

#endif