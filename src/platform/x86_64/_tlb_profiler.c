#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void i386_processing_tlb()
{
    int i;
    int num_caches;


    uint32_t eax, ebx, ecx, edx;

    eax = 18;
    ecx = i;

    // CPUID Sub-Leaf 18H Address Translation Params
    asm (
        "cpuid"
        : "+a" (eax)
        , "=b" (ebx)
        , "+c" (ecx)
        , "=d" (edx)
    ); // end assembly

    int allows_4k_pages = (ebx & 1);
    int allows_2mb_pages = ((ebx >>= 1) & 0x1);
    int allows_4mb_pages = ((ebx >>= 1) & 0x1);
    int allows_1gb_pages = ((ebx >>= 1) & 0x1);
    int paritioning = ((ebx >>= 5) & 0x3);

    int tlb_associativity = ((ebx >>= 8) & 0xFFFF);

    int number_of_set = ecx + 1;

    int translation_type = (edx & 0x1F);

    char* translation_cache_type;
    switch (translation_type) {
        case 0: translation_cache_type = "NULL"; break;
        case 1: translation_cache_type = "Data TLB"; break;
        case 2: translation_cache_type = "Instruction TLB"; break;
        case 3: translation_cache_type = "Unified TLB"; break;
    };

    int tlb_level = ((edx >>= 5) & 0x3);
    int is_fully_associative = ((edx >>= 3) & 0x1);
    int max_number_addresses = ((edx >>= 6) & 0x3FF);

    printf(
        "Cache ID: %d:\n"
        "- Cache Type %s:\n"
        "- TLB Associativity %d:\n"
        "- Number of Sets %d:\n"
        , i
        , translation_cache_type
        , tlb_associativity
        , number_of_set
    );

}

int main(int argc, char* argv[])
{
    i386_processing_tlb();

    return 0;
}