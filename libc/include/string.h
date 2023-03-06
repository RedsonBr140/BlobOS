#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>

void *memmove(void *dstptr, const void *srcptr, size_t size);
size_t strlen(const char *str);
#endif
