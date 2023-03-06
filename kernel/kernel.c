#include <stdarg.h>
#include <stdint.h>

#include "drivers/terminal/include/terminal.h"
#include "libc/include/stdlib.h"

void k_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            switch (*(++p)) {
            case 'd': {
                char buffer[300];
                int num = va_arg(args, int);

                itoa(num, buffer, 10);
                terminal_writestring(buffer);
                break;
            }
            case 's': {
                char *str = va_arg(args, char *);

                terminal_writestring(str);
                break;
            }
            // add more cases for additional format specifiers
            default:
                terminal_putchar(*p);
                break;
            }
        } else {
            terminal_putchar(*p);
        }
    }

    va_end(args);
}

void kernel_main(void) {
    terminal_initialize();
    k_printf("Welcome to BlobOS!\n");
}
