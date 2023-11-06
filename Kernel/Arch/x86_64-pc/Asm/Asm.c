#include <Asm/Asm.h>
#include <System/IDT.h>
#include <stdbool.h>

// Checks if the interrupts are enabled.
bool interrupts_enabled() {
    unsigned long flags;
    asm volatile("pushf\n\t"
                 "pop %0"
                 : "=g"(flags));
    return flags & (1 << 9);
}
void loadIDT(idtr_t *idtr) { __asm__ volatile("lidt %0" : : "m"(*idtr)); }
void sti(void) { asm("sti"); }
void cli(void) { asm("cli"); }
__attribute__((noreturn)) void halt(void) { asm("hlt"); }

__attribute__((noreturn)) void hcf(void) {
    asm("cli");
    for (;;) {
        asm("hlt");
    }
}
