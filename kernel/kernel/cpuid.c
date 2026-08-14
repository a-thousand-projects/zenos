//
// Created by graeme on 13/08/2026.
//
#include <stdint.h>
#include <stdio.h>
#include "kernel/cpuid.h"
extern void cpuid(uint32_t leaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);


void check_long_mode_support(void) {
    uint32_t eax, ebx, ecx, edx;

    cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
    if (eax < 0x80000001) {
        printf("CPUID extended leaves not supported - cannot check for long mode\n\r");
        printf("** System Halting **");
        while(1);
    }

    cpuid(0x80000001, &eax, &ebx, &ecx, &edx);
    if (!(edx & (1 << 29))) {
        printf("Long mode (LM) not supported by this CPU\n\r");
        printf("** System Halting **");
        while(1);
    }

    cpuid(1, &eax, &ebx, &ecx, &edx);
    if (!(edx & (1 << 6))) {
        printf("PAE not supported by this CPU\n\r");
        printf("** System Halting **");
        while(1);
    }

    printf("Long mode + PAE supported [OK]\n\r");
}