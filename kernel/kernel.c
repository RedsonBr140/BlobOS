#include <stdarg.h>
#include <stdint.h>

#include "drivers/terminal/include/terminal.h"
#include "idt.h"
#include "libc/include/stdio.h"

void kernel_main(void) {

    idtInit();
    k_printf("Welcome to %aBlobOS!%a\n", VGA_COLOR_LIGHT_CYAN, RESET);
}
