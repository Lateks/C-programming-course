#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Fisher-Yates shuffle */
void shuffle_ints(int* array, int len) {
    if (len < 2)
        return;
    srand(time(NULL));
    do {
        int j = rand()/((float) RAND_MAX)*(len);
        // another possible way to do this (might be biased)
        // int j = rand()%(len);
        int temp = array[len-1];
        array[len-1] = array[j];
        array[j] = temp;
    } while(--len > 1);
}

int main(void) {
    int len = 7;
    int nums[] = { 0, 1, 2, 3, 4, 5, 6 };
    shuffle_ints(nums, len);

    for (int i = 0; i < len-1; i++)
        printf("%d, ", nums[i]);
    printf("%d\n", nums[len-1]);

    return 0;
}
