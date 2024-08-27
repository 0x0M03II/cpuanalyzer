#include "../../../../include/platform/x86_64/_cpu_preprocess.h"

/* cpuid utility function */
static inline void cpuid(topology_t* top)
{
    __asm__ volatile (
        "cpuid"
        : "=a" (top->eax), "=b" (top->ebx), "=c" (top->ecx), "=d" (top->edx)
        : "a" (top->func), "c" (top->subfunc)
    );
}

/* cpuid utility function */
static inline void cpuidimport(
    uint32_t func,
    uint32_t subfunc,
    uint32_t* eax,
    uint32_t* ebx,
    uint32_t* ecx,
    uint32_t* edx
)
{
    __asm__ volatile (
        "cpuid"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "a" (func), "c" (subfunc)
    );
}

/* Helper function for cpuid call */
static inline cpuidHelper(topology_t* cpu_object, uint32_t cpuidfunction)
{
    if(cpu_object == NULL) 
    {
        fprintf(stderr, "CPUID Routine %d (errno = %d)\n",
            cpuidfunction,
            errno);
        exit(EXIT_FAILURE);
    }

    cpu_object->func      = cpuidfunction;
    cpu_object->subfunc   = 0;
}

/* CPU Ventor utility function */
static inline void get_cpu_vendor(topology_t* cpu_object, topology_data_t* tdata)
{
    cpuidHelper(cpu_object, CPUID_BASE_DEFINITION);

    cpuid(cpu_object);

    // Set Platform MACRO
    cpu_object->cplat.platformID = GET_PLATFORM(*cpu_object->ebx);
    cpu_object->cplat.vendorID = GET_VENDOR(*cpu_object->ebx);
}


static inline void get_cpu_topology(topology_t* cpu_object, topology_data_t* tdata)
{

    int i;
    int numCaches = 0;
    cpuidHelper(cpu_object, CPUID_CACHE_TOPOLOGY); // define the cpuid function

    // call CPUID
    cpuid(cpu_object);

    *cpu_object->ecx = i;
    cpu_topology(cpu_object);

    // Some values must be incrememented.  See Docs for specification
    int *tdata->cache_type = *cpu_object->eax & 0x1F;
    int *tdata->cache_level = (*cpu_object->eax >> 5) & 0x3;
    int *tdata->fully_associative = (*cpu_object->eax >> 9) & 0x01;
    int *tdata->cache_line_size = (*cpu_object->ebx & 0x4FF) + 1;
    int *tdata->cache_physical_partitions = ((*cpu_object->ebx >> 12) & 0x1FF) + 1;
    int *tdata->cache_number_ways = ((*cpu_object->ebx >> 22) & 0x1FF) + 1;
    int *tdata->cache_number_sets = *cpu_object->ecx + 1;
    int *tdata->cache_inclusive = (*cpu_object->edx >> 1) & 0x01;
    int *tdata->cache_writeback_pol = (*cpu_object->edx & 0x01);

    if (*tdata->cache_type == 0)
        return;

    char* cache_type_string;
    switch (*tdata->cache_type) {

        case 1: *tdata->cache_type_string = "Data Cache"; break;
        case 2: *tdata->cache_type_string = "Instruction Cache"; break;
        case 3: *tdata->cache_type_string = "Unified Cache"; break;
        default: *tdata->cache_type_string = "Cache Type Uknown"; break;
    }
}