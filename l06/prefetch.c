#include "stdio.h"
#include "stdlib.h"

#define PREFETCH 0

int main()
{
    const int size = 100000000;
    volatile int* a = calloc(size, sizeof(int));
    volatile int* b = calloc(size, sizeof(int));

    const int offset = 3;

    for (int i = 0; i < size; i++) {
#if PREFETCH
        __builtin_prefetch(a + i + offset, 1, 1);
        __builtin_prefetch(b + i + offset, 0, 1);
#endif
        a[i] = i + a[i] + b[i];
    }

    return a[10000001];
}