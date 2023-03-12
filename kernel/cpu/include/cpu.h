#pragma once

typedef struct {
    unsigned int model;
    unsigned int stepping;
    unsigned int family;
    char *brand;
} CPUInfo;

int cpuSupportsBrandString();
char *getBrandString();
CPUInfo getCPUInfo();
