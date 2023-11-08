#include <Asm/Asm.h>
#include <Devices/PIT.h>
#include <Devices/PS2Keyboard.h>
#include <Entry/HAL.h>
#include <LibK/stdio.h>
#include <System/GDT.h>
#include <System/IDT.h>
#include <System/PIC.h>

// Assembly function from GDT.
extern void reloadSegments(void);

void HAL_Init() {

    GDT_Init();
    reloadSegments();
    kprintf("[OK] Initialize GDT\n");

    PIC_Initialize(0x20, 0x28);
    kprintf("[OK] PIC remapped to 0x20 and 0x28\n");
    PIC_MaskAll();

    IDT_Init();
    kprintf("[OK] Initialize IDT\n");

    Keyboard_Init();
    PIT_Init();

    sti();
    kprintf("[OK] Enable interrupts\n");
}
