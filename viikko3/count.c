/* A program that counts the number of characters and words in a text file
(given as a command line argument. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv []) {
    FILE* fptr;
    int ch, prev;
    int words = 0;
    int chars = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: count filename.\n");
        exit(1);
    }
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Failed to open file %s.\n", argv[1]);
        exit(2);
    }

    while ((ch = getc(fptr)) != EOF) {
        chars++;
        if (isspace(ch) && !isspace(prev))
            words++;
        prev = ch;
    }
    
    if (!isspace(prev))
        words++;

    printf("Word and character counts for file %s:\n"
           "%d words\n%d characters\n", argv[1], words, chars);

    exit(0);
}
