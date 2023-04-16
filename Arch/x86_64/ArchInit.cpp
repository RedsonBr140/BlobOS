#include <Arch/x86_64/Interrupts/IDT.h>
#include <Arch/x86_64/cpuid.hpp>
#include <Kernel/IOPorts.hpp>
#include <Kernel/Kernel.hpp>
#include <Kernel/SerialPorts.hpp>
// Functions from 32bit_boot.asm
extern "C" {
void _ClearTables();
void _SetupPaging();
void _EnablePAE();
void _LongMode();
void _EnablePaging();
}

extern "C" void ArchInit() {
    x86_64::hasCPUID();
    x86_64::SupportsLongMode();

    _ClearTables();
    _SetupPaging();
    _EnablePAE();
    _LongMode();
    _EnablePaging();

    return;
}
