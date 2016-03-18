COMPILER = g++
COMPILER_OPTS = -c -g -O0 -Wall
LINKER = g++

test : test.o GetOpts.o
	$(LINKER) test.o GetOpts.o -o test

test.o : test.cpp GetOpts.hpp
	$(COMPILER) $(COMPILER_OPTS) test.cpp

clean :
	-rm -f *.o test
