#
#  NAME:    John Graham
#  PLEDGE:  I pledge my honor that I have abided by the Stevens Honor System.
#  
#  FILE: 	Makefile
#


CC = gcc
CFLAGS = -c -g


all: minishell clean

minishell: minishell.o
	$(CC) minishell.o -o minishell

minishell.o: minishell.c
	$(CC) $(CFLAGS) minishell.c

clean:
	rm *.o