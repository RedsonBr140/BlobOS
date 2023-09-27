#pragma once

#include <stdint.h>

char *itoa(int value, char *buffer, int base);
char *ultoa(uint64_t value, char *str, int base);
