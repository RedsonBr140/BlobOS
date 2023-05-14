#pragma once
#include <stdint.h>

class Port {
  public:
    Port(uint16_t port) : port(port) {}
    void Write(uint8_t data);
    uint8_t Read();

    // Wait a very small amount of time (1 to 4 microseconds, generally).
    // Note that it's an imprecise wait.
    void IOWait();

  private:
    uint16_t port;
};
