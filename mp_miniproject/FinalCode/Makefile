SOURCES=main.cpp parsing.cpp define.cpp test.cpp numint.cpp mcint.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++03

test: $(OBJS)
	g++ $(CPPFLAGS) -o numerics $(OBJS)
%.o: %.cpp parsing.h define.h expressions.h test.h numint.h mcint.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm numerics *~ *.o



