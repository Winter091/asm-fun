#include "stdio.h"

#define SIZE 2048

int main(int argc, const char* argv[])
{
    unsigned char c[SIZE];

    for (int i = 0; i < SIZE; i++) {
        if (i % 16 == 0 && i)
            putc('\n', stdout);
        printf("%02X ", c[i]);
    }
    putc('\n', stdout);
}