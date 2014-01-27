CC = /usr/bin/gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
OBJECTS = main.o standard.o special.o

rechner :  $(OBJECTS)
	$(CC) -o rechner main.o special.o standard.o

standard.o : standard.c
	$(CC) $(CFLAGS) -c standard.c

special.o : special.c
	$(CC) $(CFLAGS) -c special.c
	
main.o : main.c
	$(CC) $(CFLAGS) -c main.c
