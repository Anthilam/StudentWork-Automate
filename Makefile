CFLAGS=-c -Wall -std=c99 -Iinclude -g -fprofile-arcs -ftest-coverage

MATH=-lm
CXX = c++
CXXFLAGS = -Wall -O2 -g -Iinclude -Itests -Itests/include -fprofile-arcs -ftest-coverage

LIBDIR=lib

LIBFA_OBJ = $(LIBDIR)/fa.o

RUNTESTS_OBJ = tests/src/gtest-all.o tests/test_fa.o

PROGS=run_tests libfa.a

MATH=-lm

all: $(PROGS)

libfa.a: $(LIBFA_OBJ)
	ar cru $@ $(LIBFA_OBJ)

run_tests: run_tests.cc $(RUNTESTS_OBJ) libfa.a
	$(CXX) $(CXXFLAGS) $< -o $@ $(RUNTESTS_OBJ) -L. -lfa -lpthread -lgcov --coverage

testfa: $(LIBDIR)/fa.o testfa.o
	gcc -g -Wall -std=c99 -o testfa $^ $(MATH)

testfa.o: testfa.c include/fa.h
	gcc $(CFLAGS) $< -o testfa.o $< $(MATH) -lgcov --coverage

coverage: run_tests
	./run_tests
	./lcov/bin/lcov -c -d '.' -o coverage.info
	./lcov/bin/genhtml coverage.info --output-directory html

clean:
	rm -f *.o
	rm -f $(LIBDIR)/*.o
	rm -f tests/*.gcno
	rm -f tests/*.gcda
	rm -f lib/*.gcda
	rm -f tests/*.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.info
	rm -f ./lib/*.gcno
	rm -f print.txt

mrproper: clean
	rm -f testfa
	rm -f libalgo.a
	rm -f run_tests
	rm -f libfa.a
