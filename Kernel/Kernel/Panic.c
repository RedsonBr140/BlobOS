#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <IO/Ports.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <stdint.h>

struct stackframe {
    struct stackframe *rbp;
    uint64_t rip;
};

// FIXME: Not exactly the stack trace, it's just for the panic not to be
// empty...
// TODO: Get the function names.
void get_stack_trace(unsigned int MaxFrames) {
    struct stackframe *stk;
    stk = __builtin_frame_address(0);
    printk(LOG_LEVEL_INFO, "\nStack trace:\n");
    for (unsigned int frame = 0; stk && frame < MaxFrames; ++frame) {
        if (stk->rip == 0)
            break;
        printk(LOG_LEVEL_INFO, "Frame %d: RIP %p     \n", frame,
               (void *)stk->rip);
        stk = stk->rbp;
    }
}

void panic(char *message) {
    framebuffer_clear(0xcccccc, 0xc40404);
    printk(
        LOG_LEVEL_ERROR,
        "BlobOS encountered an error which it couldn't recover from.\nPlease "
        "file an issue to https://github.com/RedsonBr140/BlobOS/issues "
        "with detailed information.\nYou will need to restart your "
        "computer.\n");
    get_stack_trace(5);

    printk(LOG_LEVEL_ERROR, "\nError message: %s\n", message);
    hcf();
}
