/**
 * NAME:    John Graham
 * PLEDGE:  I pledge my honor that I have abided by the Stevens Honor System.
 * 
 * FILE:    spfind_old.c    (single pipe, does NOT print total matches)
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define READ_END    0
#define WRITE_END   1


int main(int argc, char** argv) {
    if(argc!=3) { //print usage message for incorrect numbers of args
        printf("Usage: ./spfind <directory> <permissions string>\n");
        exit(EXIT_SUCCESS); //TODO: exit success?
    }

    int fd[2]; //initialize pipe fds and child pids
    pid_t ch1, ch2;

    if(pipe(fd) != 0) { //create a pipe!
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if((ch1=fork()) < 0) { //fork a child to execute pfind
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(ch1==0) { //in the child...
        close(fd[READ_END]); //close read end (unneeded)
        dup2(fd[WRITE_END], STDOUT_FILENO); //dup the write end into stdout (output of pfind will go to pipe)
        close(fd[WRITE_END]); //close write end (unneeded)
        execlp("./pfind", "./pfind", argv[1], argv[2], NULL); //execute pfind!
        fprintf(stderr, "Error: pfind failed.\n"); //print error if failed 
        exit(EXIT_FAILURE);
    }
    else { //in the parent...
        close(fd[WRITE_END]); //close write end (unneeded)
        int stat_find;
        wait(&stat_find); //wait for pfind to finish
        if(stat_find!=0) {
            exit(EXIT_FAILURE);
        }
        if((ch2=fork()) < 0) { //fork a child to execute sort
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(ch2==0) { //in the second child...
            dup2(fd[READ_END], STDIN_FILENO); //dup the read end into stdin (input to sort will be data in the pipe, which is output of pfind)
            close(fd[READ_END]); //close read end (unneeded)
            execlp("sort", "sort", NULL); //execute sort!
            fprintf(stderr, "Error: sort failed.\n"); //print error if failed
            exit(EXIT_FAILURE);
        }
        else { //in the parent...
            close(fd[READ_END]); //close read end (unneeded)
            int stat_sort;
            wait(&stat_sort); //wait for sort to finish
            if(stat_sort!=0) {
                exit(EXIT_FAILURE);
            }
        }
    }
    exit(EXIT_SUCCESS);
}