CC = gcc
CFLAGS = -c -Wall -g


all: pfind clean

pfind: pfind.o
	$(CC) pfind.o -o pfind

pfind.o: pfind.c
	$(CC) pfind.c $(CFLAGS)

clean:
	rm *.o