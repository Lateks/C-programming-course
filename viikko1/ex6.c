#include <stdio.h>

int main()
{
    int i = 113, j = 12345;
    long ix = 1234567890;
    short s = 5043;
    float x = 1.14159;
    double dx = 1.1415927;
    char c = 'G';
    unsigned long ux = 2134567890;

    printf("a: %d\n", i + c);
    printf("b: %f\n", x + c);
    printf("c: %f\n", dx + x);
    printf("d: %ld\n", ((int) dx) + ix);
    printf("e: %f\n", i + x);
    printf("f: %d\n", s + j);
    printf("g: %ld\n", ix + j);
    printf("h: %hd\n", s + c);
    printf("i: %ld\n", ix + c);
    printf("j: %lu\n", ix + ux);

    return 0;
}
