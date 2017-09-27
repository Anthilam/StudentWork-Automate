CFLAGS=-c -Wall -std=c99 -O2 -g -o
PROGS=testfa

all: $(PROGS)

testfa: fa.o testfa.o
	gcc -g -Wall -std=c99 -o testfa $^ -lcunit

testfa.o: testfa.c fa.h
	gcc $(CFLAGS) testfa.o $< -lcunit

fa.o: fa.c
	gcc $(CFLAGS) fa.o $<

clean:
	rm -f *.o

mrproper: clean
	rm -f testfa
