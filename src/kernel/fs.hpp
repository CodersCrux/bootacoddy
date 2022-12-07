#ifndef BOOTACODDY_KERNEL_FS_HPP
#define BOOTACODDY_KERNEL_FS_HPP

#include "../util/types.h"

#define FLAG_FS_FILE 0x01
#define FLAG_FS_DIRECTORY 0x02
#define FLAG_GS_CHARDEVICE 0x03
#define FLAG_FS_BLOCKDEVICE 0x04
#define FLAG_FS_PIPE 0x05
#define FLAG_FS_SYMLINK 0x06
#define FLAG_FS_MOUNTPOINT 0x08

namespace bac::kernel::fs {

    struct DirEntry {

        char name[128];
        u32 ino;
    };

    struct FileNode {

        typedef u32 (*ReadFunc)(FileNode *, u32, u32, u8 *);

        typedef u32 (*WriteFunc)(FileNode *, u32, u32, u8 *);

        typedef void (*OpenFunc)(FileNode *);

        typedef void (*CloseFunc)(FileNode *);

        typedef DirEntry *(*ReadDirFunc)(FileNode *, u32);

        typedef FileNode *(*FindDirFunc)(FileNode *, char *name);

        char name[128];
        u32 mask;
        u32 uid;
        u32 gid;
        u32 flags;
        u32 inode;
        u32 length;
        u32 impl;
        ReadFunc read;
        WriteFunc write;
        OpenFunc open;
        CloseFunc close;
        ReadDirFunc readdir;
        FindDirFunc finddir;
        FileNode *ptr;
    };

//    extern FileNode *root;

}

#endif
