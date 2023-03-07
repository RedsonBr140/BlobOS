#include <stdarg.h>
#include <stdint.h>

#include "drivers/terminal/include/terminal.h"
#include "libc/include/stdlib.h"
#include "libc/include/stdio.h"

void kernel_main(void) {
    terminal_initialize();
    k_printf("Welcome to BlobOS!\n");
}
