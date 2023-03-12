#include <stdarg.h>
#include <stdint.h>

#include "drivers/terminal/include/terminal.h"
#include "idt.h"
#include "libc/include/stdio.h"
#include "multiboot.h"

#include "cpu/include/cpu.h"
#include "stdlib.h"
#include "string.h"

typedef struct {
    uint32_t TotalRAM;
    CPUInfo cpu;
} PCSpecs;

PCSpecs hwInfo(multiboot_info_t *mbi) {
    PCSpecs pc;
    pc.TotalRAM = (mbi->mem_lower + mbi->mem_upper) / 1024 + 1;

    pc.cpu.brand = getBrandString();
    // If the CPU doesn't supports branding, we use the "old fashion way"
    if (!cpuSupportsBrandString()) {
        pc.cpu = getCPUInfo();
        char model_str[16], family_str[16], stepping_str[16];
        int model = pc.cpu.model;
        int family = pc.cpu.family;
        int stepping = pc.cpu.stepping;

        // Convert model, family, and stepping to strings
        itoa(model, model_str, 10);
        itoa(family, family_str, 10);
        itoa(stepping, stepping_str, 10);

        // Concatenate strings and copy to cpu.brand
        strcpy(pc.cpu.brand, "model: ");
        strcat(pc.cpu.brand, model_str);
        strcat(pc.cpu.brand, " family: ");
        strcat(pc.cpu.brand, family_str);
        strcat(pc.cpu.brand, " stepping: ");
        strcat(pc.cpu.brand, stepping_str);
    }
    return pc;
}

void kernel_main(multiboot_info_t *mbi) {
    k_printf("Loading IDT...\n");
    idtInit();
    k_printok("IDT Loaded!");

    // We can't enable interrupts for now, as if we do, It will hang the kernel
    // because we can't handle them.

    // enableInterrupts();
    // k_printok("Interrupts enabled");

    k_printf("Welcome to %aBlobOS!%a\n", VGA_COLOR_LIGHT_CYAN, RESET);
    PCSpecs pc = hwInfo(mbi);
    k_printf("CPU: %s\nTotal RAM: %dMB\n", pc.cpu.brand, pc.TotalRAM);
}
