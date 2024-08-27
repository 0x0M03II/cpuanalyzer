#include "../../../../include/common/_cpu_multiarch.h"
#include "../../../../include/platform/x86_64/_cpu_bitmap.h"
#include "../../../../include/platform/x86_64/_cpu_preprocess.h"

void _get_cpu_cache_topology_information(topology_t* cpu_object) {

    int i;
    int numCaches = 0;
    uint32_t eax, ebx, ecx, edx;

    for (i = 0; (eax & 0x1F) != 0; ++i) {

        ecx = i;
        cpuidimport(CPUID_CACHE_TOPOLOGY, 0, eax, ebx, ecx, edx);

        // Some values must be incrememented.  See Docs for specification
        int cache_type = eax & 0x1F;
        int cache_level = (eax >> 5) & 0x3;
        int fully_associative = (eax >> 9) & 0x01;
        int cache_line_size = (ebx & 0x4FF) + 1;
        int cache_physical_partitions = ((ebx >> 12) & 0x1FF) + 1;
        int cache_number_ways = ((ebx >> 22) & 0x1FF) + 1;
        int cache_number_sets = ecx + 1;
        int cache_inclusive = (edx >> 1) & 0x01;
        int cache_writeback_pol = (edx & 0x01);

        if (cache_type == 0)
            break;

        char* cache_type_string;
        switch (cache_type) {

            case 1: cache_type_string = "Data Cache"; break;
            case 2: cache_type_string = "Instruction Cache"; break;
            case 3: cache_type_string = "Unified Cache"; break;
            default: cache_type_string = "Cache Type Uknown"; break;
        }

        printf("Cache:\tL%d %s\n", cache_level, cache_type_string);
        
        // Cache Information
        printf("\tAssociativity:\t\t\t%s\n", fully_associative ? "Fully Associative" : "Set-Associative");
        printf("\tCache Physical Partitions:\t%d\n", cache_physical_partitions);
        printf("\tCache Number of Ways:\t\t%d\n", cache_number_ways);
        printf("\tCache Line Size:\t\t%d\n", cache_line_size);
        printf("\tCache Inclusive:\t\t%s\n", cache_inclusive ? "Yes" : "No");
        printf("\tCache Number of Sets:\t\t%d\n", cache_number_sets);
        printf("\tCache Write-Back Scope:\t\t%s Write-Back/Invalidate\n", cache_writeback_pol ? "Lower Cache Not Guaranteed" : "Lower Cache Guaranteed");
        printf("\n");
    }
}
