#include <stdio.h>

void print_doubles(double* array, int len)
{
    for (int i; i < len-1; i++)
        printf("%.5f, ", array[i]);
    printf("%.5f\n", array[len-1]);
}

int main(void)
{
    double nums[5] = { 3.14159, 2.71828, 1.41421, 1.61803, 4.66920 };
    print_doubles(nums, 5);

    return 0;
}
