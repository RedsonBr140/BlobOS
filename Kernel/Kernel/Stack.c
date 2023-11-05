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
#else
void dumpStack(void) { kprintf("Stacktrace unavaliable.\n"); }
#endif
