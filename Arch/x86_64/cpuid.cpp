#include "Kernel.hpp"
#include "TextMode.hpp"
#include <cpuid.h>

#include "cpuid.hpp"

bool x86_64::hasCPUID() {
    int cpuid_supported;

    // Check if CPUID is supported
    cpuid_supported = __get_cpuid_max(0, nullptr);
    if (cpuid_supported == 0) {
        Kernel::Panic((char *)"CPUID not Supported!");
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
        Kernel::Panic((char *)"Long mode not supported!");
    }
    return false;
}
