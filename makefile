CC  = g++
CXX = g++ -o

INCLUDES = -I

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++11

LDFLAGS = -g -L
LDLIBS  = 

test : test.o doubleChain.o

test.o: test.cpp linearList.h doubleChain.h

doubleChain.o: doubleChain.cpp linearList.h doubleChain.h

.PHONY: clean
clean:
	rm -f *~ a.out core *.o test

.PHONY: all
all: clean default
