#include <Devices/PS2Keyboard.h>
#include <IO/Ports.h>
#include <LibK/stdio.h>
#include <System/Exceptions.h>
#include <System/IDT.h>
#include <System/PIC.h>

#define MAX_KEYB_BUFFER_SIZE 255

// A global buffer to store previous keypresses.
Key_Event keyboard_buffer[MAX_KEYB_BUFFER_SIZE];
uint8_t buf_position; // Position in the keyboard buffer.
uint8_t kbd_state;    // Current state of the keyboard.
uint8_t caps_state;   // Current state of caps lock.

void Keyboard_Wait();

/* A US keymap, courtesy of Bran's tutorial */
unsigned char kbdmix[128] = {
    0,    27,  '1', '2',        '3',  '4', '5', '6', '7',  '8', /* 9 */
    '9',  '0', '+', /*'´' */ 0, '\b',                           /* Backspace */
    '\t',                                                       /* Tab */
    'q',  'w', 'e', 'r',                                        /* 19 */
    't',  'y', 'u', 'i',        'o',  'p', '[', ']', '\n',      /* Enter key */
    0, /* 29   - Control */
    'a',  's', 'd', 'f',        'g',  'h', 'j', 'k', 'l',  ';', /* 39 */
    '\'', '<', 0,                                               /* Left shift */
    '\\', 'z', 'x', 'c',        'v',  'b', 'n',                 /* 49 */
    'm',  ',', '.', '-',        0,                      /* Right shift */
    '*',  0,                                            /* Alt */
    ' ',                                                /* Space bar */
    0,                                                  /* Caps lock */
    0,                                                  /* 59 - F1 key ... > */
    0,    0,   0,   0,          0,    0,   0,   0,   0, /* < ... F10 */
    0,                                                  /* 69 - Num lock*/
    0,                                                  /* Scroll Lock */
    0,                                                  /* Home key */
    0,                                                  /* Up Arrow */
    0,                                                  /* Page Up */
    '-',  0,                                            /* Left Arrow */
    0,    0,                                            /* Right Arrow */
    '+',  0,                                            /* 79 - End key*/
    0,                                                  /* Down Arrow */
    0,                                                  /* Page Down */
    0,                                                  /* Insert Key */
    0,                                                  /* Delete Key */
    0,    0,   '<', 0,                                  /* F11 Key */
    0,                                                  /* F12 Key */
    0, /* All other keys are undefined */
};

// Excerpt from the US no-modifier key-table
//'q', 'w', 'e', 'r',	/* 19 */
//'t', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
// 0,			/* 29   - Control */
//'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
//'\'', '`',   0,		/* Left shift */
//'<', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
//'m', ',', '.', '-',   0,				/* Right shift */

unsigned char kbdse_shift[128] = {
    0,    27,  '!',  '\"', '#',  0 /* shift+4 */,
    '%',  '&', '/',  '(',        /* 9 */
    ')',  '=', '?',  '`',  '\b', /* Backspace */
    '\t',                        /* Tab */

    'Q',  'W', 'E',  'R', /* 19 */
    'T',  'Y', 'U',  'I',  'O',  'P',
    'A',  'A', '\n', /* Enter key */
    0,               /* 29   - Control */
    'A',  'S', 'D',  'F',  'G',  'H',
    'J',  'K', 'L',  'O', /* 39 */
    '\'', '>', 0,         /* Left shift */
    '*',  'Z', 'X',  'C',  'V',  'B',
    'N',                      /* 49 */
    'M',  ';', ':',  '_',  0, /* Right shift */

    '*',  0, /* Alt */
    ' ',     /* Space bar */
    0,       /* Caps lock */
    0,       /* 59 - F1 key ... > */
    0,    0,   0,    0,    0,    0,
    0,    0,   0,       /* < ... F10 */
    0,                  /* 69 - Num lock*/
    0,                  /* Scroll Lock */
    0,                  /* Home key */
    0,                  /* Up Arrow */
    0,                  /* Page Up */
    '-',  0,            /* Left Arrow */
    0,    0,            /* Right Arrow */
    '+',  0,            /* 79 - End key*/
    0,                  /* Down Arrow */
    0,                  /* Page Down */
    0,                  /* Insert Key */
    0,                  /* Delete Key */
    0,    0,   '>',  0, /* F11 Key */
    0,                  /* F12 Key */
    0,                  /* All other keys are undefined */
};

