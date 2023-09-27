#include <Framebuffer/Framebuffer.h>
#include <LibK/stdio.h>
#include <LibK/stdlib.h>
#include <LibK/string.h>
#include <stdarg.h>

typedef void (*formatter_t)(va_list *);

static void format_char(va_list *args) {
    char c = va_arg(*args, int);
    framebuffer_putchar(c);
};

static void format_string(va_list *args) {
    char *string = va_arg(*args, char *);
    framebuffer_puts(string);
};

static void format_hexa(va_list *args) {
    char buffer[32];
    uint64_t number = va_arg(*args, size_t);

    ultoa(number, buffer, 16);

    framebuffer_puts("0x");
    framebuffer_puts(buffer);
};

static void format_decimal(va_list *args) {
    char buffer[32];

    int num = va_arg(*args, int);
    itoa(num, buffer, 10);
    framebuffer_puts(buffer);
};

static const formatter_t FORMATTERS[256] = {
    ['c'] = format_char,
    ['s'] = format_string,
    ['d'] = format_decimal,
    ['p'] = format_hexa,
};

void kprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            formatter_t formatter = FORMATTERS[(unsigned char)*(++p)];
            if (formatter != NULL) {
                formatter(&args);
            } else {
                framebuffer_putchar('%');
                framebuffer_putchar(*p);
            }
        } else {
            framebuffer_putchar(*p);
        }
    }

    va_end(args);
}