#include <stdarg.h>
#include <stdint.h>

#include "drivers/terminal/include/terminal.h"
#include "idt.h"
#include "libc/include/stdio.h"
#include "multiboot.h"

#include "cpu/include/cpu.h"

void kernel_main(multiboot_info_t *mbi) {
    k_printf("Loading IDT...\n");
    idtInit();
    k_printok("IDT Loaded!");

    // We can't enable interrupts for now, as if we do, It will hang the kernel
    // because we can't handle them.

    // enableInterrupts();
    // k_printok("Interrupts enabled");

    k_printf("Welcome to %aBlobOS!%a\n", VGA_COLOR_LIGHT_CYAN, RESET);

    if (cpuSupportsBrandString()) {
        k_printf("Model: %s\n", getBrandString());
    } else {
        CPUInfo cpu = getCPUInfoString();
        k_printf("Model: %d Family: %d Stepping: %d", cpu.model,
                 cpu.family, cpu.stepping);
    }
}
