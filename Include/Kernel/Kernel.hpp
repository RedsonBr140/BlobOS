#pragma once
#include <Arch/TextMode.hpp>

namespace Kernel {
TextMode::Terminal *GetMainTerminal();
extern "C" void Panic(char *PanicMessage);
}; // namespace Kernel
