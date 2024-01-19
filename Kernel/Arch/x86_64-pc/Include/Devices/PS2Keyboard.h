#pragma once

#include <stdint.h>

// Define the keyboard port address.
#define KBD_PORT 0x60
// Define the keyboard pending port address.
#define KBD_PENDING 0x64

#define NORMAL_STATE 0
#define PREFIX_STATE 1

#define CTRL_PRESSED 0x1D
#define CTRL_RELEASED 0x9D

#define LSHIFT_PRESSED 0x2A
#define RSHIFT_PRESSED 0x36
#define LSHIFT_RELEASED 0xAA
#define RSHIFT_RELEASED 0xB6

#define CAPS_LOCK 0x3A

#define CTRL_MASK 1
#define ALT_MASK 2
#define SHIFT_MASK 3

// Structure to represent a keyboard key state.
typedef struct {
    // Bitfield to know if ctrl, shift and alt are pressed.
    uint8_t status_mask;
    // 1 if the key was just released, 0 if it's pressed.
    int released;
    // The original scancode received from the keyboard.
    uint8_t scancode;
    // The character corresponding to the key.
    unsigned char key;
} Key_Event;

// Initialize the keyboard interface.
void Keyboard_Init();
