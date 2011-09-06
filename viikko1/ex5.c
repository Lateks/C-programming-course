/* As the previous program, but now the program reads
several names one after another. Design how to inform
the program that there are no more names. */
#include <stdio.h>

int main()
{
    char forename[20], surname[20];
    int year;
    char more_names = 'y';

    do {
        printf("Enter your forename: ");
        scanf("%s", forename);
        printf("Enter your surname: ");
        scanf("%s", surname);
        printf("Enter your year of birth: ");
        scanf("%d", &year);

        printf("%s %s %d\n", forename, surname, year);
        
        do {
            printf("Enter another name? (y/n) ");
            getchar(); /* flush \n from the input buffer */
            more_names = getchar();
        } while (more_names != 'y' && more_names != 'n');
    } while(more_names == 'y');

    return 0;
}

