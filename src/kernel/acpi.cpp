#include "acpi.hpp"

namespace bac::kernel::acpi {

    RSDPtr *RSDP = 0;
    RSDTable *RSDT = 0;
    MADTable *MADT = 0;
    HPETTable *HPET = 0;
    bool ACPI2;

    u32 NumRSDTEntries = 0;

    u32 NumCores = 0;
    u8 LocalAPIC_IDs[256] = {0};

    void init() {


        /*
         * The RSD Pointer can be loaded into memory at range 0x000E0000 to 0x000FFFFF.
         * It begins with an 8 byte signature of "RSD PTR ", and that's what this loop is looking for.
         * The Root System Description Table holds a LOT of useful data supplied by the BIOS.
         * Mainly, I can use it to find how many cores the CPU has.
         */
        const char *rsdptr = "RSD PTR ";
        for (size_t i = 0xE0000; i < 0xFFFFF; i++)
            if (memory::streq((const char *) i, rsdptr, 8))
                RSDP = (RSDPtr *) i;

        if (RSDP == 0)
            PANIC("RSDPtr could not be found!");

        // Make sure the version 1 RSDPtr is valid
        u8 sum = 0;
        for (size_t i = 0; i < sizeof(RSDPtr); i++)
            sum += ((u8 *) RSDP)[i];

        // If the sum's lowest byte isn't zero, invalid RSDPtr
        if (sum)
            PANIC("RSDPtr has an invalid checksum.");

        ACPI2 = RSDP->Revision != 0;

        if (ACPI2) {

            sum = 0;
            for (size_t i = 0; i < sizeof(RSDPtr2); i++)
                sum += ((u8 *) RSDP)[i];

            if (sum & 0xFF)
                PANIC("RSDPtr 2 has an invalid checksum.");
        }


        RSDT = (RSDTable *) RSDP->RSDTAddress;
        NumRSDTEntries = (RSDT->Length - sizeof(SDTHeader)) / 4;

        // Enumerate available tables
        for (u32 i = 0; i < NumRSDTEntries; i++) {

            SDTHeader *header = (SDTHeader *) RSDT->Entries[i];

            if (MADT == 0 && memory::streq("APIC", header->Signature, 4))
                MADT = (MADTable *) header;
            if (HPET == 0 && memory::streq("HPET", header->Signature, 4))
                HPET = (HPETTable *) header;
        }

        // Run through the MADT, checking for available CPU cores
        if (!MADT)
            PANIC("MADT Not found! (The MADT is a table displaying how many logical cores we have)");

        u8 *madtPtr = (u8 *) MADT + sizeof(MADTable);
        u8 *end = (u8 *) MADT + MADT->Length;

        while (madtPtr < end) {

            MADTEntry *entry = (MADTEntry *) madtPtr;

            // For now, I only check for cores and not APICs since I don't really use them
            switch (entry->EntryType) {

                case 0: // Logical Processor
                    MADTEntryProcessorAPIC *proc = (MADTEntryProcessorAPIC *) entry;
                    if (proc->Flags & 1)
                        LocalAPIC_IDs[NumCores++] = proc->APIC_ID;
                    break;
                    // Rest to be added at some point or never
            }

            madtPtr += entry->RecordLength;
        }
    }

}