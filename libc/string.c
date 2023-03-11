#include <stddef.h>
#include <stdint.h>

#include "include/string.h"

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
