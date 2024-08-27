#include "../../include/common/_cpu_interface.h"

/*
 * This file serves as an interface, and strictly uses functions
 * that are assigned to function pointers in _cpu_multiarch.h.
 * 
 * This allows outside components to access cpu information by calling
 * the appropriate interface function, without changing to for each architecture
 * essentially abstracting the multiarchitectur differences away.
 * 
 * 
*/

// print vendor
void print_cpu_vendor_information(topology_t* cpu_object, topology_data_t* tdata_object)
{
    _get_cpu_vendor_information(cpu_object, tdata_object);
}

// print topology
void print_cpu_cache_topology_information(topology_t* cpu_object, topology_data_t* tdata_object)
{
    _get_cpu_cache_topology_information(cpu_object, tdata_object);
}


/* Call assignment to function pointer for vendor*/
void _get_cpu_vendor_information(topology_t* cpu_object, topology_data_t* tdata_object) {
    if (cpuidpresent) {
        cpu_vendor(cpu_object, tdata_object);
    }
}

/* call assignment to function pointer for topology */
void _get_cpu_cache_topology_information(topology_t* cpu_object, topology_data_t* tdata_object)
{
    if (cpuidpresent)
    {
        int i;

        for (i = 0; (*cpu_object->eax & 0x1F) != 0; ++i) {

            *cpu_object->ecx = i;
            cpu_topology(cpu_object, tdata_object);

            printf("Cache:\tL%d %s\n", *tdata_object->cache_level, *tdata_object->cache_type_string);
            
            // Cache Information
            printf("\tAssociativity:\t\t\t%s\n", *tdata_object->fully_associative ? "Fully Associative" : "Set-Associative");
            printf("\tCache Physical Partitions:\t%d\n", *tdata_object->cache_physical_partitions);
            printf("\tCache Number of Ways:\t\t%d\n", *tdata_object->cache_number_ways);
            printf("\tCache Line Size:\t\t%d\n", *tdata_object->cache_line_size);
            printf("\tCache Inclusive:\t\t%s\n", *tdata_object->cache_inclusive ? "Yes" : "No");
            printf("\tCache Number of Sets:\t\t%d\n", *tdata_object->cache_number_sets);
            printf("\tCache Write-Back Scope:\t\t%s Write-Back/Invalidate\n", *tdata_object->cache_writeback_pol ? "Lower Cache Not Guaranteed" : "Lower Cache Guaranteed");
            printf("\n");
        }
    }
}
