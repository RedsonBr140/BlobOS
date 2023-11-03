#pragma once

#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *str);
char *strcat(char *restrict dest, const char *restrict src);
char *strtok(char *srcString, char *delim);
int strcmp(const char *s1, const char *s2);
char *strchr(const char *s, int c);