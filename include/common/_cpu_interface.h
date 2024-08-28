#ifndef CPU_INTERFACE_H
#define CPU_INTERFACE_H

#include "_structures.h"
#include "_cpu_multiarch.h"

/* Ref. Assembly code in cpuidIsSupported.S */
extern int cpuidispresent(void);

/* CPU Vendor Access Methods */
void _get_cpu_vendor_information(topology_t* cpu_object, topology_data_t* tdata_object);
void print_cpu_vendor_information(topology_t* cpu_object, topology_data_t* tdata_object);

/* CPU Topology Access Methods */
void _get_cpu_cache_topology_information(topology_t* cpu_object, topology_data_t* tdata_object);
void print_cpu_cache_topology_information(topology_t* cpu_object, topology_data_t* tdata_object);

#endif // CPU_INTERFACE_H