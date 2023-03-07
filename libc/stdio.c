#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include "drivers/terminal/include/terminal.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef void (*formatter_t)(va_list *);

static void format_char(va_list *args) {
    char c = va_arg(*args, int);
    terminal_putchar(c);
}

static void format_string(va_list *args) {
    char *s = va_arg(*args, char *);
    terminal_writestring(s);
}

static void format_decimal(va_list *args) {
    char buffer[32];
    int num = va_arg(*args, int);
    itoa(num, buffer, 10);
    terminal_writestring(buffer);
}

static void format_hexa(va_list *args) {
    char buffer[sizeof(void *) + 2]; // add space for "0x"
    int *pointer = va_arg(*args, void *);
    itoa((int)&pointer, buffer, 16);

    terminal_writestring(buffer);
}

// add more format specifier functions as needed

static const formatter_t FORMATTERS[256] = {
    ['c'] = format_char,
    ['s'] = format_string,
    ['d'] = format_decimal,
    ['p'] = format_hexa,
    // set other format specifier mappings as needed
};

void k_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            formatter_t formatter = FORMATTERS[(unsigned char)*(++p)];
            if (formatter != NULL) {
                formatter(&args);
            } else {
                terminal_putchar('%');
                terminal_putchar(*p);
            }
        } else {
            terminal_putchar(*p);
        }
    }

    va_end(args);
}
