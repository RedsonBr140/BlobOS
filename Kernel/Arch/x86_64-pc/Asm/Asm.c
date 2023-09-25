#include <Asm/Asm.h>

void sti(void) { asm("sti"); }
void cli(void) { asm("cli"); }
void halt(void) { asm("hlt"); }

void hcf(void) {
    asm("cli");
    for (;;) {
        asm("hlt");
    }
}