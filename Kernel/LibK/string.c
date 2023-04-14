#include <stddef.h>
#include <stdint.h>

#include "LibK/string.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void *memcpy(void *dest, const void *src, size_t size) {
    char *d = dest;
    const char *s = src;

    while (size--) {
        *d++ = *s++;
    }

    return dest;
}

void *memmove(void *dstptr, const void *srcptr, size_t size) {
    unsigned char *dst = (unsigned char *)dstptr;
    const unsigned char *src = (const unsigned char *)srcptr;
    if (dst < src) {
        for (size_t i = 0; i < size; i++)
            dst[i] = src[i];
    } else {
        for (size_t i = size; i != 0; i--)
            dst[i - 1] = src[i - 1];
    }
    return dstptr;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : 1;
}

char *strcat(char *dest, const char *src) {
    char *p = dest + strlen(dest);
    while (*src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';
    return dest;
}

char *strcpy(char *dest, const char *src) {
    char *ptr = dest; // Store the starting address of destination string

    while (*src != '\0') { // Copy each character until null character
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0'; // Add null character at the end of destination string

    return ptr; // Return the starting address of destination string
}
