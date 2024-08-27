
#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Topology Struct */

typedef struct { // container for CPUID params
    uint32_t func;
    uint32_t subfunc;
    uint32_t* eax;
    uint32_t* ebx;
    uint32_t* ecx;
    uint32_t* edx;
    union
    { // for vendor ID detection
        const char* platformID;
        uint32_t* vendorID;    
    } cplat;
} topology_t;

typedef struct {
    int* cache_type;
    int* cache_level;
    int* cache_inclusive;
    int* cache_line_size;
    int* cache_number_ways;
    int* cache_number_sets;
    int* fully_associative;
    char* cache_type_string;
    int* cache_writeback_pol;
    int* cache_physical_partitions;
    union
    {
        uint32_t* vendorId;
        const char* platformID;
    } cplat;
} topology_data_t;

#endif // STRUCTURE_H
