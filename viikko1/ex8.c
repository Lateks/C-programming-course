/* Write a function that returns the greatest common divisor
of two integers.

Both versions of the function run in 0.002 seconds for the
given long integers. In other words, there is no discernible
difference in performances. */
#include <stdio.h>
#include "euclid.h"

int main() {
    long int a = 98765432198765, b = 123456789012345;
    printf("%ld\n", gcd_rec(a, b));
    printf("%ld\n", gcd_rec(a, b));
    
    return 0;
}
