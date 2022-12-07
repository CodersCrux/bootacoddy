#include "hpet.hpp"


namespace bac::drivers::system::hpet {

    CapabilitiesAndID *CAPS_AND_ID;
    Configuration *CONF;
    InterruptStatus *INT_STATUS;
    u64 *MAIN_COUNTER;
    Timer *TIMER0_CONF;
    u64 *TIMER0_COUNTER;

    void init(u64 period) {

        if (!kernel::acpi::HPET)
            PANIC("HPET ACPI table doesn't exist!");

        u64 base = kernel::acpi::HPET->Address.Address;

        CAPS_AND_ID = (CapabilitiesAndID *) base;
        CONF = (Configuration *) (base + 0x10);
        INT_STATUS = (InterruptStatus *) (base + 0x20);
        MAIN_COUNTER = (u64 *) (base + 0xF0);
        TIMER0_CONF = (Timer *) (base + 0x100 - 0x107);
        TIMER0_COUNTER = (u64 *) (base + 0x108 - 0x10F);


        TIMER0_CONF->InterruptType = 0;

        kernel::console->print("Addr: %x\n", kernel::acpi::HPET->Address.Address);
        kernel::console->print("64bit: %s\n", CAPS_AND_ID->IsCapable64bit ? "true" : "false");
        kernel::console->print("LRA: %s\n", TIMER0_CONF->PeriodicAvailable ? "true" : "false");
        kernel::console->print("Counter: %i\n", *MAIN_COUNTER);
        kernel::console->print("Timer cap: %i\n", CAPS_AND_ID->NumTimersMinusOne);
    }

}