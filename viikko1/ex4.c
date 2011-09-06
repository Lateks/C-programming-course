/* Task: Write a program that reads a forename, surname and
year of birth. Use the scanf function. Then the program prints
the names and the year one after another sequentially. */
#include <stdio.h>

int main()
{
    char forename[20], surname[20];
    int year;

    printf("Enter your forename: ");
    scanf("%s", forename);
    printf("Enter your surname: ");
    scanf("%s", surname);
    printf("Enter your year of birth: ");
    scanf("%4d", &year);

    printf("%s %s %d\n", forename, surname, year);

    return 0;
}
