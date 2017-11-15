CFLAGS=-c -Wall -std=c99 -O2 -Iinclude -g -o

CXX = c++
CXXFLAGS = -Wall -O2 -g -Iinclude -Itests -Itests/include

LIBDIR=lib

LIBFA_OBJ = $(LIBDIR)/fa.o

RUNTESTS_OBJ = tests/src/gtest-all.o tests/test_fa.o run_tests.o

PROGS=testfa run_tests libfa.a

all: $(PROGS)

test: run_tests
	./run_tests

libfa.a: $(LIBFA_OBJ)
	ar cru $@ $(LIBFA_OBJ)

run_tests: $(RUNTESTS_OBJ) libfa.a
	$(CXX) -o $@ $(RUNTESTS_OBJ) -L. -lfa -lpthread

testfa: $(LIBDIR)/fa.o testfa.o
	gcc -g -Wall -std=c99 -o testfa $^

testfa.o: testfa.c include/fa.h
	gcc $(CFLAGS) testfa.o $<


clean:
	rm -f *.o
	rm -f $(LIBDIR)/*.o

mrproper: clean
	rm -f testfa
	rm -f libalgo.a
	rm -f run_tests