char Get_Printable_Char(Key_Event Key) {
    if (Key.status_mask & SHIFT_MASK || caps_state == 1)
        return kbdse_shift[Key.scancode];
    else
        return kbdmix[Key.scancode];
}

void Set_CapsLockState() {
    Keyboard_Wait();

    outb(KBD_PORT, 0xED);

    Keyboard_Wait();

    outb(KBD_PORT, 0x04);
}

// Keyboard interrupt handler.
__attribute__((interrupt)) void Keyboard_Handler(struct stack_frame *frame) {
    // Wait until the keyboard is ready to send a scancode.
    Keyboard_Wait();

    // Read the scancode from the keyboard port.
    uint8_t scancode = inb(KBD_PORT);

    // TODO: Handle general purpose keys release
    if (scancode & 0x80) {
        PIC_SendEOI(KEYBOARD);
        return;
    }

    if (scancode == 0xE0) {
        // Handle extended scancodes (prefix).
        kbd_state = PREFIX_STATE;
        PIC_SendEOI(KEYBOARD);
        return;
    }

    // TODO: Study how we should handle this extended state.
    if (kbd_state == PREFIX_STATE)
        kbd_state = NORMAL_STATE;

    // Store the scancode in the global buffer.
    keyboard_buffer[buf_position].scancode = scancode;

    // Process specific key events.
    switch (scancode) {
    case CTRL_PRESSED:
        // Set the CTRL bit in the status_mask.
        keyboard_buffer[buf_position].status_mask |= 1 << CTRL_MASK;
        break;
    case CTRL_RELEASED:
        // Clear the CTRL bit in the status_mask.
        keyboard_buffer[buf_position].status_mask &= ~(1 << CTRL_MASK);
        break;
    case LSHIFT_PRESSED:
    case RSHIFT_PRESSED:
        // Set both LEFT and RIGHT SHIFT bits in the status_mask.
        keyboard_buffer[buf_position].status_mask |= (1 << SHIFT_MASK);
        break;
    case LSHIFT_RELEASED:
    case RSHIFT_RELEASED:
        // Clear both LEFT and RIGHT SHIFT bits in the status_mask.
        keyboard_buffer[buf_position].status_mask &= ~(1 << SHIFT_MASK);
        break;
    case 0x3A:
        caps_state = !caps_state;
        Set_CapsLockState();

    default:
        break;
    };

    kprintf("%c", Get_Printable_Char(keyboard_buffer[buf_position]));

    // Update the buffer position.
    buf_position = (buf_position + 1) % MAX_KEYB_BUFFER_SIZE;

    // Send End of Interrupt (EOI) signal to the PIC.
    PIC_SendEOI(KEYBOARD);
}

// Initialize the PS/2 keyboard interface.
void Keyboard_Init() {
    // Add the keyboard interrupt handler to the Interrupt Descriptor Table
    // (IDT).
    IDT_Add_Int(PIC_REMAP_OFFSET + KEYBOARD, Keyboard_Handler,
                IDT_FLAGS_INTERRUPT_GATE);

    // Print a message indicating successful initialization.
    kprintf("[OK] Initialize PS/2 Keyboard\n");

    // Unmask the keyboard interrupt on the Programmable Interrupt Controller
    // (PIC).
    PIC_Unmask(KEYBOARD);

    // Set the initial state of the keyboard to NORMAL_STATE.
    kbd_state = NORMAL_STATE;
    caps_state = 0;
}

// Wait until the keyboard is ready to send a scancode.
void Keyboard_Wait() {
    while (inb(KBD_PENDING) & 2)
        ;
}
