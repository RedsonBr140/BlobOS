#include <Asm/Asm.h>
#include <Devices/Framebuffer.h>
#include <Entry/HAL.h>
#include <IO/Ports.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <Meta.h>
#include <Serial/Serial.h>
#include <limine.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

void Arch_entry(void) {

    // Ensure interrupts are disabled.
    cli();

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

    HAL_Init();
    kprintf("Welcome to BlobOS!\nVersion: %s\n", GIT_VERSION);

    // FIXME: This is hacky and will slow down the kernel.
    for (;;) {
        io_wait();
    }
}
