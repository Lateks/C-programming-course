/* Program received signal SIGSEGV, Segmentation fault.
0x00007ffff7aca5d1 in ?? () from /lib/x86_64-linux-gnu/libc.so.6*/

#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
    /* Corrected from i<=argc. */
    for (int i = 0; i < argc; ++i)
    {
    printf("%s\n", argv[i]);
    }
    exit(EXIT_SUCCESS);
}

