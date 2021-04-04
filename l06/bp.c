#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void exit_usage()
{
    printf("Usage: bp <method>, where method is 'branch', 'mul' or 'and'\n");
    exit(1);
}

// Compile with -fno-if-conversion -fno-if-conversion2

int main(int argc, const char* argv[])
{
    if (argc < 2)
        exit_usage();

    int method = -1;
    if (!strcmp(argv[1], "branch"))
        method = 0;
    else if (!strcmp(argv[1], "mul"))
        method = 1;
    else if (!strcmp(argv[1], "and"))
        method = 2;

    if (method == -1)
        exit_usage();

    unsigned int num = 0xfcb5a2b8; 

    if (method == 0) {
        for (int i = 0; i < 1000000000; i++) {
            unsigned int lsb = num & 1;
            num >>= 1;
            if (lsb)
                num ^= 0xb400;
        }
    } else if (method == 1) {
        for (int i = 0; i < 1000000000; i++) {
            unsigned int lsb = num & 1;
            num >>= 1;
            num ^= 0xb400 * lsb;
        }
    } else if (method == 2) {
        for (int i = 0; i < 1000000000; i++) {
            unsigned int lsb = num & 1;
            num >>= 1;
            num ^= 0xb400 & -lsb;
        }
    }

    return num;
}
