#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INIT_SIZE 10

/* Dynamic array type */
typedef struct array {
    int* array;
    int used;
    int len;
} DynArray;

/* Constructor for the dynamic array type. */
DynArray* DynArray_create(void) {
    DynArray* new = (DynArray*) malloc(sizeof(DynArray));

    if (!new)
        return NULL;

    new->array = (int*) malloc(INIT_SIZE * sizeof(int));
    new->len = INIT_SIZE;
    new->used = 0;

    if (!new->array) {
        free(new);
        return NULL;
    }

    return new;
}

/* Destructor for the dynamic array type. */
void DynArray_destroy(DynArray* arr) {
    if (arr) { /* Do nothing if pointer is NULL. */
        free(arr->array);
        free(arr);
    }
}

/* Append a new value at the end of the array. Reallocate memory
if needed. */
bool DynArray_append(DynArray* arr, int number) {
    if (arr->used == arr->len) {
        int* temp = (int*) realloc(arr->array, 2*arr->len*sizeof(int));
        if (!temp)
            return false;
        arr->array = temp;
        arr->len *= 2;
    }
    arr->array[arr->used] = number;
    arr->used++;
    return true;
}

/* Return the value at the given index in the dynamic array. */
int DynArray_get(DynArray* arr, int index) {
    /* Return something even if out of bounds. Let the caller be
    responsible for using sensible indices. */
    return arr->array[index];
}

int main(void) {
    DynArray* arr = DynArray_create();
    for (int i = 0; i <= 25; i++) {
        if (!DynArray_append(arr, i)) {
            printf("Append fail.");
            return 1;
        }
    }
    printf("0: %d, 15: %d, 25: %d\n", DynArray_get(arr, 0),
        DynArray_get(arr, 15), DynArray_get(arr, 25));
    DynArray_destroy(arr);

    return 0;
}
