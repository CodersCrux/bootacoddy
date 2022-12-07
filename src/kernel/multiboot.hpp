#ifndef BOOTACODDY_KERNEL_MULTIBOOT_HPP
#define BOOTACODDY_KERNEL_MULTIBOOT_HPP

#include "../util/types.h"

#define MULTIBOOT_FLAG_MEM     0x001
#define MULTIBOOT_FLAG_DEVICE  0x002
#define MULTIBOOT_FLAG_CMDLINE 0x004
#define MULTIBOOT_FLAG_MODS    0x008
#define MULTIBOOT_FLAG_AOUT    0x010
#define MULTIBOOT_FLAG_ELF     0x020
#define MULTIBOOT_FLAG_MMAP    0x040
#define MULTIBOOT_FLAG_CONFIG  0x080
#define MULTIBOOT_FLAG_LOADER  0x100
#define MULTIBOOT_FLAG_APM     0x200
#define MULTIBOOT_FLAG_VBE     0x400

struct MultibootFramebuffer {

    u32 addr;
    u32 addr_high;
    u32 pitch;
    u32 width;
    u32 height;
    u8 bpp;
    u8 type;
    u8 color_info[5];
};

struct multiboot {

    u32 flags;
    u32 mem_lower;
    u32 mem_upper;
    u32 boot_device;
    u32 cmdline;
    u32 mods_count;
    u32 mods_addr;
    u32 num;
    u32 size;
    u32 addr;
    u32 shndx;
    u32 mmap_length;
    u32 mmap_addr;
    u32 drives_length;
    u32 drives_addr;
    u32 config_table;
    u32 boot_loader_name;
    u32 apm_table;
    u32 vbe_control_info;
    u32 vbe_mode_info;
    u16 vbe_mode;
    u16 vbe_interface_seg;
    u16 vbe_interface_off;
    u16 vbe_interface_len;

    MultibootFramebuffer fb;

};

struct VBEModeInfo {

    u16 attributes;
    u8 window_a;
    u8 window_b;
    u16 granularity;
    u16 window_size;
    u16 segment_a;
    u16 segment_b;
    u32 win_func_ptr;
    u16 pitch;
    u16 width;
    u16 height;
    u8 w_char;
    u8 y_char;
    u8 planes;
    u8 bpp;
    u8 banks;
    u8 memory_model;
    u8 bank_size;
    u8 image_pages;
    u8 reserved0;

    u8 red_mask;
    u8 red_position;
    u8 green_mask;
    u8 green_position;
    u8 blue_mask;
    u8 blue_position;
    u8 reserved_mask;
    u8 reserved_position;
    u8 direct_color_attributes;

    u32 framebuffer;
    u32 off_screen_mem_off;
    u16 off_screen_mem_size;
    u8 reserved1[206];
} __attribute__((packed));

struct MemoryMapEntry {

    u32 size;
    u32 addr;
    u32 addr_high;
    u32 len;
    u32 len_high;
    u32 type;
};

#endif

