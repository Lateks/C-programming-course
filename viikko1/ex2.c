/* Task: Write a program which prints the values of three
variables. The types of the variables are char, int, and
float. Test with different values. */
#include <stdio.h>

int main()
{
    char k = 'k', punct = '@';
    int a = 1, b = 1337;
    float pi = 3.14159, e = 2.718;

    printf("char: %c\ninteger: %d\npi: %.5f\n***\n", k, a, pi); 
    printf("symbol: %c\ninteger: %d\nEuler's constant: %.3f", punct, b, e);

    return 0;
}
