#include <Devices/PS2Keyboard.h>
#include <IO/Ports.h>
#include <LibK/stdio.h>
#include <System/Exceptions.h>
#include <System/IDT.h>
#include <System/PIC.h>

// A global variable to store the last keypress for syscall access.
Key lastkeypress;

// This is a standard US keyboard scancode table.
// TODO: Consider loading this data from files for better organization.
unsigned char kbdus[128] = {
    // The scancode-to-character mapping for standard US keyboard.
    // Each element corresponds to a specific key or function.
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',    /* 9 */
    '9', '0', '-', '=', '\b',                         /* Backspace */
    '\t',                                             /* Tab */
    'q', 'w', 'e', 'r',                               /* 19 */
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     /* Enter key */
    0,                                                /* 29   - Control */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
    '\'', '`', 0,                                     /* Left shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',               /* 49 */
    'm', ',', '.', '/', 0,                            /* Right shift */
    '*', 0,                                           /* Alt */
    ' ',                                              /* Space bar */
    0,                                                /* Caps lock */
    // ... Continue mapping for F1, F2, and other keys ...
    0, /* All other keys are undefined */
};

void Keyboard_Wait();

// Keyboard interrupt handler.
__attribute__((interrupt)) void Keyboard_Handler(struct stack_frame *frame) {
    Keyboard_Wait();

    lastkeypress.scancode = inb(KBD_PORT);

    if (lastkeypress.scancode & 0x80) {
        lastkeypress.released = 1;
        lastkeypress.key = kbdus[lastkeypress.scancode & 0x7F];
        // Temporary: Print released key.
        kprintf("Released: %c\n", lastkeypress.key);
    } else {
        lastkeypress.key = kbdus[lastkeypress.scancode];
        // Temporary: Print pressed key.
        kprintf("%c\n", lastkeypress.key);
    }

    PIC_SendEOI(KEYBOARD);
}

// Initialize the PS/2 keyboard interface.
void Keyboard_Init() {
    IDT_Add_Int(PIC_REMAP_OFFSET + KEYBOARD, Keyboard_Handler,
                IDT_FLAGS_INTERRUPT_GATE);

    kprintf("[OK] Initialize PS/2 Keyboard\n");
    PIC_Unmask(KEYBOARD);
}

// Wait until the keyboard is ready to send a scancode.
void Keyboard_Wait() {
    while (inb(KBD_PENDING) & 2)
        ;
}
