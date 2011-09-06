/* Task: Write a function that takes an integer as a parameter
and returns its absolute value. */
#include <stdio.h>

int abs(int i)
{
    if (i < 0)
        return -i;
    else
        return i;
}

int main() {
    printf("%i\n", abs(-7654321));
    printf("%i\n", abs(1234567));
}
