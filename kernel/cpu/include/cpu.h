#pragma once

typedef struct {
    unsigned int model;
    unsigned int stepping;
    unsigned int family;
} CPUInfo;

int cpuSupportsBrandString();
char *getBrandString();
CPUInfo getCPUInfoString();
