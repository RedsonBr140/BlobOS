#pragma once

int start_serial(void);
void serial_putchar(char a);
void serial_puts(char *string);
char read_serial();
