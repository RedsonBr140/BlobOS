#pragma once

#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t size);
void *memmove(void *dstptr, const void *srcptr, size_t size);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *str);
