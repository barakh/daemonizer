CC = gcc
CFLAGS = -pedantic -Wall -Wextra -g

all: libdaemonizer.a

clean:
	rm -f *.o *.a
	-for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done

test: all
	cd tests; $(MAKE)

daemonizer.o: daemonizer.c daemonizer.h
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o$@ -c daemonizer.c $(LDFLAGS)

libdaemonizer.a: daemonizer.o
	ar rcs $@ daemonizer.o
