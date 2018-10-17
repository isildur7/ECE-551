CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
intArrayTest: IntArray.o test.o
	g++ -o intArrayTest $(CCFLAGS) IntArray.o test.o
Test: IntArray.o test1.o
	g++ -o yTest $(CCFLAGS) IntArray.o test1.o
%.o: %.cpp IntArray.h
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ intArrayTest
