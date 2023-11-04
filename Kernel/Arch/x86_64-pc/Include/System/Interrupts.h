#pragma once
#include <stdint.h>

struct interrupt_frame {
    uint64_t ip;
    uint64_t cs;
    uint64_t flags;
    uint64_t sp;
    uint64_t ss;
};

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbx, rdx, rcx, rax;
    uint64_t error;
} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers *regs);

void Load_Exceptions(void);
