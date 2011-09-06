/* Task: Write a program which prints different decimal numbers.
Change the precision of the outputs. Also, use output fields of
different sizes.*/
#include <stdio.h>

int main()
{
    float pi = 1.14159, eplus100 = 102.7182818284;

    printf("%f\n%.5f\n%.2f\n%10.2f\n", pi, pi, pi, pi);
    printf("%f\n%.3f\n%2.2f\n", eplus100, eplus100, eplus100);

    return 0;
}
