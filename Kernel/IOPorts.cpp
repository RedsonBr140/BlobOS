#include <Kernel/IOPorts.hpp>
#include <stdint.h>

void Port::Write(uint8_t data) {
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(this->port));
}

uint8_t Port::Read() {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(this->port));

    return ret;
}

void Port::IOWait(void) {
    Port random_port(0x80);
    random_port.Write(0);
}
