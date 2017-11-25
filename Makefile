CFLAGS=-c -Wall -std=c99 -O2 -g -o
PROGS=testfa

MATH=-lm

all: $(PROGS)

testfa: fa.o testfa.o
	gcc -g -Wall -std=c99 -o testfa $^ $(MATH)

testfa.o: testfa.c fa.h
	gcc $(CFLAGS) testfa.o $< $(MATH)

fa.o: fa.c
	gcc $(CFLAGS) fa.o $< $(MATH)

clean:
	rm -f *.o

mrproper: clean
	rm -f testfa
