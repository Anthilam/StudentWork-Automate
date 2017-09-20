CFLAGS=-c -Wall -std=c99 -O2 -g -o
PROGS=testfa

all: $(PROGS) 

testfa: fa.o testfa.o
	gcc -g -Wall -std=c99 -o testfa $^

testfa.o: testfa.c fa.h
	gcc $(CFLAGS) testfa.o $<

fa.o: fa.c states.o
	gcc $(CFLAGS) fa.o $<

states.o: states.c states.h 
	gcc $(CFLAGS) states.o $<

clean:
	rm -f *.o

mrproper: clean
	rm -f testfa
