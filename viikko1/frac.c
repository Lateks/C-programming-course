#include <stdio.h>
#include "euclid.h"

struct fraction {
    int num;
    int denom;
};

void simplify(struct fraction * frac)
{
    long int div = gcd_rec(frac->num, frac->denom);
    frac->num /= div;
    frac->denom /= div;

    if (frac->denom < 0)
    {
        frac->num *= -1;
        frac->denom *= -1;
    }
}

/* Task 9: Make a function fr-add(f1, f2) which returns the
sum of fractions f1 and f2. */
struct fraction fr_add(struct fraction * f1, struct fraction * f2)
{
    struct fraction newfrac;
    newfrac.num = f1->num * f2->denom + f2->num * f1->denom;
    newfrac.denom = f1->denom * f2->denom;
    simplify(&newfrac);

    return newfrac;
}

/* Task 10: Make a function fr-sub(f1, f2) which returns the subtraction
of f2 from f1.*/
struct fraction fr_sub(struct fraction * f1, struct fraction * f2)
{
    struct fraction newfrac;
    newfrac.num = f1->num * f2->denom - f2->num * f1-> denom;
    newfrac.denom = f1->denom * f2->denom;
    simplify(&newfrac);

    return newfrac;
}

/* Task 11: Make a function fr-mul(f1, f2) which returns the multiplication
of f1 and f2.*/
struct fraction fr_mul(struct fraction * f1, struct fraction * f2)
{
    struct fraction newfrac;
    newfrac.num = f1->num * f2->num;
    newfrac.denom = f1->denom * f2->denom;
    simplify(&newfrac);

    return newfrac;
}

/* Task 12: Make a function fr-div(f1, f2) which returns the division of
f1 by f2.*/
struct fraction fr_div(struct fraction * f1, struct fraction * f2)
{
    struct fraction newfrac;
    newfrac.num = f2->denom;
    newfrac.denom = f2->num;
    
    return fr_mul(f1, &newfrac);
}

void printeq(char operator, struct fraction * frac1,
        struct fraction * frac2, struct fraction * resultfrac)
{
    printf("%d/%d %c %d/%d = %d/%d\n", frac1->num, frac1->denom, operator,
        frac2->num, frac2->denom, resultfrac->num, resultfrac->denom);
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
    printeq('+', &frac1, &frac2, &fracsum);

    struct fraction fracdiff = fr_sub(&frac1, &frac2);
    printeq('-', &frac1, &frac2, &fracdiff);

    struct fraction fracprod = fr_mul(&frac1, &frac2);
    printeq('*', &frac1, &frac2, &fracprod);

    struct fraction fracquot = fr_div(&frac1, &frac2);
    printeq('/', &frac1, &frac2, &fracquot);

    return 0;
}
