#pragma once

#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 2

void printk(int log_level, const char *format, ...);
