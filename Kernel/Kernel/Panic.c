#include <Asm/Asm.h>
#include <Framebuffer/Framebuffer.h>
#include <IO/Ports.h>
#include <Kernel/Panic.h>
#include <LibK/stdio.h>
#include <stdint.h>

void get_all_registers() {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rsp, rbp, r8, r9, r10, r11, r12, r13,
        r14, r15;

    // Inline assembly to read registers
    asm volatile("movq %%rax, %0\n"
                 "movq %%rbx, %1\n"
                 "movq %%rcx, %2\n"
                 "movq %%rdx, %3\n"
                 "movq %%rsi, %4\n"
                 "movq %%rdi, %5\n"
                 "movq %%rsp, %6\n"
                 "movq %%rbp, %7\n"
                 "movq %%r8, %8\n"
                 "movq %%r9, %9\n"
                 "movq %%r10, %10\n"
                 "movq %%r11, %11\n"
                 "movq %%r12, %12\n"
                 "movq %%r13, %13\n"
                 "movq %%r14, %14\n"
                 "movq %%r15, %15\n"
                 : "=m"(rax), "=m"(rbx), "=m"(rcx), "=m"(rdx), "=m"(rsi),
                   "=m"(rdi), "=m"(rsp), "=m"(rbp), "=m"(r8), "=m"(r9),
                   "=m"(r10), "=m"(r11), "=m"(r12), "=m"(r13), "=m"(r14),
                   "=m"(r15));
    kprintf("\nRegisters: \nRAX: %p"
            " | RBX: %p"
            " | RCX: %p\n"
            "RDX: %p"
            " | RSI: %p"
            " | RDI: %p"
            " | RSP: %p\n"
            "RBP: %p"
            " | R8: %p"
            " | R9: %p\n"
            "R10: %p"
            " | R11: %p"
            " | R12: %p\n"
            "R13: %p"
            " | R14: %p"
            " | R15: %p"
            " |\n",
            rax, rbx, rcx, rdx, rsi, rdi, rsp, rbp, r8, r9, r10, r11, r12, r13,
            r14, r15);
}

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
    kprintf("\nStack trace:\n");
    for (unsigned int frame = 0; stk && frame < MaxFrames; ++frame) {
        if (stk->rip == 0)
            break;
        kprintf("Frame %d: RIP %p     \n", frame, (void *)stk->rip);
        stk = stk->rbp;
    }
}

void panic(char *message) {
    framebuffer_clear(0xcccccc, 0xc40404);
    kprintf(
        "BlobOS encountered an error which it couldn't recover from.\nPlease "
        "file an issue to https://github.com/RedsonBr140/BlobOS/issues "
        "with detailed information.\nYou will need to restart your "
        "computer.\n");
    get_stack_trace(5);
    get_all_registers();

    kprintf("\nError message: %s\n", message);
    hcf();
}