#include <Asm/Asm.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <System/ISR.h>

void isr_handler(Registers *frame);
void isr_handler(Registers *frame) {
    kprintf("It was working 5 sec ago: %\n", frame->interrupt);
    return;
}