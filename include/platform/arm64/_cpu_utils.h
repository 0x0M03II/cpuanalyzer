#ifndef ARM_CPU_UTILS_H
#define ARM_CPU_UTILS_H

#include <stdint.h>

// Function to read the MIDR (Main ID Register) on ARM
static inline uint32_t read_midr() {
    uint32_t midr;
    __asm__ volatile ("mrs %0, MIDR_EL1" : "=r" (midr));
    return midr;
}

// Macros to extract information from MIDR
#define GET_IMPLEMENTER(midr)  (((midr) >> 24) & 0xFF)   // Bits 31:24
#define GET_VARIANT(midr)      (((midr) >> 20) & 0xF)    // Bits 23:20
#define GET_ARCHITECTURE(midr) (((midr) >> 16) & 0xF)    // Bits 19:16
#define GET_PARTNUM(midr)      (((midr) >> 4) & 0xFFF)   // Bits 15:4
#define GET_REVISION(midr)     ((midr) & 0xF)            // Bits 3:0

// Example CPU implementer codes (from ARM documentation)
#define IMPLEMENTER_ARM    0x41
#define IMPLEMENTER_APPLE  0x61

static void get_cpu_topology() {
    uint32_t midr = read_midr();
    return GET_IMPLEMENTER(midr);
}

#endif // ARM_CPU_UTILS_H