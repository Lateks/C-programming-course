#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Fisher-Yates shuffle */
void shuffle_ints(int* array, int len)
{
    do {
        int j = rand()/((float) RAND_MAX)*(len);
        int temp = array[len-1];
        array[len-1] = array[j];
        array[j] = temp;
    } while(--len);
}

int main()
{
    srand(time(NULL));
    int len = 7;
    int nums[] = { 0, 1, 2, 3, 4, 5, 6 };
    shuffle_ints(nums, len);

    for (int i = 0; i < len-1; i++)
        printf("%d, ", nums[i]);
    printf("%d\n", nums[len-1]);

    return 0;
}
