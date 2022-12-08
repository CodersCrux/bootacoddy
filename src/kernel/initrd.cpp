#include "initrd.hpp"

namespace bac::kernel::initrd {

    BAFSHeader *bafs;
    fs::FileNode *root;

    fs::FileNode *nodes;
    u32 num_nodes;

    fs::DirEntry result_entry;

    u32 read(fs::FileNode *node, u32 offset, u32 size, u8 *buffer) {

        BAFSFileHeader file = bafs->files[node->inode];
        if (offset + size > file.size)
            size = file.size - offset;
        memory::memcpy(buffer, (u8 *) (file.address + offset), size);
        return size;
    }

    fs::DirEntry *readdir(fs::FileNode *node, u32 index) {

        if (index >= num_nodes)
            return 0;

        memory::strcpy(result_entry.name, nodes[index].name);
        result_entry.name[memory::strlen(nodes[index].name)] = 0;
        result_entry.ino = nodes[index].inode;
        return &result_entry;
    }

    fs::FileNode *finddir(fs::FileNode *node, char *name) {

        for (size_t i = 0; i < num_nodes; i++)
            if (memory::streq(name, nodes[i].name))
                return &nodes[i];
        return 0;
    }

    void init(u32 location) {

        bafs = (BAFSHeader *) location;

        root = (fs::FileNode *) paging::malloc(sizeof(fs::FileNode));
        memory::strcpy(root->name, "BOOTACODDY INITRD Filesystem");
        root->mask = root->uid = root->gid = root->inode = root->length = 0;
        root->flags = FLAG_FS_DIRECTORY;
        root->read = 0;
        root->write = 0;
        root->open = 0;
        root->close = 0;
        root->readdir = &readdir;
        root->finddir = &finddir;
        root->ptr = 0;
        root->impl = 0;

        // Allocate space for every file node
        num_nodes = bafs->num_files;
        nodes = (fs::FileNode *) paging::malloc(sizeof(fs::FileNode) * num_nodes);

        // Fill every node with the name, content and functions it needs
        for (size_t i = 0; i < num_nodes; i++) {

            bafs->files[i].address += location;
            memory::strcpy(nodes[i].name, bafs->files[i].name);
            nodes[i].length = bafs->files[i].size;
            nodes[i].mask = nodes[i].uid = nodes[i].gid = 0;
            nodes[i].inode = i;
            nodes[i].flags = FLAG_FS_FILE;
            nodes[i].read = &read;
            nodes[i].write = 0;
            nodes[i].readdir = 0;
            nodes[i].finddir = 0;
            nodes[i].open = 0;
            nodes[i].close = 0;
            nodes[i].impl = 0;
        }
    }

}