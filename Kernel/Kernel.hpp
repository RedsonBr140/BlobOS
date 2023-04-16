#pragma once
#include <Arch/TextMode.hpp>

#define PANIC(msg) Kernel::Panic(msg, __FILE__, __LINE__)

namespace Kernel {
TextMode::Terminal *GetMainTerminal();
extern "C" void Panic(const char *PanicMessage, const char *file,
                      const int line);
}; // namespace Kernel
