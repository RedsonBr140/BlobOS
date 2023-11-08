#include <Asm/Asm.h>
#include <Entry/HAL.h>
#include <Framebuffer/Framebuffer.h>
#include <IO/Ports.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <Meta.h>
#include <Serial/Serial.h>
#include <limine.h>

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST, .revision = 0};

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

    // Wait for the framebuffer to initialize so that we can show what happened
    if (memmap_request.response == NULL ||
        memmap_request.response->entry_count < 1) {
        panic("(x86-64) Memory map unavailable!");
    }

    HAL_Init();
    kprintf("Welcome to BlobOS!\nVersion: %s\n", GIT_VERSION);

    uint64_t total = 0;

    for (size_t i = 0; i < memmap_request.response->entry_count; i++) {
        struct limine_memmap_entry *entry = memmap_request.response->entries[i];
        kprintf("Mem Entry %d: Base: %p | Lenght: %d | Type: %d\n", i,
                entry->base, entry->length, entry->type);

        total += entry->length;
    }

    kprintf("Total RAM: %d MiB\n", (total / 1024) / 1024 - 1);

    // FIXME: This is hacky and will slow down the kernel.
    for (;;) {
        io_wait();
    }
}
