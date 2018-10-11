mystat: mystat.o mystat_funcs.o
	gcc -o mystat mystat.o mystat_funcs.o
mystat.o: mystat.c mystats.h
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -Werror -c mystat.c
mystat_funcs.o: mystat_funcs.c mystats.h
	gcc -ggdb3 -std=gnu99 -pedantic -Wall -Werror -c mystat_funcs.c 
.PHONY: clean
clean:
	rm -f mystat *.o *.c~ *.h~ *#
