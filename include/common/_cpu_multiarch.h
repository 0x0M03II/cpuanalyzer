#ifndef CPU_MULTIARCH_H
#define CPU_MULTIARCH_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#if defined(__x86_64__) || defined(_M_X64)

    // x86 Architecture, determine platform
    #include <immintrin.h>
    #include "../platform/x86_64/_cpu_preprocess.h"
    
    // #if (PLATFORM == 0x6874754) // AMD
        
    // #else

    // #endif
    
    // function pointer to implement
    typedef void (* cpu_implementer_top)(topology_t* cpu_object, topology_data_t* tdata);
    typedef void (* cpu_implementer_vend)(topology_t* cpu_object, topology_data_t* tdata);

    // function pointer assignments
    extern const cpu_implementer_vend cpu_vendor;
    extern const cpu_implementer_top cpu_topology;

#endif

#endif // CPU_MULTIARCH_H