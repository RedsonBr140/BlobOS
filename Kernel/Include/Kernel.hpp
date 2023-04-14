#pragma once
#include <TextMode.hpp>

namespace Kernel {
extern TextMode::Terminal terminal;
extern "C" void Panic(char *PanicMessage);
}; // namespace Kernel
