#include <LibK/stdio.h>
#include <System/ISR.h>
#include <stddef.h>

ISRHandler ISR_handlers[256];

static const char *const exceptions_str[] = {"Division by Zero",
                                             "Debug",
                                             "Non-maskable Interrupt",
                                             "Breakpoint",
                                             "Overflow",
                                             "Bound Range Exceeded",
                                             "Invalid Opcode",
                                             "Device Not Available",
                                             "Double Fault",
                                             "Coprocessor Segment Overrun",
                                             "Invalid TSS",
                                             "Segment Not Present",
                                             "Stack-Segment Fault",
                                             "General Protection Fault",
                                             "Page Fault",
                                             "",
                                             "x87 Floating-Point Exception",
                                             "Alignment Check",
                                             "Machine Check",
                                             "SIMD Floating-Point Exception",
                                             "Virtualization Exception",
                                             "Control Protection Exception ",
                                             "",
                                             "",
                                             "",
                                             "",
                                             "",
                                             "",
                                             "Hypervisor Injection Exception",
                                             "VMM Communication Exception",
                                             "Security Exception",
                                             ""};

void isr_handler(Registers *frame);
void isr_handler(Registers *frame) {
    uint64_t isr = frame->interrupt;

    if (ISR_handlers[isr] != NULL)
        ISR_handlers[isr](frame);
    else if (isr < 32) {
        kprintf("Unhandled exception %d %s", isr, exceptions_str[isr]);
    } else {
        kprintf("Unhandled interrupt: %d", isr);
    }
}

void isr_register_handler(int interrupt, ISRHandler handler) {
    ISR_handlers[interrupt] = handler;
}
