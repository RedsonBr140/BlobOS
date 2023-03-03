#include "drivers/terminal/include/terminal.h"

void kernel_main(void) {
    terminal_initialize();
    terminal_writestring("Welcome to BlobOS!");
}
