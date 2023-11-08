#pragma once

#define PIC_REMAP_OFFSET 0x20

/*
 * IRQ macros
 */

enum Interrupts {
    ALL = 0xFF,
    // Programmable Interval Timer
    TIMER = 0,
    KEYBOARD,
    // Used internally by the two PICs. never raised
    CASCADE,
    COM2,
    COM1,
    LPT2,
    FLOPPY,
    FREE7,
    // CMOS real-time clock
    CLOCK,
    FREE9,
    FREE10,
    FREE11,
    PS2MOUSE,
    // FPU / Coprocessor / Inter-processor
    FPU,
    // Primary ATA Hard Disk
    IDE_1,
    // Secondary ATA Hard Disk
    IDE_2
};

/*
 * Functions
 */

void PIC_Initialize(int offset1, int offset2);
void PIC_SendEOI(unsigned char irq);
void PIC_Mask(unsigned char IRQline);
void PIC_MaskAll(void);
void PIC_Unmask(unsigned char IRQline);
