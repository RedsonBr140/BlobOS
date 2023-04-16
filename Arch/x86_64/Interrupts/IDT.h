#pragma once

#include <stdbool.h>
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

#ifdef __cplusplus
extern "C" {
#endif
void enableInterrupts(void);
bool areInterruptsEnabled();
void idtInit(void);

// 64-bit IDT Entry.
typedef struct {
    uint16_t isr_low;   // The lower 16 bits of the ISR's address
    uint16_t kernel_cs; // The GDT segment selector that the CPU will load into
                        // CS before calling the ISR
    uint8_t ist; // The IST in the TSS that the CPU will load into RSP; set to
                 // zero for now
    uint8_t attributes; // Type and attributes; see the IDT page
    uint16_t
        isr_mid; // The higher 16 bits of the lower 32 bits of the ISR's address
    uint32_t isr_high; // The higher 32 bits of the ISR's address
    uint32_t reserved; // Set to zero
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idtr_t;
#ifdef __cplusplus
}
#endif
