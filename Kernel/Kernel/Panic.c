#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <meta.h>

#include <Kernel/Stack.h>

void panic(char message[static 1]) {
    framebuffer_clear(0xcccccc, 0xc40404);
    kprintf(
        "BlobOS encountered an error which it couldn't recover from.\nPlease "
        "file an issue to https://github.com/RedsonBr140/BlobOS/issues "
        "with detailed information.\nYou will need to restart your "
        "computer.\n");

    kprintf("\nVersion: %s\n", GIT_VERSION);
    kprintf("Error message: %s\n", message);

    dumpStack();
    hcf();
}
