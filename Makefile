CFLAGS=-c -Wall -std=c99 -Iinclude -g -o

MATH=-lm
CXX = c++
CXXFLAGS = -Wall -O2 -g -Iinclude -Itests -Itests/include -fprofile-arcs -ftest-coverage

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
	$(CXX) $(CXXFLAGS) -o $@ $(RUNTESTS_OBJ) -L. -lfa -lpthread --coverage

testfa: $(LIBDIR)/fa.o testfa.o
	gcc -g -Wall -std=c99 -o testfa $^ $(MATH)

testfa.o: testfa.c include/fa.h
	gcc $(CFLAGS) testfa.o $< $(MATH)

coverage:
	./lcov/bin/lcov -c -d '.' -o coverage.info
	./lcov/bin/genhtml coverage.info --output-directory html

clean:
	rm -f *.o
	rm -f $(LIBDIR)/*.o
	rm -f tests/test_fa.gcno
	rm -f tests/*.o
	rm -f run_tests.gcno

mrproper: clean
	rm -f testfa
	rm -f libalgo.a
	rm -f run_tests
	rm -f libfa.a
