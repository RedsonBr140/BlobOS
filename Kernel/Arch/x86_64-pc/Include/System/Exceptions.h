#pragma once
#include <stdint.h>

__attribute__((packed)) struct interrupt_frame {
    uint64_t rax, rds, rcx, rsi, rdi, r8, r9, r10, r11, rbp;
};

typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbx, rdx, rcx, rax;
    uint64_t error;
} __attribute__((packed)) Registers;

void Load_Exceptions(void);
