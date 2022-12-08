
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

struct BAFSFileHeader
{

    uint32_t size = 0;
    uint32_t address = 0;
    char name[64] {0};

} __attribute__((packed));

struct BAFSHeader
{

    uint32_t num_files = 0;

    BAFSFileHeader files[16];
} __attribute__((packed));

std::string dir = "../ramdisk";

std::string output = "../ramdisk.bafs";

int main()
{

    BAFSHeader fs;
    uint32_t offset = sizeof(BAFSHeader);

    std::cout << "Reading all files in " << dir << " ..." << std::endl;

    size_t count = std::distance(fs::directory_iterator(dir), fs::directory_iterator{});
    std::cout << count << " Files found." << std::endl;

    fs.num_files = count;

    size_t i = 0;
    for (auto &entry : fs::directory_iterator(dir))
    {

        std::ifstream file(entry.path(), std::ios::binary | std::ios::ate);
        std::cout << "Reading file " << entry.path().filename() << std::endl;

        if (!file)
        {
            std::cout << entry.path() << " Couldn't be read!" << std::endl;
            continue;
        }

        auto end = file.tellg();
        file.seekg(0, std::ios::beg);

        auto size = std::size_t(end - file.tellg());

        std::cout << "Size: " << size << std::endl;

        std::vector<std::byte> buffer(size);

        if (!file.read((char *)buffer.data(), buffer.size()))
        {
            std::cout << entry.path() << " Couldn't be read!" << std::endl;
            continue;
        }

        std::string name = entry.path().filename();

        strcpy(fs.files[i].name, name.c_str());
        fs.files[i].size = size;
        fs.files[i].address = offset;
        offset += size;

        file.close();

        i++;
    }

    std::ofstream outfile(output, std::ios::binary);
    outfile.write((const char *)&fs, sizeof(BAFSHeader));

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
