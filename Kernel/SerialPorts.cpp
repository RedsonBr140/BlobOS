#include <Kernel/IOPorts.hpp>
#include <Kernel/SerialPorts.hpp>
#include <stdint.h>

SerialPort::SerialPort(uint16_t port)
    : data_port_(port), status_port_(port + 5) {
    // Initialize the serial port
    IOPorts::outb(port + 1, 0x00); // Disable all interrupts
    IOPorts::outb(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
    IOPorts::outb(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    IOPorts::outb(port + 1, 0x00); //                  (hi byte)
    IOPorts::outb(port + 3, 0x03); // 8 bits, no parity, one stop bit
    IOPorts::outb(port + 2,
                  0xC7); // Enable FIFO, clear them, with 14-byte threshold
    IOPorts::outb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

bool SerialPort::TxReady() const {
    return (IOPorts::inb(status_port_) & 0x20) != 0;
}

bool SerialPort::RxReady() const {
    return (IOPorts::inb(status_port_) & 0x01) != 0;
}

void SerialPort::Write(char c) {
    // Wait for the transmitter to be ready
    while (!TxReady())
        ;

    // Write the byte to the data port
    IOPorts::outb(data_port_, c);
}

char SerialPort::Read() {
    // Wait for the receiver to have data
    while (!RxReady())
        ;

    // Read the byte from the data port
    return IOPorts::inb(data_port_);
}

void SerialPort::WriteString(const char *str) {
    for (const char *p = str; *p != '\0'; ++p) {
        Write(*p);
    }
}
