#include <Arch/x86_64/cpuid.hpp>
#include <Kernel/Kernel.hpp>

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
