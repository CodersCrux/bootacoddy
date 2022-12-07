#include "timer.hpp"


namespace bac::drivers::system::timer {

    using namespace ports;

    TimerTickEvent onTimerTick;

    u64 TIMER_FREQUENCY = 0;

    u16 HPET_MINIMAL_TICK = 0;

    static void irq_handler(kernel::interrupts::Registers regs) {

        if (onTimerTick)
            onTimerTick();
    }

    void initPIT(u32 period) {

        // Init PIT timer.
        kernel::interrupts::install_handler(IRQ0, &irq_handler);

        u32 divisor = PIT_FREQUENCY / period;

        // Command byte for setting frequency
        outb(0x43, 0x36);

        // Send LOW and HIGH parts of 16bit divisor
        outb(0x40, (u8) (divisor & 0xFF));
        outb(0x40, (u8) ((divisor >> 8) & 0xFF));

        TIMER_FREQUENCY = period;
    }

//    /**
//     * @brief This function checks if the HPET (a high-res timer) is accessible, if so it uses the HPET frequency to initialize it.\n
//     * Else, it sets up the PIT with it's set frequency.\n
//     * The HPET can go to frequencies up to 10^15Hz.\n
//     * The PIT can go up to 1193181Hz, but it's absolutely not advised! (won't work correctly). Use 1,000-10,000 for stable frequencies.\n
//     * @param PIT
//     * @param HPET
//     */
    void init(u32 period) {

        initPIT(period);
    }

}