#include <stdarg.h>
#include <stdint.h>

#include "drivers/terminal/include/terminal.h"
#include "idt.h"
#include "libc/include/stdio.h"

void kernel_main(void) {
    k_printf("Loading IDT...\n");
    idtInit();
    k_printok("IDT Loaded!");

    // We can't enable interrupts for now, as if we do, It will hang the kernel
    // because we can't handle them.

    // enableInterrupts();
    // k_printok("Interrupts enabled");

    k_printf("Welcome to %aBlobOS!%a\n", VGA_COLOR_LIGHT_CYAN, RESET);
}
