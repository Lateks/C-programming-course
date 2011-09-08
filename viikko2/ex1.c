#include <stdio.h>

int main()
{
    int i, j=25;
    int *pi, *pj=&j; /* pj points to an address that constains a pointer to j */
    *pj=j+5; /* essentially equivalent to j = j + 5, j = 30 */
    i= *pj+5; /* similarly equivalent to i = j + 5, i = 35 and j = 30 */
    pi=pj; /* pi is now a pointer to an address that points to j */
    *pi=i+j; /* j = i + j, j = 65 */

    printf("i: %d\nj: %d\n", i, j);
    printf("%d %d\n", (pi == pj), (*pi == *pj));
}
/*
Test experimentally and explain the results:
a) After the definitions, what values are represented by i, j, &i, &j?
    i == 35, &i is the memory address of the variable i
    j == 65, &j is the memory address of the variable j

b) After the definitions, what values are represented by pi, pj, *pi, *pj?
    pi is a pointer to an address that points to j
    pj is the same
    *pi is a pointer to j
    *pj is the same

c) After the first statement, what values are represented by pj and *pj;
    pj points to *pj which points to the variable j

d) After the second statement, what value is represented by i?
    i is uninitialized, so as a local variable it has no value
    If i was a static/global variable, it would have been initialized to zero.

e) After the third statement, what values are represented by pi and *pi?
    pi points to a memory address
    *pi (the contents of the memory address) has not been initialized

f) After the fourth statement, what values are represented by pi and *pi?
    pi and *pi have not been changed after the third statement.
    (After the _fifth_ statement pi points to another address, the same as
    pj, and therefore *pi == *pj.)
*/
