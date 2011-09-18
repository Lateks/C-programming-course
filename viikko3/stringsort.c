/* Reads character strings separated by # from a text file into a two
dimensional array, sorts them into alphabetical order and displays the
list in order. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

            getc(fptr);
            last_hash = i;
        }
    }
    return strings;
}

// void sort(char* array);

int main(int argc, char* argv []) {
    FILE* fptr;
    char* array[1000];

    if (argc < 2) {
        fprintf(stderr, "Usage: stringsort filename.\n");
        exit(1);
    }
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s.\n", argv[1]);
        exit(2);
    }

    int strings = read_strings(fptr, array);

    for (int j = 0; j < strings; j++)
        printf("%s\n", array[j]);

    exit(0);
}
