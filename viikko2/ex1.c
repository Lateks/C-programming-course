#include <stdio.h>

int main()
{
    int i, j=25;
    int *pi, *pj=&j;
    *pj=j+5; /* essentially equivalent to j = j + 5, j = 30 */
    i= *pj+5; /* similarly equivalent to i = j + 5, i = 35 and j = 30 */
    pi=pj;
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
    pi is uninitialized
    pj is a pointer to (memory address of) variable j
    *pi is uninitialized
    *pj is the same as the variable j (= 25)

c) After the first statement, what values are represented by pj and *pj;
   pj is a pointer to (memory address of) variable j
   *pj is the variable j, now incremented by 5 (= 30)

d) After the second statement, what value is represented by i?
    i is j + 5 which equals 35.

e) After the third statement, what values are represented by pi and *pi?
    pi is the same pointer as pj
    *pi is the variable j which is still 30

f) After the fourth statement, what values are represented by pi and *pi?
    pi still points to the same memory address as pj
    *pi == *pj == j == 65
*/
