#pragma once

#define PIC_REMAP_OFFSET 0x20

/*
 * IRQ macros
 */
#define ALL 0xFF
#define TIMER 0
#define KEYBOARD 1
#define CASCADE 2
#define COM2_4 3
#define COM1_3 4
#define LPT 5
#define FLOPPY 6
#define FREE7 7
#define CLOCK 8
#define FREE9 9
#define FREE10 10
#define FREE11 11
#define PS2MOUSE 12
#define COPROC 13
#define IDE_1 14
#define IDE_2 15

/*
 * Functions
 */

void PIC_Initialize(int offset1, int offset2);
void PIC_SendEOI(unsigned char irq);
void PIC_Mask(unsigned char IRQline);
void PIC_Unmask(unsigned char IRQline);
