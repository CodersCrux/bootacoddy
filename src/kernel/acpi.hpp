/*
 * RSDPtr setup, mainly to find the ACPI.
 * Refer to https://wiki.osdev.org/RSDP for explanation
 *
 *
 * I used this https://chromium.googlesource.com/chromiumos/third_party/coreboot/+/firmware-parrot-2685.B/src/arch/x86/include/arch/acpi.h
 * for help on the structure of SDT tables
 */


#ifndef BOOTACODDY_KERNEL_ACPI_HPP
#define BOOTACODDY_KERNEL_ACPI_HPP

#include "../util/types.h"
#include "../util/memory.hpp"
#include "kernel.hpp"

#define ACPI_TABLES 32

namespace bac::kernel::acpi {

    struct RSDPtr {

        char Signature[8];
        u8 Checksum;
        char OEMID[6];
        u8 Revision;
        u32 RSDTAddress;
    } __attribute__((packed));

    struct RSDPtr2 : public RSDPtr {

        u32 Length;
        u64 XSDTAddress;
        u8 ExtendedChecksum;
        u8 reserved[3];
    } __attribute__((packed));

    struct SDTHeader {

        char Signature[4];
        u32 Length;
        u8 Revision;
        u8 Checksum;
        char OEMID[6];
        char OEMTableID[8];
        u32 OEMRevision;
        u32 CreatorID;
        u32 CreatorRevision;

    } __attribute__((packed));

    struct RSDTable : public SDTHeader {
        u32 Entries[ACPI_TABLES];
    } __attribute__((packed));

    struct MADTable : public SDTHeader {

        u32 APICAddress;
        u32 Flags;
        // From now on, there's a list of record each prefixed by the MADTEntry
    } __attribute__((packed));

    struct MADTEntry {

        u8 EntryType;
        u8 RecordLength;
    } __attribute__((packed));

    struct MADTEntryProcessorAPIC : public MADTEntry {

        u8 ACPIProcessorID;
        u8 APIC_ID;
        u8 Flags;
    } __attribute__((packed));

    struct AddressStructure {

        u8 AddressSpaceID;
        u8 RegisterBitWidth;
        u8 RegisterBitOffset;
        u8 Reserved;
        u64 Address;
    } __attribute__((packed));

    struct HPETTable : public SDTHeader {

        u8 HardwareRevisionID;
        u8 ComparatorCount: 5,
                CounterSize: 1,
                Reserved: 1,
                LegacyReplacement: 1;
        u16 PCIVendorID;
        AddressStructure Address;
        u8 HPETNumber;
        u16 MinimalTick;
        u8 PageProtection;
    } __attribute__((packed));


    extern RSDPtr *RSDP;
    extern RSDTable *RSDT;
    extern MADTable *MADT;
    extern HPETTable *HPET;
    extern bool ACPI2;

    extern u32 NumRSDTEntries;

    extern u32 NumCores;
    extern u8 LocalAPIC_IDs[256];

    void init();

}


#endif