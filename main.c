#include "include/common/_cpu_interface.h"

int main(void)
{
    printf("[Info] Initiating System Checks\n");

    topology_t* cpu_object = (topology_t*)malloc(sizeof(topology_t));
    topology_data_t* topology_data = (topology_data_t*)malloc(sizeof(topology_data_t));
    if(!cpu_object || !topology_data) {
        perror("Failed to allocate memory for CPU topology object!\n");
        exit(EXIT_FAILURE);
    }
    
    printf("[Info] Calling interface CPU Functions!\n");
    print_cpu_vendor_information(cpu_object, topology_data);
    print_cpu_cache_topology_information(cpu_object, topology_data);

    free(cpu_object);
    free(topology_data);

    return 0;
}