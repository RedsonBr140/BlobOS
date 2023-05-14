#include <Kernel/IOPorts.hpp>
#include <Kernel/SerialPorts.hpp>
#include <stdint.h>

SerialPort::SerialPort(uint16_t port)
    : data_port_(port), status_port_(port + 5) {
    if (!this->enabled) {
        Port Port0(port + 0);
        Port Port1(port + 1);
        Port Port2(port + 2);
        Port Port3(port + 3);
        Port Port4(port + 4);
        this->enabled = true;

        // Initialize the serial port
        Port1.Write(0x00); // Disable all interrupts
        Port3.Write(0x80); // Enable DLAB (set baud rate divisor)
        Port0.Write(0x03); // Set divisor to 3 (lo byte) 38400 baud
        Port1.Write(0x00); // (hi byte)
        Port3.Write(0x03); // 8 bits, no parity, one stop bit
        Port2.Write(0xC7); // Enable FIFO, clear them, with 14-byte threshold
        Port4.Write(0x0B); // IRQs enabled, RTS/DSR set
    }
}

bool SerialPort::TxReady() const {
    Port statusPort(this->status_port_);

    return (statusPort.Read() & 0x20) != 0;
}

bool SerialPort::RxReady() const {
    Port statusPort(this->status_port_);

    return (statusPort.Read() & 0x01) != 0;
}

void SerialPort::Write(char c) {
    Port dataPort(this->data_port_);
    // Wait for the transmitter to be ready
    while (!TxReady())
        ;

    dataPort.Write(c);
}

char SerialPort::Read() {
    Port dataPort(this->data_port_);
    // Wait for the receiver to have data
    while (!RxReady())
        ;

    // Read the byte from the data port
    return dataPort.Read();
}

void SerialPort::WriteString(const char *str) {
    for (const char *p = str; *p != '\0'; ++p) {
        this->Write(*p);
    }
}
