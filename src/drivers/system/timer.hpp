#ifndef _BOOTACODDY_DRIVERS_SYSTEM_TIMER_HPP
#define _BOOTACODDY_DRIVERS_SYSTEM_TIMER_HPP

#include "util/types.h"
#include "kernel/interrupts.hpp"
#include "drivers/video/txt3.hpp"
#include "kernel/acpi.hpp"
#include "drivers/system/hpet.hpp"

#define PIT_FREQUENCY 1193181

namespace bac::drivers::system::timer {

    typedef void (*TimerTickEvent)();

    extern TimerTickEvent onTimerTick;

    extern u64 TIMER_FREQUENCY;

    void init(u32 period);

}

#endif
