extern "C" {
__attribute__((noreturn)) void exception_handler(void);
void ExceptionHandler() {
    for (;;) {
        __asm__ volatile("cli; hlt"); // Completely hangs the computer
    }
}
}
