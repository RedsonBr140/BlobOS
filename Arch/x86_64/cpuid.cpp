#include <Arch/TextMode.hpp>
#include <Kernel/Kernel.hpp>
#include <cpuid.h>

#include "Arch/x86_64/cpuid.hpp"

bool x86_64::hasCPUID() {
    int cpuid_supported;

    // Check if CPUID is supported
    cpuid_supported = __get_cpuid_max(0, nullptr);
    if (cpuid_supported == 0) {
        PANIC("CPUID not Supported!");
        return false;
    }

    return true;
}

bool x86_64::SupportsLongMode() {
    int ebx, edx, unused;
    // Check for long mode support
    __cpuid(0x80000001, unused, ebx, unused, edx);
    if (edx & (1 << 29)) {
        return true;
    } else {
        PANIC("Long mode not supported!");
    }
    return false;
}
