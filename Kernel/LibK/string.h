#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
void *memcpy(void *dest, const void *src, size_t size);
void *memmove(void *dstptr, const void *srcptr, size_t size);
int strcmp(const char *s1, const char *s2);
char *strcat(char *dest, const char *src);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *str);

#ifdef __cplusplus
}
#endif
