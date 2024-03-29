#pragma once

#include <stddef.h>
#include <stdint.h>

struct framebuffer {
    uint32_t *address;
    size_t width;
    size_t height;
    size_t pitch;
};

extern struct framebuffer framebuff;

void framebuffer_init(struct framebuffer *fb);
void framebuffer_clear(uint32_t foreground, uint32_t background);
void framebuffer_putchar(char c);
void framebuffer_puts(char *string);
