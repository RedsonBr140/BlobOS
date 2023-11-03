#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <Kernel/CMDLine.h>
#include <LibK/stdio.h>
#include <Serial/Serial.h>
#include <System/GDT.h>
#include <System/PIC.h>
#include <limine.h>

#ifndef GIT_VERSION
#define GIT_VERSION "Undefined"
#endif

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_kernel_file_request kernel_file_request = {
    .id = LIMINE_KERNEL_FILE_REQUEST, .revision = 0};

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, .revision = 0};

void Arch_entry(void) {
    // Be able to work with the CMDLine from the very early stage
    parseCMDLine(kernel_file_request.response->kernel_file->cmdline);

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

    // Ensure interrupts are disabled.
    cli();

    GDT_Init();
    printk(LOG_LEVEL_INFO, "GDT (Re)-loaded!\n");

    // IRQ0 starts at 0x20 and IRQ8 starts at 0x28.
    PIC_Init(0x20, 0x28);
    printk(LOG_LEVEL_INFO, "PIC working\n");

    IDT_Init();
    printk(LOG_LEVEL_INFO, "IDT Loaded!\n");

    sti();
    printk(LOG_LEVEL_INFO, "Interrupts enabled!\n");

#ifdef GIT_VERSION
    printk(LOG_LEVEL_INFO, "Welcome to BlobOS!\nVersion: %s\n", GIT_VERSION);
#endif
    halt();
}
