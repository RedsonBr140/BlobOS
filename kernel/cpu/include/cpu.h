#pragma once

typedef struct {
    unsigned int model;
    unsigned int stepping;
    unsigned int family;
    unsigned int ext_model;
} CPUInfo;

int cpuSupportsBrandString();
char *getBrandString();
CPUInfo getCPUInfoString();
