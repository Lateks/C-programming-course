/* Reads character strings separated by # from a text file into a two
dimensional array, sorts them into alphabetical order and displays the
list in order. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEN 1000

/* Reads the strings in the file pointed to by fptr into
the given char pointer array. */
int read_strings(FILE *fptr, char* array[]) {
    int ch, str_len;
    int strings = 0;
    int last_hash = 0;
    int eof_reached = 0;
    int i = 0;
    while ((ch = getc(fptr))) {
        if (!(eof_reached = (ch == EOF)))
            ++i;
        if (ch == '#' || eof_reached) {
            str_len = i - last_hash;
            char* string = (char*) malloc(str_len*sizeof(char));
            fseek(fptr, -str_len, SEEK_CUR);

            fread(string, str_len - 1, 1, fptr);
            array[strings] = string;
            strings++;

            if (eof_reached)
                break;
            if (strings >= LEN) {
                fprintf(stderr, "Too many strings, sorting the first %d.", LEN);
                break;
            }

            getc(fptr);
            last_hash = i;
        }
    }
    return strings;
}

void print_array(char* array[], int len) {
    for (int i = 0; i < len; i++)
        printf("%s\n", array[i]);
}

void shellsort(char* array[], int len) {
    int inc = round((float) len/2.0);
    while (inc > 0) {
        for (int i = inc; i < len; i++) {
            char* temp = array[i];
            int j = i;
            while (j >= inc && strcmp(array[j-inc], temp) > 0) {
                array[j] = array[j-inc];
                j = j-inc;
            }
            array[j] = temp;
        }
        inc = round((float) inc/2.2);
    }
}

int main(int argc, char* argv []) {
    FILE* fptr;
    char* array[LEN];

    if (argc < 2) {
        fprintf(stderr, "Usage: stringsort filename.\n");
        exit(1);
    }
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s.\n", argv[1]);
        exit(2);
    }

    int strings = read_strings(fptr, array);

    shellsort(array, strings);
    print_array(array, strings);

    exit(0);
}
