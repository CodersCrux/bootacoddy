#include "fs.hpp"

namespace bac::kernel::fs {

//    FileNode *root = 0;

    u32 read(FileNode *node, u32 offset, u32 size, u8 *buffer) {

        if (node->read != 0)
            return node->read(node, offset, size, buffer);
        else return 0;
    }

    u32 write(FileNode *node, u32 offset, u32 size, u8 *buffer) {

        if (node->write != 0)
            return node->write(node, offset, size, buffer);
        else return 0;
    }

    void open(FileNode *node, u8 read, u8 write) {

        if (node->open != 0)
            return node->open(node);
    }

    void close(FileNode *node) {

        if (node->close != 0)
            return node->close(node);
    }

    DirEntry *readdir(FileNode *node, u32 index) {

        if ((node->flags & 0x07) == FLAG_FS_DIRECTORY && node->readdir != 0)
            return node->readdir(node, index);
        else return 0;
    }

    FileNode *finddir(FileNode *node, char *name) {

        if ((node->flags & 0x07) == FLAG_FS_DIRECTORY && node->finddir != 0)
            return node->finddir(node, name);
        else return 0;

    }

}