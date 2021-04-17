#include "stdio.h"
#include "stdint.h"
#include "stddef.h"

//  0 1 2 3 4 5 6 7
// |a|#|#|#|b|b|b|b|
typedef struct
{
    uint8_t a;
    uint32_t b;
} S1;

//  0 1 2 3 4 5 6 7
// |a|a|a|a|b|#|#|#|
typedef struct
{
    uint32_t a;
    uint8_t b;
} S2;

void print_bytes(void* mem, size_t num_bytes)
{
    for (size_t i = 0; i < num_bytes; i++)
        printf("%02x ", *((unsigned char*)mem + i));
    putc('\n', stdout);
}

int main()
{    
    S1 var1          = { .a = 0xAA, .b = 0xFFFFFFFF };
    static S1 var1_s = { .a = 0xAA, .b = 0xFFFFFFFF };

    printf("Char is first, then int:\n");
    print_bytes(&var1,   sizeof(S1));
    print_bytes(&var1_s, sizeof(S1));

    S2 var2          = { .a = 0xFFFFFFFF, .b = 0xAA };
    static S2 var2_s = { .a = 0xFFFFFFFF, .b = 0xAA };
    
    printf("\nInt is first, then char:\n");
    print_bytes(&var2,   sizeof(S2));
    print_bytes(&var2_s, sizeof(S2));
}