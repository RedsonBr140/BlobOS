#include <Kernel.hpp>
#include <TextMode.hpp>

#include "cpuid.hpp"
extern "C" void ArchInit() {
    TextMode::Terminal terminal = *Kernel::GetMainTerminal();
    terminal.SetColor(TextMode::Color::CYAN, TextMode::Color::BLACK);
    terminal.Clear();

    x86_64::hasCPUID();
    terminal.WriteString("[OK] CPU has CPUID support.\n");

    x86_64::SupportsLongMode();
    terminal.WriteString("[OK] CPU has Long Mode support.\n");

    return;
}
