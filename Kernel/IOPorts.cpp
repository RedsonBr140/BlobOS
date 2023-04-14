#include <stdint.h>

namespace IOPorts {
void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));

    return ret;
}

// Wait a very small amount of time (1 to 4 microseconds, generally).
// Note that it's an imprecise wait.
void IOWait(void) { outb(0x80, 0); }

} // namespace IOPorts
