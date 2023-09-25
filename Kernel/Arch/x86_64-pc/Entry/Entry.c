#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <LibK/stdio.h>
#include <Serial/Serial.h>
#include <limine.h>
#ifndef GIT_VERSION
#define GIT_VERSION "Undefined"
#endif

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

void Arch_entry(void) {

    start_serial();
    serial_puts("BlobOS is initializing the framebuffer...\n");

    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    struct limine_framebuffer *framebuffer =
        framebuffer_request.response->framebuffers[0];

    struct framebuffer fb = {0};

    fb.address = (uint32_t *)framebuffer->address;
    fb.width = framebuffer->width;
    fb.height = framebuffer->height;
    fb.pitch = framebuffer->pitch;

    framebuffer_init(&fb);
    serial_puts("Framebuffer initialized!\n");

#ifdef GIT_VERSION
    kprintf("Welcome to BlobOS!\nVersion: %s", GIT_VERSION);
#endif

    hcf();
}