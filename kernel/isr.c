__attribute__((noreturn)) void exception_handler(void);

void exception_handler(void) {
    asm volatile("cli; hlt"); // Completely hangs the computer
    while (1)
        ; // Ensure that it will not return.
}
