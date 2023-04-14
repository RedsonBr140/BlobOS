#include <LibK/stdlib.h>

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

    // Convert the value to the desired base.
    do {
        int digit = value % base;
        value /= base;
        *ptr++ = digits[digit];
    } while (value != 0);

    // Add the terminating null character.
    *ptr = '\0';

    // Reverse the string.
    char *start = buffer;
    char *end = ptr - 1;
    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }

    return buffer;
}
