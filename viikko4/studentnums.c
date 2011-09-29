#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void) {
    FILE* studentnums = fopen("studentnumbers.txt", "r");
    if (!studentnums) {
        fprintf(stderr, "Could not open file.");
        exit(1);
    }

    int line_len = 10;
    fseek(studentnums, 0, SEEK_END);
    unsigned long int len = ftell(studentnums);
    int nums_len = len/line_len;

    srand(time(NULL));
    unsigned int student;
    for (int i = 0; i < 3; i++) {
        fseek(studentnums, (int) (rand() / (float) RAND_MAX * nums_len) * line_len,
            SEEK_SET);
        fscanf(studentnums, "%u\n", &student);
        printf("%09u\n", student);
    }
    fclose(studentnums);

    exit(0);
}
