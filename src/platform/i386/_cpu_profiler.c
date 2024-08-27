#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>


void i386_processor_info(size_t* data_caches)
{
    int i;
    int num_data_caches = 0;

    for (i = 0; i < 32; i++) {

        /*
            * CPUID -> Information
            * Official Documentation is provided by Intel
            * See the Manual for 32 and 64-bit processors
            * https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
        */

        // EAX, EBX, ECX, EDX 32-bit registers are used for storing cpuid values
        
        uint32_t eax, ebx, ecx, edx;
        
        eax = 4;
        ecx = i;

        // inline call to the Intel intrinsic -> cpuid
        asm (
            "cpuid"
            : "+a" (eax)
            , "=b" (ebx)
            , "+c" (ecx)
            , "=d" (edx)
        ); // output stored in these 4 i386 registers

        int cache_type = eax & 0x1F; // mask 0001 1111

        /*
            * 0 = Null - No more caches
            * 1 = Data Cache
            * 2 = Instruction Cache
            * 3 = Unified Cache
            * 4-31 = Reserved
        */

        if (cache_type == 0)
            break;
        
        char* cache_type_string;
        switch (cache_type) {
            case 1: cache_type_string = "Data Cache"; break;
            case 2: cache_type_string = "Instruction Cache"; break;
            case 3: cache_type_string = "Unified Cache"; break;
            default: cache_type_string = "Unknown Cache Type"; break;
        }

        int cache_level = (eax >>= 5) & 0x7;
        int cache_is_self_initializing = (eax >>= 3) & 0x1;
        int cache_is_fully_associative = (eax >> 1) & 0x1;

        /* ebx and ecx operations */
        int number_of_cache_sets = ecx + 1;

        int cache_coherency_line_size = (ebx & 0xFFF) + 1;
        int cache_physical_line_partitions = ((ebx >>= 12) & 0x3FF) + 1;
        int cache_associativity = ((ebx >>= 10) & 0x3FF) + 1;

        /* edx operations */
        bool wb_invalidate_guaranteed = false;
        if ((edx & 0x1) == 1)
            wb_invalidate_guaranteed = true;
        
        bool cache_inclusive = false;
        if (((edx >>= 1) & 1) == 1)
            cache_inclusive = true;
        
        bool complex_cache_indexing = false;
        if (((edx >>= 1) & 1) == 1)
            complex_cache_indexing = true;


        /* final calculations and print */
        size_t cache_total_size = number_of_cache_sets 
                               * cache_associativity 
                               * cache_coherency_line_size 
                               * cache_physical_line_partitions;
        

        if (cache_type == 1 || cache_type == 3)
            data_caches[num_data_caches++] = cache_total_size;
        
        printf(
            "Cache ID %d:\n"
            "- Level: %d\n"
            "- Type: %s\n"
            "- Sets: %d\n"
            "- System Coherency Line Size: %d bytes\n"
            "- Physical Line partitions: %d\n"
            "- Ways of associativity: %d\n"
            "- Total Size: %zu bytes (%zu kb)\n"
            "- Is fully associative: %s\n"
            "- Is Self Initializing: %s\n"
            "- Write-Back Guaranteed: %s\n"
            "- Cache Inclusive Policy: %s\n"
            "- Complex Cache Indexing: %s\n"
            "\n"
            , i
            , cache_level
            , cache_type_string
            , number_of_cache_sets
            , cache_coherency_line_size
            , cache_physical_line_partitions
            , cache_associativity
            , cache_total_size, cache_total_size >> 10
            , cache_is_fully_associative ? "true" : "false"
            , cache_is_self_initializing ? "true" : "false"
            , wb_invalidate_guaranteed ? "true" : "false"
            , cache_inclusive ? "true" : "false"
            , complex_cache_indexing ? "true" : "false"
        );
    }
    return num_data_caches;
}


test_cache(size_t attempts, size_t lower_cache_size, int * latencies, size_t max_latency) {
    int fd = open('/dev/urandom', O_RDONLY);
    if (fd < 0) {
        perror("open");
        abort();
    }

    /* mapping to random data */
    char* random_data = mmap(
        NULL
        , lower_cache_size
        , PROT_READ | PROT_WRITE
        , MAP_PRIVATE | MAP_ANON
        , -1
        , 0
    );

    if (random_data == MAP_FAILED) {
        perror("mmap");
        abort();
    }

    /* initialize the memory */
    size_t i;
    for (i = 0; i < lower_cache_size; i += sysconf(_SC_PAGESIZE))
        random_data[i] = 1;

    
    int random_offset = 0;
    while (attempts--) {
        random_offset += rand();
        random_offset %= lower_cache_size;

        int32_t cycles, edx, gpr1, gpr2;
        asm (
            "mfence\n\t"
            "rdtsc\n\t"
            "mov %%edx, %2\n\t"
            "mov %%eax, %3\n\t"
            "mfense\n\t"
            "mov %4, %%al\n\t"
            "mfense\n\t"
            "rdtsc\n\t"
            "sub $2, %%edx\n\t"
            "sub $3, %%eax\n\t"
            : "=&a" (cycles)
            , "=&d" (edx)
            , "=&r" (gpr1)
            , "=&r" (gpr2)
            : "m" (random_data[random_offset])
        );

        if (cycles < max_latency)
            latencies[cycles]++;
        else 
            latencies[max_latency - 1]++;
    }
    munmap(random_data, lower_cache_size);
    
    return 0;
}

int main(int argc, char* argv[]) {
    size_t cache_sizes[32];
    int num_data_caches = i386_processor_info(cache_sizes);
}