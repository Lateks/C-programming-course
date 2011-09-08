CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Werror

all: ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 frac ex13

ex8.o: euclid.h

ex8: euclid.o

frac.o: euclid.h

frac: euclid.o

clean:
	rm -f ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 frac ex13 *.o
