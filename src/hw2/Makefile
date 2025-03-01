# John Graham
# I pledge my honor that I have abided by the Stevens Honor System.
#
# Makefile

CC = gcc
CFLAGS = -c -Wall -g

all: isort clean

isort: main.o insertion.o utils.o
	$(CC) main.o insertion.o utils.o -o a.out

main.o: main.c
	$(CC) main.c $(CFLAGS)

insertion.o: insertion.c
	gcc insertion.c -c

utils.o: utils.c
	gcc utils.c -c

clean:
	rm *.o