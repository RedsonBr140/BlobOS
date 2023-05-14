#include <Arch/x86_64/Interrupts/PIC.hpp>
#include <Kernel/IOPorts.hpp>
#define PIC_EOI 0x20 /* End-of-interrupt command code */

#define ICW1_ICW4 0x01      /* Indicates that ICW4 will be present */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

namespace PIC {
void SendEOI(unsigned char irq) {
    Port PIC2_CMD(PIC2_COMMAND);
    Port PIC1_CMD(PIC1_COMMAND);
    if (irq >= 8)
        PIC2_CMD.Write(PIC_EOI);

    PIC1_CMD.Write(PIC_EOI);
}

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */

  

/*
arguments:
        offset1 - vector offset for master PIC
                vectors on the master become offset1..offset1+7
        offset2 - same for slave PIC: offset2..offset2+7
*/
void Remap(int offset1, int offset2) {
    Port PIC1Data(PIC1_DATA);
    Port PIC1CMD(PIC1_COMMAND);
    Port PIC2Data(PIC2_DATA);
    Port PIC2CMD(PIC2_COMMAND);
    unsigned char a1, a2;

    a1 = PIC1Data.Read(); // save masks
    a2 = PIC2Data.Read();

    PIC1CMD.Write(
        ICW1_INIT |
        ICW1_ICW4); // starts the initialization sequence (in cascade mode)

    // In fact, doesn't matter which port we use it on.
    PIC1Data.IOWait();

    PIC2CMD.Write(ICW1_INIT | ICW1_ICW4);

    PIC2CMD.IOWait();
    PIC1Data.Write(offset1); // ICW2: Master PIC vector offset
    PIC1Data.IOWait();
    PIC2Data.Write(offset2); // ICW2: Slave PIC vector offset
    PIC2Data.IOWait();
    PIC1Data.Write(4); // ICW3: tell Master PIC that there is a slave PIC at
                       // IRQ2 (0000 0100)
    PIC1Data.IOWait();
    PIC2Data.Write(2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    PIC2Data.IOWait();

    PIC1Data.Write(
        ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    PIC1Data.IOWait();
    PIC2Data.Write(ICW4_8086);
    PIC2Data.IOWait();

    PIC1Data.Write(a1); // restore saved masks.
    PIC2Data.Write(a2);
}
} // namespace PIC
