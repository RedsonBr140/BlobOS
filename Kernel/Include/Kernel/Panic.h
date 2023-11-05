#pragma once

/**
    @brief Panics the kernel
    @param message The message to put in kernel panic, must be non null.
*/
__attribute__((noreturn)) void panic(char message[static 1]);
