#include <Arch/TextMode.hpp>
#include <Kernel/Kernel.hpp>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <Kernel/LibK/stdio.h>
#include <Kernel/LibK/stdlib.h>
#include <Kernel/LibK/string.h>

extern "C" {
typedef void (*formatter_t)(va_list *);

struct FormatterMap {
    char key;
    formatter_t value;
};

static void format_char(va_list *args) {
    TextMode::Terminal term = *Kernel::GetMainTerminal();
    char c = va_arg(*args, int);
    term.PutChar(c);
}

static void format_string(va_list *args) {
    TextMode::Terminal term = *Kernel::GetMainTerminal();
    char *s = va_arg(*args, char *);
    term.WriteString(s);
}

static void format_decimal(va_list *args) {
    TextMode::Terminal term = *Kernel::GetMainTerminal();

    char buffer[32];
    int num = va_arg(*args, int);
    itoa(num, buffer, 10);
    term.WriteString(buffer);
}

static void format_hexa(va_list *args) {
    TextMode::Terminal term = *Kernel::GetMainTerminal();

    char buffer[sizeof(void *) + 2];
    char prefix[] = "0x";
    size_t prefix_length = strlen(prefix);

    void *pointer = va_arg(*args, void *);
    itoa((uintptr_t)&pointer, buffer, 16);

    // Shift buffer to the right by two bytes
    size_t buf_length = strlen(buffer);
    memmove(buffer + prefix_length, buffer, buf_length);
    memcpy(buffer, prefix, prefix_length);

    term.WriteString(buffer);
}

static void format_color(va_list *args) {
    TextMode::Terminal term = *Kernel::GetMainTerminal();
    enum TextMode::Color colors = va_arg(*args, TextMode::Color);

    // TODO: Don't hardcode the background
    term.SetColor(colors, TextMode::Color::BLACK);
}

// FIXME: When we get an STL, use std::map instead of this hack.
static const FormatterMap FORMATTERS[256] = {
    {'c', format_char}, {'s', format_string}, {'d', format_decimal},
    {'p', format_hexa}, {'a', format_color},
};

void k_printf(const char *format, ...) {
    TextMode::Terminal term = *Kernel::GetMainTerminal();
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) {
        if (*p == '%') {
            formatter_t formatter = nullptr;
            for (const FormatterMap &map : FORMATTERS) {
                if (map.key == *(++p)) {
                    formatter = map.value;
                }
            }
            if (formatter != nullptr) {
                formatter(&args);
            } else {
                term.PutChar('%');
                term.PutChar(*p);
            }
        } else {
            term.PutChar(*p);
        }
    }

    va_end(args);
}

void k_printok(const char *message) {
    k_printf("%a[OK]%a %s\n", TextMode::Color::LIGHT_CYAN,
             TextMode::Color::RESET, message);
}
}
