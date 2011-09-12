/* Shuffling function */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 5

void swap(void* a, void* b, size_t elem_size) {
    char* ca = a;
    char* cb = b;

    for (size_t i = 0; i < elem_size; i++) {
        char temp = ca[i];
        ca[i] = cb[i];
        cb[i] = temp;
    }

    return;
}

/* Fisher-Yates shuffle */
void shuffle(void* array, int len, size_t elem_size) {
    if (len < 2)
        return;
    srand(time(NULL)); /* Pass system time as seed for rand. */
    char* arr = array;
    do {
        int i = rand()/((float) RAND_MAX)*(len);
        swap(&arr[i*elem_size], &arr[(len-1)*elem_size], elem_size);
    } while (--len > 1);
}

void print_doubles(double* array, int len)
{
    for (int i = 0; i < len-1; i++)
        printf("%.5f, ", array[i]);
    printf("%.5f\n", array[len-1]);
}

int main(void) {
    double nums[LEN] = { 1.5, 3.5, 5.5, 7.5, 9.5 };
    shuffle(nums, LEN, sizeof(double));

    print_doubles(nums, LEN);

    return 0;
}
