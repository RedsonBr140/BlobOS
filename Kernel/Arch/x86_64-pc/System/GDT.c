#include <System/GDT.h>
#include <stdint.h>

static uint64_t gdt[] = {
    0x0000000000000000, // null
    0x00009a000000ffff, // 16-bit code
    0x000093000000ffff, // 16-bit data
    0x00cf9a000000ffff, // 32-bit code
    0x00cf93000000ffff, // 32-bit data
    0x00af9b000000ffff, // 64-bit code
    0x00af93000000ffff, // 64-bit data
    0x00affb000000ffff, // usermode 64-bit code
    0x00aff3000000ffff  // usermode 64-bit data
    /* at some stage (presumably when starting to work on usermode) you'll need
     * at least one TSS desriptor in order to set that up, you'll need some
     * knowledge of the segment descriptor and TSS layout */
};

struct __attribute__((packed)) {
    uint16_t size;
    uint64_t *base;
} gdtr = {sizeof(gdt) - 1, gdt};

void GDT_Init() { asm volatile("lgdt %0" ::"m"(gdtr)); }
