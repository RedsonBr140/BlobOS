#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <LibK/stdio.h>
#include <Serial/Serial.h>
#include <System/GDT.h>
#include <System/Interrupts.h>
#include <System/PIC.h>
#include <limine.h>

#ifndef GIT_VERSION
#define GIT_VERSION "Undefined"
#endif

extern void far_jump(void);

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

    // Ensure interrupts are disabled.
    cli();
    kprintf("Interrupts disabled!\n");

    GDT_Init();
    kprintf("GDT (Re)-loaded!\n");

    reloadSegments();
    kprintf("Data and code segment registers reloaded!\n");

    // IRQ0 starts at 0x20 and IRQ8 starts at 0x28.
    PIC_Initialize(0x20, 0x28);
    kprintf("PIC remapped to 0x20 and 0x28\n");
    PIC_Mask(ALL);

    Load_Exceptions();
    kprintf("Exceptions Loaded!\n");

    IDT_Init();
    kprintf("IDT Loaded!\n");

    sti();
    kprintf("Interrupts enabled!\n");

    // PIC_Unmask(TIMER);

    asm("int $0");
    asm("int $0");
    asm("int $0");
    asm("int $0");
    asm("int $0");
    asm("int $35");
    asm("int $0");
    asm("int $0");
    asm("int $0");
    asm("int $0");
    asm("int $0");

#ifdef GIT_VERSION
    kprintf("Welcome to BlobOS!\nVersion: %s\n", GIT_VERSION);
#endif
    halt();
}
