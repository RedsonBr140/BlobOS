#pragma once

// Define the keyboard port address.
#define KBD_PORT 0x60
// Define the keyboard pending port address.
#define KBD_PENDING 0x64

#define LEFT_SHIFT_DOWN 0x2a
#define RIGHT_SHIFT_DOWN 0x36
#define LEFT_SHIFT_UP 0xaa
#define RIGHT_SHIFT_UP 0xb6

// Structure to represent a keyboard key state.
typedef struct {
    // 1 if the Ctrl key is currently pressed, 0 otherwise.
    int ctrl;
    // 1 if the Shift key is currently pressed, 0 otherwise.
    int shift;
    // 1 if the key was just released, 0 if it's pressed.
    int released;
    // The original scancode received from the keyboard.
    unsigned char scancode;
    // The character corresponding to the key.
    unsigned char key;
} Key;

// Initialize the keyboard interface.
void Keyboard_Init();
