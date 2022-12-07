
#include <iostream>
#include <filesystem>
#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include <stdint.h>
#include <cstring>
#include <sstream>

namespace fs = std::filesystem;

typedef uint32_t u32;
typedef uint8_t u8;


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

std::string output = "test.bafs";

int main()
{

    FSHeader bafs;
    bafs.count = 1;

    FileHeader file;
    file.length = 10;
    file.flags = 0xFF;
    strcpy(file.name, "iamafile.txt");
    file.address = sizeof(FSHeader) + sizeof(FileHeader);

    FileTable table;
    table.count = 1;
    memcpy(&table.files[0], &file, sizeof(FileHeader));


    std::ofstream outfile(output, std::ios::binary);
    outfile.write();

    i = 0;
    for (auto &entry : fs::directory_iterator(dir))
    {

        std::ifstream file(entry.path(), std::ios::binary);
        std::stringstream ss;
        ss << file.rdbuf();

        outfile.write(ss.str().c_str(), fs.files[i].size);

        file.close();
        i++;
    }

    outfile.close();
    return 0;
}
