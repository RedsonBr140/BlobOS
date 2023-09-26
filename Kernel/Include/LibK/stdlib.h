#ifndef STDLIB_H
#define STDLIB_H
#include <stdint.h>

char *itoa(int value, char *buffer, int base);
char *ultoa(uint64_t value, char *str, int base);
#endif