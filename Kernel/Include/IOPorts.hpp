#pragma once
#include <stdint.h>

namespace IOPorts {
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

// Wait a very small amount of time (1 to 4 microseconds, generally).
// Note that it's an imprecise wait.
void IOWait(void);

} // namespace IOPorts
