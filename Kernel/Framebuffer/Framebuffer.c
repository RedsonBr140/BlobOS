#include "flanterm/backends/fb.h"
#include "flanterm/flanterm.h"
#include <Framebuffer/Framebuffer.h>
#include <string.h>

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

void framebuffer_putchar(char c) { flanterm_write(ctx, &c, 1); }

void framebuffer_puts(char *string) {
    flanterm_write(ctx, string, strlen(string));
}