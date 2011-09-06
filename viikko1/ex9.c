/* Task: Make a function fr-add(f1, f2) which returns the
sum of fractions f1 and f2. */
#include <stdio.h>
#include "euclid.h"

struct fraction {
    int num;
    int denom;
};

struct fraction fr_add(struct fraction * f1, struct fraction * f2)
{
    struct fraction newfrac;
    newfrac.num = f1->num * f2->denom + f2->num * f1->denom;
    newfrac.denom = f1->denom * f2->denom;

    long int div = gcd_rec(newfrac.num, newfrac.denom);
    newfrac.num /= div;
    newfrac.denom /= div;

    return newfrac;
}

int main()
{
    struct fraction frac1;
    struct fraction frac2;

    frac1.num = 1;
    frac1.denom = 2;
    frac2.num = 1;
    frac2.denom = 4;

    struct fraction fracsum = fr_add(&frac1, &frac2);
    printf("%d/%d + %d/%d = %d/%d\n", frac1.num, frac1.denom,
        frac2.num, frac2.denom, fracsum.num, fracsum.denom);

    return 0;
}
