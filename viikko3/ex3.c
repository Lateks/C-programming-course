/* A program that removes all empty lines from a text file. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv []) {
    int ch;
    bool prev_nonempty = false;
    FILE *fptr, *fout;

    if (argc < 2) {
        fprintf(stderr, "Usage: ex2 source_file [output_file]\n");
        exit(1);
    }

    if ((fptr = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s.\n", argv[1]);
        exit(3);
    }

    if (argc > 2) {
        if ((fout = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "Failed to open output file %s.\n", argv[2]);
            exit(2);
        }
    }
    else {
        fprintf(stderr, "No output file given, writing to standard output.\n");
        fout = stdout;
    }

    while ((ch = getc(fptr)) != EOF) {
        bool is_eol = (ch == '\n' || ch == '\r');
        if (!is_eol || prev_nonempty)
            putc(ch, fout);
        prev_nonempty = !is_eol;
    }
    fclose(fptr);

    exit(0);
}
