CC=g++
CXXFLAGS =-std=c++11 -gdwarf-3 -Wall
CPPFLAGS += -O0
CPPFLAGS += -g
LDFLAGS += -g

test:	PrimitiveMap.o

PrimitiveMap.o: PrimitiveMap.hpp

clean:
	rm -f *.o core*

