#ifndef BOOTACODDY_KERNEL_PCI_HPP
#define BOOTACODDY_KERNEL_PCI_HPP

#include "../../util/types.h"
#include "../../util/ports.hpp"
#include "../../kernel/kernel.hpp"
//#include "../../util/types/list.hpp"

#define PCI_MAX_BUSES 256

#define PCI_VALUE16_VendorID 0x0
#define PCI_VALUE16_DeviceID 0x2
#define PCI_VALUE16_Command 0x4
#define PCI_VALUE16_Status 0x6
#define PCI_VALUE8_RevisionID 0x8
#define PCI_VALUE8_ProgIF 0x9
#define PCI_VALUE8_Subclass 0xA
#define PCI_VALUE8_ClassCode 0xB
#define PCI_VALUE8_CacheLineSize 0xC
#define PCI_VALUE8_LatencyTimer 0xD
#define PCI_VALUE8_HeaderType 0xE
#define PCI_VALUE8_BIST 0xF


namespace bac::drivers::system::pci {

    struct PCIHeaderShared {

        u16 VendorID;
        u16 DeviceID;

        u16 Command;
        u16 Status;

        u8 RevisionID;
        u8 ProgIF;
        u8 Subclass;
        u8 ClassCode;

        u8 CacheLineSize;
        u8 LatencyTimer;
        u8 HeaderType;
        u8 BIST;
    };

    struct PCIHeader0 : public PCIHeaderShared {

        u32 BaseAddress0;
        u32 BaseAddress1;
        u32 BaseAddress2;
        u32 BaseAddress3;
        u32 BaseAddress4;
        u32 BaseAddress5;
        u32 CardbusCISPointer;

        u16 SubsystemVendorID;
        u16 SubsystemID;

        u32 ExpansionROMBaseAddress;

        u8 CapabilitiesPointer;
        u8 RSVD1[3];

        u32 RSVD2;

        u8 InterruptLine;
        u8 InterruptPIN;
        u8 MinGrant;
        u8 MaxLatency;
    };

    struct PCIHeader1 : public PCIHeaderShared {

        u32 BaseAddress0;
        u32 BaseAddress1;

        u8 PrimaryBusNumber;
        u8 SecondaryBusNumber;
        u8 SubordinateBusNumber;
        u8 SecondaryLatencyTimer;

        u8 IOBase;
        u8 IOLimit;
        u16 SecondaryStatus;

        u16 MemoryBase;
        u16 MemoryLimit;

        u16 PrefetchableMemoryBase;
        u16 PrefetchableMemoryLimit;

        u32 PrefetchableBaseUpper32Bits;
        u32 PrefetchableLimitUpper32Bits;

        u16 IOBaseUpper16Bits;
        u16 IOLimitUpper16Bits;

        u8 CapabilitiesPointer;
        u8 RSVD1[3];

        u32 ExpansionROMBaseAddress;

        u8 InterruptLine;
        u8 InterruptPIN;
        u16 BridgeControl;
    };

    struct PCIDevice {

        u32 PCIAddress;
        PCIHeaderShared *Header;
    };

    void init();

}

#endif