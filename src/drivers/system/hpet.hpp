#ifndef BOOTACODDY_DRIVERS_SYSTEM_HPET_HPP
#define BOOTACODDY_DRIVERS_SYSTEM_HPET_HPP

#include "../../util/types.h"
#include "../../kernel/acpi.hpp"
#include "../../kernel/kernel.hpp"

namespace bac::drivers::system::hpet {

    struct CapabilitiesAndID {
        u64
                RevisionID: 8,
                NumTimersMinusOne: 5,
                IsCapable64bit: 1,
                Reserved: 1,
                LegacyReplacementAvailable: 1,
                VendorID: 16,
                FrequencyInFemto: 32; // Clock frequency in femtoseconds (10^-15 sec)
    };

    struct Configuration {
        u64
                Enable: 1,
                EnableLegacyReplacement: 1,
                Reserved: 62;
    };

    struct InterruptStatus {
        u32 TimerInterruptStatuses;
        u32 Reserved;
    };

    struct Timer {
        u64
                Reserved: 1,
                InterruptType: 1, // Edge-triggered (0) or level (1), just set it to edge triggered
        InterruptEnable: 1,
                EnablePeriodicMode: 1,
                PeriodicAvailable: 1,
                Enable64bit: 1,
                SetValue: 1,
                Reserved2: 1,
                Force32bit: 1,
                InterruptRouting: 5,
                EnableFSBInterrupts: 1,
                FSBInterruptsAvailable: 1,
                Reserved3: 16,
                RoutingCapability: 32;
    };

    void init(u64 period);

}

#endif