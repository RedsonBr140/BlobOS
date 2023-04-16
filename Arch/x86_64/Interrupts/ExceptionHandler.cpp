#include <Kernel/Kernel.hpp>

extern "C" {
[[noreturn]] void exception_handler(void);
void ExceptionHandler() { PANIC("Exception!"); }
}
