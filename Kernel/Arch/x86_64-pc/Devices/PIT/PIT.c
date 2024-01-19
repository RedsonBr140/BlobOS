#include <Devices/PIT.h>
#include <IO/Ports.h>
#include <LibK/stdio.h>
#include <System/Exceptions.h>
#include <System/IDT.h>
#include <System/PIC.h>

__attribute__((interrupt)) void PIT_Handler(struct stack_frame *frame) {
    PIC_SendEOI(TIMER);
}

void PIT_Init() {
    IDT_Add_Int(PIC_REMAP_OFFSET + TIMER, PIT_Handler,
                IDT_FLAGS_INTERRUPT_GATE);

    kprintf("[OK] Initialize Programmable Interval Timer\n");
    PIC_Unmask(TIMER);
}
