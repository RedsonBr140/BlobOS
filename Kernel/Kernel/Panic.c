#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <stdint.h>

struct stackframe {
    struct stackframe *rbp;
    uint64_t rip;
};

// TODO: Unwind the stack and get a cool stack trace :)
void panic(char *message) {
    framebuffer_clear(0xcccccc, 0xc40404);
    kprintf(
        "BlobOS encountered an error which it couldn't recover from.\nPlease "
        "file an issue to https://github.com/RedsonBr140/BlobOS/issues "
        "with detailed information.\nYou will need to restart your "
        "computer.\n");

    kprintf("\nError message: %s\n", message);
    hcf();
}
