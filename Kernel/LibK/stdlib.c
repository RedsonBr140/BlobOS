#include <LibK/stdlib.h>
#include <stdint.h>

char *ultoa(uint64_t value, char *str, int base) {
    char *rc;
    char *ptr;
    char *low;
    // Check for supported base.
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do {
        *ptr++ = "0123456789abcdefghijklmnop"
                 "qrstuvwxyz"[value % base];
        value /= base;
    } while (value);
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char *itoa(int value, char *buffer, int base) {
    const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *ptr = buffer;

    // Check for supported base.
    if (base < 2 || base > 36) {
        *buffer = '\0';
        return buffer;
    }

    // Handle negative values.
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }

    // Convert the value to the desired base in reverse order.
    do {
        int digit = value % base;
        *ptr++ = digits[digit];
        value /= base;
    } while (value > 0);

    // Null-terminate the string.
    *ptr = '\0';

    // Reverse the string in-place.
    char *start = buffer;
    char *end = ptr - 1;
    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }

    return buffer;
}
