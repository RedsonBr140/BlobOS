#include <Asm/Asm.h>
#include <Kernel/Panic.h>
#include <System/IDT.h>

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;
void IDT_Add_Int(uint8_t vector, void (*isr)(), uint8_t flags) {
    idt_entry_t *descriptor = &idt[vector];

    descriptor->isr_low = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs = 0x08; // Kernel code offset
    descriptor->ist = 0;
    descriptor->attributes = flags;
    descriptor->isr_mid = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved = 0;
}

void IDT_Init(void) {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    __asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
}
