#include <Arch/x86_64/cpuid.hpp>
#include <Kernel/IOPorts.hpp>
#include <Kernel/Kernel.hpp>

// Functions from 32bit_boot.asm
extern "C" {
void _ClearTables();
void _SetupPaging();
void _EnablePAE();
void _LongMode();
void _EnablePaging();
}

extern "C" void ArchInit() {
    /* TODO: Kernel functions aren't available yet, we can't even panic.
     * We should have a fallback function in assembly for this case.
     */

    /* We can't use Kernel::GetMainTerminal(), as the kernel hasn't started yet.
     */
    // TextMode::Terminal terminal;
    // terminal.SetColor(TextMode::Color::CYAN, TextMode::Color::BLACK);
    // terminal.Clear();
    //
    // x86_64::hasCPUID();
    // terminal.WriteString("[OK] CPU has CPUID support.\n");
    //
    // x86_64::SupportsLongMode();
    // terminal.WriteString("[OK] CPU has Long Mode support.\n");
    //
    // // TODO: Colors + Debug function
    // terminal.WriteString("Enabling Paging...\n");
    //
    _ClearTables();
    // terminal.WriteString("[OK] Tables clear.\n");
    //
    _SetupPaging();
    // terminal.WriteString("[OK] Page tables set.\n");
    //
    _EnablePAE();
    // terminal.WriteString("[OK] PAE enabled.\n");
    //
    _LongMode();
    // terminal.WriteString("[OK] Long Mode enabled.\n");
    //
    _EnablePaging();
    // terminal.WriteString("[OK] Paging enabled.\n");

    return;
}
