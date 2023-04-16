#include <Kernel/Kernel.hpp>

extern "C" {
__attribute__((noreturn)) void exception_handler(void);
void ExceptionHandler() { PANIC("Exception!"); }
}
