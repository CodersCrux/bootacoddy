#ifndef BOOTACODDY_KERNEL_TASKING_HPP
#define BOOTACODDY_KERNEL_TASKING_HPP

#include "../util/types.h"
#include "../kernel/paging.hpp"

namespace bac::kernel::tasking {

    typedef i32 ProcessID;

    struct Task : paging::Allocatable<Task> {

        Task(ProcessID ID, paging::PageDir *PageDir, u32 ESP, u32 EBP, u32 EIP, Task *next)
                : ID(ID), PageDir(PageDir), ESP(ESP), EBP(EBP), EIP(EIP), next(next) {}

        ProcessID ID; // Process ID
        u32 ESP, EBP, EIP; // Registers
        paging::PageDir *PageDir; // Mamory page xdirectory
        Task *next;
    };

    cname void task_switch(u32 eip, u32 physicalAddr, u32 ebp, u32 esp);

    void init();

    void task_switch();

    int fork();

    void move_stack(u32 new_stack_start, u32 size);

    int getPID();

}

#endif