#include "pci.hpp"
#include "util/types/dictionary.hpp"

namespace bac::drivers::system::pci {

    namespace names {

        const char *sub_unclass[]{
                "Non-VGA-Compatible Unclassified Device",
                "VGA-Compatible Unclassified Device"
        };

        const char *sub_mcs[]{
                "SCSI Bus Controller",
                "IDE Controller",
                "Floppy Disk Controller",
                "IPI Bus Controller",
                "RAID Controller",
                "ATA Controller",
                "Serial ATA Controller",
                "Serial Attached SCSI Controller",
                "Non-Volatile Memory Controller"
        };

        const char *sub_net[]{
                "Ethernet Controller",
                "Token Ring Controller",
                "FDDI Controller",
                "ATM Controller",
                "ISDN Controller",
                "WorldFip Controller",
                "PICMG 2.14 Multi Computing Controller",
                "Infiniband Controller",
                "Fabric Controller"
        };

        const char *sub_disp[]{
                "VGA Compatible Controller",
                "XGA Controller",
                "3D Controller (Not VGA-Compatible)"
        };

        const char *sub_multi[]{
                "Multimedia Video Controller",
                "Multimedia Audio Controller",
                "Computer Telephony Device",
                "Audio Device"
        };

        const char *sub_mem[]{
                "RAM Controller",
                "Flash Controller"
        };

        const char *sub_bridge[]{
                "Host Bridge",
                "ISA Bridge",
                "EISA Bridge",
                "MCA Bridge",
                "PCI-to-PCI Bridge",
                "PCMCIA Bridge",
                "NuBus Bridge",
                "CardBus Bridge",
                "RACEway Bridge",
                "PCI-to-PCI Bridge",
                "Infiniband-to-PCI Host Bridge"
        };

        const char *sub_scc[]{
                "Serial Controller",
                "Parallel Controller",
                "Multiport Serial Controller",
                "Modem",
                "IEEE 488.1/2 (GPIB) Controller",
                "Smart Card Controller"
        };

        const char *sub_bsp[]{
                "PIC",
                "DMA Controller",
                "Timer",
                "RTC Controller",
                "PCI Hot-Plug Controller",
                "SD Host Controller",
                "IOMMU"
        };

        const char *sub_idc[]{
                "Keyboard Controller",
                "Digitizer Pen",
                "Mouse Controller",
                "Scanner Controller",
                "Gameport Controller"
        };

        const char *sub_dock[]{
                "Generic"
        };

        const char *sub_proc[]{
                "386",
                "486",
                "Pentium",
                "Pentium Pro",
                "Alpha",
                "PowerPC",
                "MIPS",
                "Co-Processor"
        };

        const char *sub_sbc[]{
                "FireWire (IEEE 1394) Controller",
                "ACCESS Bus Controller",
                "SSA",
                "USB Controller",
                "Fibre Channel",
                "SMBus Controller",
                "Infiniband Controller",
                "IPMI Interface",
                "SERCOS Interface (IEC 61491)",
                "CANbus Controller"
        };

        const char *sub_wire[]{
                "IRDA Compatible Controller",
                "Consumer IR Controller",
                "RF Controller",
                "Bluetooth Controller",
                "Broadband Controller",
                "Ethernet Controller (802.1a)",
                "Ethernet Controller (802.1b)"
        };

        const char *Classes[]{
                "Unclassified",
                "Mass Storage Controller",
                "Network Controller",
                "Display Controller",
                "Multimedia Controller",
                "Memory Controller",
                "Bridge",
                "Simple Communication Controller",
                "Base System Peripheral",
                "Input Device Controller",
                "Docking Station",
                "Processor",
                "Serial Bus Controller",
                "Wireless Controller"
        };

        const char **Subclasses[]{
                sub_unclass,
                sub_mcs,
                sub_net,
                sub_disp,
                sub_mem,
                sub_bridge,
                sub_scc,
                sub_bsp,
                sub_idc,
                sub_dock,
                sub_proc,
                sub_sbc,
                sub_wire
        };
    }

    types::List<PCIDevice *> devices;

    u32 get_address(u8 bus, u8 device, u8 func) {
        return (u32) (((u32) bus << 16) | ((u32) device << 11) | ((u32) func << 8) | 0x80000000);
    }


    u16 read16(u32 address, u8 offset) {

        ports::outl(PORT_PCI_CONFIG_ADDRESS, address | (offset & 0xFC));
        return (u16) ((ports::inl(PORT_PCI_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xFFFF);
    }

    u8 read8(u32 address, u8 offset) {

        return (u8) (offset % 2 == 0 ? read16(address, offset) & -0xFF00 : (read16(address, offset) & -0xFF) >> 8);
    }

    u32 read32(u32 address, u8 offset) {

        ports::outl(PORT_PCI_CONFIG_ADDRESS, address | (offset & 0xFC));
        return ports::inl(PORT_PCI_CONFIG_DATA);
    }

    void printDevice(PCIDevice *dev) {

        kernel::console->print("%x:%x | %s/%s\n", dev->Header->VendorID, dev->Header->DeviceID,
                               names::Classes[dev->Header->ClassCode],
                               dev->Header->Subclass == 0x80 ? "Other" :
                               names::Subclasses[dev->Header->ClassCode][dev->Header->Subclass]);
    }

    /**
     * @brief Makes sure device exists, adds it to list if it does
     * @param bus
     * @param device
     * @return Returns TRUE if device is okay, returns FALSE on error.
     */
    bool checkDevice(u8 bus, u8 device, u8 func) {

        u32 address = get_address(bus, device, func);
        u16 vendorID = read16(address, PCI_VALUE16_VendorID);
        if (vendorID == 0xFFFF)
            return false;

        PCIDevice *dev = new PCIDevice;
//        devices += dev;
        dev->Header->VendorID = vendorID;

        dev->Header->ClassCode = read8(address, PCI_VALUE8_ClassCode);
        dev->Header->Subclass = read8(address, PCI_VALUE8_Subclass);
        dev->Header->HeaderType = read8(address, PCI_VALUE8_HeaderType);
        dev->Header->DeviceID = read16(address, PCI_VALUE16_DeviceID);
        dev->Header->RevisionID = read8(address, PCI_VALUE8_RevisionID);

        return true;
    }

    void init() {

        for (size_t bus = 0; bus < 256; bus++)
            for (size_t device = 0; device < 32; device++)
                for (size_t func = 0; func < 8; func++)
                    checkDevice(bus, device, func);

    }


}

