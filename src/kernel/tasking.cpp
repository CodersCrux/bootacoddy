//
//#include "tasking.hpp"
//#include "../util/types/list.hpp"
//#include "../util/types/sorted_list.hpp"
//#include "../util/types/sorted_dictionary.hpp"
//#include "../drivers/video/txt3.hpp"
//
//extern u32 k_INITIAL_ESP;
//
//cname u32 read_eip();
//
//#define KERNEL_STACK_ADDR 0xE0000000
//#define KERNEL_STACK_SIZE 0x2000
//
//namespace bac::kernel::tasking {
//
//    ProcessID next_pid = 1;
//
//    volatile Task *current_task = 0;
//    volatile Task *ready_queue;
//
//    void init() {
//
//        asm("cli");
//
//        move_stack(KERNEL_STACK_ADDR, KERNEL_STACK_SIZE);
//
//        ready_queue = current_task = new Task(next_pid++, paging::current_dir, 0, 0, 0, nullptr);
//
//        asm("sti");
//    }
//
//    int fork() {
//
//        asm("cli");
//
//        Task *parent_task = (Task *) current_task;
//
//        paging::PageDir *directory = paging::clone_pagedir(paging::current_dir);
//
//        Task *new_task = new Task(next_pid++, directory, 0, 0, 0, nullptr);
//
//        Task *task_iter = (Task *)ready_queue;
//        while (task_iter->next)
//            task_iter = task_iter->next;
//        task_iter->next = new_task;
//
//        u32 eip = read_eip();
//
//        if (current_task == parent_task) {
//
//            u32 esp, ebp;
//            asm("mov %%esp, %0" : "=r" (esp));
//            asm("mov %%ebp, %0" : "=r" (ebp));
//            new_task->ESP = esp;
//            new_task->EBP = ebp;
//            new_task->EIP = eip;
//
//            asm("sti");
//            return new_task->ID;
//        } else return 0;
//    }
//
//    void task_switch() {
//
//        // If tasking isn't initialized, quit
//        if (!current_task) return;
//
//        asm("cli");
//
//        u32 esp, ebp, eip;
//        asm("mov %%esp, %0" : "=r" (esp));
//        asm("mov %%ebp, %0" : "=r" (ebp));
//
//        // To detect errors, we put a dummy EIP value such as 0x12345
//        // If we switched tasks, EIP will contain this value.
//        eip = read_eip();
//        if (eip == 0x12345)
//            return;
//
//        // If we didn't switch tasks, let's switch
//        current_task->EIP = eip;
//        current_task->ESP = esp;
//        current_task->EBP = ebp;
//
//        current_task = current_task->next;
//        if (!current_task) current_task = ready_queue;
//
//        eip = current_task->EIP;
//        esp = current_task->ESP;
//        ebp = current_task->EBP;
//
//        paging::current_dir = current_task->PageDir;
//
////        drivers::video::txt3::print("ID: %i, ESP: %x", current_task->ID, current_task->ESP);
//
//        // Switch tasks
//        task_switch(eip, paging::current_dir->physicalAddr, ebp, esp);
//    }
//
//    void move_stack(u32 new_stack_start, u32 size) {
//
//        for (u32 i = new_stack_start; i >= new_stack_start - size; i -= 0x1000)
//            paging::alloc_frame(paging::get_page(i, 1, paging::current_dir), 0, 1);
//
//        // Inform the CPU our mapping was updated, by flushing the TLB.
//        // This is done by reading and writing the page address from CR3
//
//        u32 pagedir_addr;
//        asm("mov %%cr3, %0" : "=r" (pagedir_addr));
//        asm("mov %0, %%cr3" : : "r" (pagedir_addr));
//
//        u32 old_esp, old_ebp;
//        asm("mov %%esp, %0" : "=r" (old_esp));
//        asm("mov %%ebp, %0" : "=r" (old_ebp));
//
//        u32 offset = new_stack_start - k_INITIAL_ESP;
//
//        u32 new_esp = old_esp + offset;
//        u32 new_ebp = old_ebp + offset;
//
//        memory::memcpy((u8 *) new_esp, (u8 *) old_esp, k_INITIAL_ESP - old_esp);
//
//        for (size_t i = 0; i > new_stack_start - size; i -= 4) {
//
//            u32 temp = *(u32 *) i;
//
//            if (old_esp < temp && temp < k_INITIAL_ESP) {
//
//                temp += offset;
//                u32 *temp2 = (u32 *) i;
//                *temp2 = temp;
//            }
//        }
//
//        // Switch stacks
//        asm("mov %0, %%esp" : : "r" (new_esp));
//        asm("mov %0, %%ebp" : : "r" (new_ebp));
//    }
//
//    int getPID() {
//        return current_task->ID;
//    }
//}
//
