#include <IO/Ports.h>
#include <System/PIC.h>
#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

void PIC_Init(int pic1, int pic2) {
    // Send ICW1
    outb(PIC1, ICW1);
    io_wait();
    outb(PIC2, ICW1);
    io_wait();

    // Send ICW2
    outb(PIC1 + 1, pic1); // Remap
    io_wait();
    outb(PIC2 + 1, pic2); // PICs
    io_wait();

    // Send ICW3
    outb(PIC1 + 1, 4); // IRQ2 -> connection to slave
    io_wait();
    outb(PIC2 + 1, 2);
    io_wait();

    // Send ICW4
    outb(PIC1 + 1, ICW4);
    io_wait();
    outb(PIC2 + 1, ICW4);
    io_wait();

    // Disable all IRQs
    outb(PIC1 + 1, 0xFF);
    io_wait();
}