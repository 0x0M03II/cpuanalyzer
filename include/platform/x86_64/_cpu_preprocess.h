
#ifndef CPU_PREPROCESS
#define CPU_PREPROCESS

/* Access Bitmap Macros */
#include "../x86_64/_cpu_bitmap.h"
#include "../../common/_cpu_interface.h"

/* cpuid utility function */
void cpuid(topology_t* top);

// /* cpuid utility overload */
// static inline void cpuidimport(
//     uint32_t func,
//     uint32_t subfunc,
//     uint32_t* eax,
//     uint32_t* ebx,
//     uint32_t* ecx,
//     uint32_t* edx
// );

/* CPU Ventor utility function */
void get_cpu_vendor(topology_t* cpu_object, topology_data_t* tdata);

/* CPU Topology utility function */
void get_cpu_topology(topology_t* cpu_object, topology_data_t* tdata);

#endif // CPU_PREPROCESS