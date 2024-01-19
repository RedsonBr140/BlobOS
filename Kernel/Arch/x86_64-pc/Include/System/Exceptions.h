#pragma once
#include <stdint.h>

__attribute__((packed)) struct interrupt_frame {
    uint64_t rax, rds, rcx, rsi, rdi, r8, r9, r10, r11, rbp;
};

void Load_Exceptions(void);
