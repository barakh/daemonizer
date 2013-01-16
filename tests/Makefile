CC = gcc
CFLAGS = -pedantic -Wall -Wextra -g
LDFLAGS = -L../ -ldaemonizer -lreadline

all: test1 test2
	./test1
	./test2

test1:	test1.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -otest1 test1.c $(LDFLAGS)

test2:	test2.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -otest2 test2.c $(LDFLAGS) 

clean:
	rm -f test1 test2
