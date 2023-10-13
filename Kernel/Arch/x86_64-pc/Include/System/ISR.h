#pragma once
#include <stdint.h>

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbx, rdx, rcx, rax;
    uint64_t interrupt, error;
} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers *regs);

void isr_register_handler(int interrupt, ISRHandler handler);
