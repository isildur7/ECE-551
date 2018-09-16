CFLAGS=-std=gnu99 -pedantic -Wall -Werror -ggdb3

functest: test-subseq.o maxSeq.o
	gcc -ggdb3 -o functest test-subseq.o maxSeq.o

test-subseq: test-subseq.c
	gcc -o test-subseq $(CFLAGS) test-subseq.c

maxSeq: maxSeq.c
	gcc -o maxSeq $(CFLAGS) maxSeq.c

.PHONY: clean
clean:
	rm -f functest *.o *.c~ *.h~

