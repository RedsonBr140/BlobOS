#pragma once

#define PIC_REMAP_OFFSET 0x20

/*
 * IRQ macros
 */

enum Interrupts {
    ALL = 0xFF,
    TIMER = 0,
    KEYBOARD,
    CASCADE,
    COM2_4,
    COM1_3,
    LPT,
    FLOPPY,
    FREE7,
    CLOCK,
    FREE9,
    FREE10,
    FREE11,
    PS2MOUSE,
    COPROC,
    IDE_1,
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
