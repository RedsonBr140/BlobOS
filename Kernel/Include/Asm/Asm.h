#pragma once
#include <System/IDT.h>
#include <stdbool.h>

// Checks if the interrupts are enabled. Return 1 if so, otherwise, return 0.
bool interrupts_enabled();
void loadIDT(idtr_t *idtr);
__attribute__((noreturn)) void halt(void);
__attribute__((noreturn)) void hcf(void);
void sti(void);
void cli(void);
