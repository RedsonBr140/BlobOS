#include <Devices/PS2Keyboard.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <LibK/string.h>

#define SHELL_BUFFER_SIZE 256
#define SHELL_PROMPT "BlobOS> "

char shell_buffer[SHELL_BUFFER_SIZE];
size_t buffer_position = 0;

// Forward declarations
void shell_execute_command(char *command);
void shell_clear_buffer();

void shell_init() {
    kprintf("\nBlobOS Shell v0.1\n");
    kprintf("Type 'help' for a list of commands\n");
    kprintf(SHELL_PROMPT);
}

void shell_process_keypress(char c) {
    kprintf("%c", c); // Echo the character to the screen
    // Handle special keys
    if (c == '\t') {
        // Handle tab completion (not implemented)
        return;
    }
    // Handle backspace
    if (c == '\b') {
        if (buffer_position > 0) {
            buffer_position--;
            shell_buffer[buffer_position] = '\0';
            kprintf("\b \b"); // Erase character on screen
        }
        return;
    }

    // Handle enter key
    if (c == '\n') {
        shell_buffer[buffer_position] = '\0';
        kprintf("\n");

        // Execute the command
        shell_execute_command(shell_buffer);

        // Clear buffer and show prompt again
        shell_clear_buffer();
        kprintf(SHELL_PROMPT);
        return;
    }

    // Add character to buffer if there's space
    if (buffer_position < SHELL_BUFFER_SIZE - 1) {
        shell_buffer[buffer_position++] = c;
        shell_buffer[buffer_position] = '\0';
    }
}

void shell_clear_buffer() {
    for (size_t i = 0; i < SHELL_BUFFER_SIZE; i++) {
        shell_buffer[i] = '\0';
    }
    buffer_position = 0;
}

void shell_execute_command(char *command) {
    if (strcmp(command, "help") == 0) {
        kprintf("Available commands:\n");
        kprintf("  help    - Display this help message\n");
        kprintf("  clear   - Clear the screen\n");
        kprintf("  version - Display kernel version\n");
    } else if (strcmp(command, "clear") == 0) {
        framebuffer_clear(0xFFFFFF, 0x000000); // White text on black background
    } else if (strcmp(command, "version") == 0) {
        kprintf("BlobOS Kernel Version %s\n", GIT_VERSION);
    } else if strcmp (command, "panic") {
        panic("Requested by the user.");
    } else if (strlen(command) > 0) {
        kprintf("Unknown command: %s\n", command);
    }
}
