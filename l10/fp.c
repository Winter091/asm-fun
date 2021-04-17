#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#define BIT_TOGGLE(num, index) (num) |= (1 << (index))
#define BIT_CLEAR(num, index)  (num) &= ~(1 << (index))

#define BIT_SET_VALUE(num, index, bit)  \
    if (bit)                            \
        BIT_TOGGLE(num, index);         \
    else                                \
        BIT_CLEAR(num, index)

void print_bits(float a)
{
    int num = *(int*)(&a);

    printf("%12.50f: \033[0;31m %d \033[0;35m", a, ((num & (1 << 31)) >> 31) ? 1 : 0);

    for (int i = 30; i > 22; i--)
        printf("%d", ((num & (1 << i)) >> i) ? 1 : 0);

    printf("\033[0;33m ");

    for (int i = 22; i >= 0; i--)
        printf("%d", ((num & (1 << i)) >> i) ? 1 : 0);
    
    printf("\033[0m\n");
}

void set_sign(float* a, int sign)
{
    uint32_t* b = (uint32_t*)a;
    BIT_SET_VALUE(*b, 31, sign);
}

void set_exponent(float* a, uint8_t bits)
{
    uint32_t* b = (uint32_t*)a;

    for (int i = 0; i < 8; i++) {
        int bit = (bits & (1 << (7 - i))) >> (7 - i);
        BIT_SET_VALUE(*b, 30 - i, bit);
    }
}

// only 23 least significant bits are used
void set_mantissa(float* a, uint32_t bits)
{
    uint32_t* b = (uint32_t*)a;

    for (int i = 0; i < 23; i++) {
        int bit = (bits & (1 << (22 - i))) >> (22 - i);
        BIT_SET_VALUE(*b, 22 - i, bit);
    }
}

int main(int argc, char* argv[])
{
    float a;
    set_sign(&a, 0);
    set_exponent(&a, 0x00);
    
    set_mantissa(&a, 0x00000000);
    print_bits(a);

    set_mantissa(&a, 0x00000001);
    print_bits(a);
}
