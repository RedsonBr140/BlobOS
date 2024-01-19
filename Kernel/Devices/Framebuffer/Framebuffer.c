#include "flanterm/backends/fb.h"
#include "flanterm/flanterm.h"
#include <Devices/Framebuffer.h>
#include <LibK/stdlib.h>
#include <LibK/string.h>

uint8_t framebuffer_initialized = 0;

struct framebuffer framebuff;
struct flanterm_context *ctx;

void framebuffer_init(struct framebuffer *fb) {
    framebuff.address = fb->address;
    framebuff.width = fb->width;
    framebuff.height = fb->height;
    framebuff.pitch = fb->pitch;

    ctx =
        flanterm_fb_simple_init(fb->address, fb->width, fb->height, fb->pitch);

    framebuffer_initialized = 1;
}

static void ultoa_strcat(char *dest, uint64_t src, bool add_semicolon) {
    char buf[65];
    strcat(dest, ultoa(src, (char *)buf, 10));
    if (add_semicolon == true) {
        strcat(dest, ";");
    }
}

// Format: 0xFFFFFF (No alpha)
void framebuffer_clear(uint32_t foreground, uint32_t background) {
    uint8_t red_fg = (foreground & 0xFF0000) >> 16;
    uint8_t green_fg = (foreground & 0xFF00) >> 8;
    uint8_t blue_fg = foreground & 0xFF;

    uint8_t red_bg = (background & 0xFF0000) >> 16;
    uint8_t green_bg = (background & 0xFF00) >> 8;
    uint8_t blue_bg = background & 0xFF;

    char result[128] = "\033[38;2;";

    ultoa_strcat(result, red_fg, true);
    ultoa_strcat(result, green_fg, true);
    ultoa_strcat(result, blue_fg, true);

    strcat(result, "48;2;");

    ultoa_strcat(result, red_bg, true);
    ultoa_strcat(result, green_bg, true);
    ultoa_strcat(result, blue_bg, false);

    strcat(result, "m");

    flanterm_write(ctx, result, strlen(result));
    flanterm_write(ctx, "\033[2J", 5);
    flanterm_write(ctx, "\033[H", 4);
}

void framebuffer_putchar(char c) {
    flanterm_write(ctx, &c, 1);
    if (c == '\b') {
        char space = ' ';
        flanterm_write(ctx, &space, 1);
        flanterm_write(ctx, &c, 1);
    }
}

void framebuffer_puts(char *string) {
    flanterm_write(ctx, string, strlen(string));
}
