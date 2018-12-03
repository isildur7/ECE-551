SOURCES=testprog.cpp parsing.cpp define.cpp test.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

test: $(OBJS)
	g++ $(CPPFLAGS) -o test $(OBJS)
%.o: %.cpp parsing.h define.h expressions.h test.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm test *~ *.o
