#include <Kernel/Stack.h>
#include <LibK/stdio.h>
#include <stdint.h>

#if defined(__x86_64__)
void dumpStack(void) {
    kprintf("Stacktrace:\n");
    uint64_t rbp = 0;

    __asm__ volatile("mov %%rbp, %0" : "=r"(rbp));

    for (uint64_t frame = 0; rbp && frame < DUMP_STACK_ENTRIES_MAX; ++frame) {
        kprintf(" [%p]\n", rbp);
        rbp += sizeof(void *);
    }
}

#elif defined(__i386__)
/* NOTE: NOT TESTED. */

struct stackframe {
    struct stackframe *ebp;
    uint64_t rip;
};

void dumpStack(void) {
    kprintf("Stacktrace:\n");
    struct stackframe *stackFrame;
    asm("movl %%ebp,%0" : "=r"(stackFrame)::);
    for (uint64_t frame = 0; stackFrame && frame < PANIC_STACK_ENTRIES_MAX;
         ++frame) {

        kprintf(" [%p]\n", stackFrame->rip);
        stackFrame = stackFrame->ebp;
    }
}
#else
void dumpStack(void) { kprintf("Stacktrace unavaliable.\n"); }
#endif
