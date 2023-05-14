#pragma once

#include "IOPorts.hpp"
#include <stdint.h>

class SerialPort {
  public:
    SerialPort(uint16_t port);

    bool TxReady() const;
    bool RxReady() const;
    void Write(char c);
    char Read();
    void WriteString(const char *str);

  private:
    const uint16_t data_port_;
    const uint16_t status_port_;
    bool enabled = false;
};

// Define the COM1 base address
constexpr uint16_t COM1_BASE = 0x3F8;

// Define a function to write a byte to the serial port
void serial_write(char c);

// Define a function to read a byte from the serial port
char serial_read();
