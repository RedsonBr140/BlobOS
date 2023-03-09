#include "../drivers/terminal/include/terminal.h"
#include "stdio.h"
#include <stdint.h>

#include "idt.h"

extern void *isr_stub_table[];
extern void reload_idt(void *);

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;

void idtSetDescriptor(uint8_t vector, void *isr, uint8_t flags) {
    idt_entry_t *descriptor = &idt[vector];

    descriptor->isr_low = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs =
        0x08; // Offset of the code selector on the GDT table.
    descriptor->attributes = flags;
    descriptor->isr_high = (uint32_t)isr >> 16;
    descriptor->reserved = 0;
}

void enableInterrupts(void) {
    __asm__ volatile("sti");
}

void idtInit(void) {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idtSetDescriptor(vector, isr_stub_table[vector], 0x8E);
    }
    reload_idt(&idt);
}
