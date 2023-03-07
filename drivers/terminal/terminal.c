#include <stddef.h>
#include <stdint.h>

#include "include/terminal.h"
#include "kernel/include/io_ports.h"
#include "kernel/include/kernel.h"
#include "libc/include/string.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void update_cursor(int x, int y) {
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}

void terminal_initialize(void) {
    terminal_column = 0;
    terminal_row = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t *)0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = x + VGA_WIDTH * y;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;

    if (index >= VGA_WIDTH * VGA_HEIGHT) {
        k_printf("Error: Attempted to write to an invalid memory address "
                 "(row=%d, col=%d)\n",
                 terminal_row, terminal_column);
        return;
    }

    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll(void) {
    // Scroll the buffer up by one row.
    const size_t buffer_size = (VGA_HEIGHT - 1) * VGA_WIDTH;

    memmove(terminal_buffer, terminal_buffer + VGA_WIDTH, buffer_size * 2);

    // Clear the last row.
    const size_t last_row_offset = VGA_HEIGHT - 1;
    for (size_t x = 0; x < VGA_WIDTH; x++) {
        terminal_putentryat(' ', terminal_color, x, last_row_offset);
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        if (terminal_row + 1 == VGA_HEIGHT) {
            terminal_scroll();
            // If we have reached the last line, we won't be able to go to
            // another line, so we reset the column to the first position.
            terminal_column = 0;
        } else {
            // Move the cursor to the beginning of the next line.
            terminal_row++;
            terminal_column = 0;
        }
    } else {
        // Put the character at the current cursor position and update
        // the cursor position to the next position.
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        update_cursor(terminal_column + 1, terminal_row);

        // If the cursor reaches the end of the line, move it to the
        // beginning of the next line. If we have reached the last line,
        // scroll the terminal.
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_scroll();
            }
        }
    }
}

void terminal_write(const char *data, size_t size) {
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char *data) {
    terminal_write(data, strlen(data));
}
