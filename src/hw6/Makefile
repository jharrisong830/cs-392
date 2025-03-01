CC = gcc
CFLAGS = -c -Wall -g


all: spfind clean

spfind: spfind.o
	$(CC) spfind.o -o spfind

pfind.o: spfind.c
	$(CC) spfind.c $(CFLAGS)

clean:
	rm *.o