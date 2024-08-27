/* 
 * Application: CPU Profiler
 * Author: Maurice Green Jr
 * License: MIT No Attribution Copyright 2024
 * 
 * Purpose: This is a header file to support the cpu_profiler application of mine that will not only profile the CPU, 
 * it will also provide performance testing for research by using the CPU information gathered from the profiler.
 * 
 * Documentation: https://www.amd.com/content/dam/amd/en/documents/processor-tech-docs/programmer-references/24594.pdf
 * 
 * 
 * Specification: Unless special convention is clearly denoted, EAX always holds the first parameter.  In cases where
 * A second parameter is used, ECX will hold the second paramter.
 * 
 * Return Values: Values are returned via the EAX, EBX, ECX, EDX registers. See pages 600 - 604 for specific information 
 * on feature flags.
 * 
*/
#ifndef CPU_BITMAP
#define CPU_BITMAP

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <intrin.h>
#include <errno.h>

#define CPUID_BASE_DEFINITION       0x00000000
#define CPUID_L3_CACHE_MONITORING   0x0000000F    /* page 615 */
#define CPUID_L3_CACHE_ALLOCATION   0x00000010    /* page 616 */
#define CPUID_L1_CACHE_TLB_INFOR    0x80000005    /* page 621 */
#define CPUID_L1_CACHE_TLB_INFOR_4k 0x80000005    /* page 622 */
#define CPUID_L1_INSTRUCTION_CACHE  0x80000005    /* page 623 */
#define CPUID_L2_CACHE_L3_TLB       0x80000006    /* page 623 */
#define CPUID_L2_CACHE_INFORMATION  0x80000006    /* page 625 */
#define CPUID_L3_CACHE_INFORMATION  0x80000006    /* page 625 */
#define CPUID_CACHE_TOPOLOGY        0x8000001D    /* page 636 */
#define CPUID_PROCESSOR_TOPOLOGY    0x8000001E    /* page 638 */


/* Preprocessor MACROS */
/* Vendor ID */
#define VENDOR_AMD   0x68747541  // "Auth" - AMD
#define VENDOR_INTEL 0x756e6547  // "Genu" - Intel

// Handle vendor-specific bit extraction
#define CACHE_TYPE_AMD(eax)   ((eax) & 0x1F)  // Extract bits 4:0
#define CACHE_TYPE_INTEL(eax) ((eax) & 0x1F)  // Extract bits 6:0

// Handle Vendor specific differences
#define GET_CACHE_TYPE(vendor, eax)  \
    ((vendor) == VENDOR_AMD ? CACHE_TYPE_AMD(eax) : CACHE_TYPE_INTEL(eax))

// Handle Platform
#define GET_PLATFORM(ebx) \
    ((ebx) == VENDOR_AMD ? "AMD" : "INTEL")

// Handle Vendor
#define GET_VENDOR(ebx) \
    ((ebx) == VENDOR_AMD ? VENDOR_AMD : VENDOR_INTEL)

#define SET_PLATFORM(name, value) \
    ((value) == VENDOR_AMD ? static const char* name = VENDOR_AMD : static const char* name = VENDOR_INTEL)


#endif // CPU_BITMAP