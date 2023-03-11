#include "cpu.h"
#include "libc/include/stdio.h"
#include "libc/include/string.h"
#include <cpuid.h>

int cpuSupportsBrandString() {
    unsigned int eax, unused;
    __get_cpuid(0x80000000, &eax, &unused, &unused, &unused);
    if (eax < 0x80000004)
        return 0;
    return 1;
}

char *getBrandString() {
    unsigned int regs[12];
    char *str = NULL;

    __cpuid(0x80000002, regs[0], regs[1], regs[2], regs[3]);
    __cpuid(0x80000003, regs[4], regs[5], regs[6], regs[7]);
    __cpuid(0x80000004, regs[8], regs[9], regs[10], regs[11]);

    memcpy(str, regs, sizeof(regs));

    return str;
}

CPUInfo getCPUInfoString() {
    unsigned int eax, unused;
    CPUInfo cpu;
    __get_cpuid(1, &eax, &unused, &unused, &unused);
    cpu.family = (eax >> 8) & 0xF;
    cpu.model = (eax >> 4) & 0xF;
    cpu.stepping = eax & 0xF;
    return cpu;
}
