/**
 * NAME:    John Graham
 * PLEDGE:  I pledge my honor that I have abided by the Stevens Honor System.
 * 
 * FILE:    spfind.c
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
        if(dup2(fd[WRITE_END], STDOUT_FILENO)==-1) { //dup the write end into stdout (output of pfind will go to pipe)
            perror("dup2");
            close(fd[WRITE_END]);
            exit(EXIT_FAILURE);
        }
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
        int fd_new[2]; //initialize a second set of pipe fds
        if(pipe(fd_new) != 0) { //create a pipe! (again!)
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        if((ch2=fork()) < 0) { //fork a child to execute sort
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if(ch2==0) { //in the second child...
            close(fd_new[READ_END]); //close new read end (unneeded)
            if(dup2(fd[READ_END], STDIN_FILENO)==-1) { //dup the read end into stdin (input to sort will be data in the pipe, which is output of pfind)
                perror("dup2");
                close(fd[READ_END]);
                close(fd_new[WRITE_END]);
                exit(EXIT_FAILURE);
            }
            close(fd[READ_END]); //close read end (unneeded)
            if(dup2(fd_new[WRITE_END], STDOUT_FILENO)==-1) { //dup the new write end into stdout (output of sort will be passed into the new pipe, which will go back to the parent)
                perror("dup2");
                close(fd_new[WRITE_END]);
                exit(EXIT_FAILURE);
            }
            close(fd_new[WRITE_END]); //close new write end (unneeded)
            execlp("sort", "sort", NULL); //execute sort!
            fprintf(stderr, "Error: sort failed.\n"); //print error if failed
            exit(EXIT_FAILURE);
        }
        else { //in the parent...
            close(fd[READ_END]); //close read end (unneeded)
            close(fd_new[WRITE_END]); //close new write end (unneeded)
            int stat_sort;
            wait(&stat_sort); //wait for sort to finish
            if(stat_sort!=0) {
                exit(EXIT_FAILURE);
            }
            int matches=0; //counter for total matches

            //code below is from my hw4 lmao
            int i=0; //counter of total bytes read
            char* temp=malloc(128); //initially has 128 bytes in the buffer
            int eof_checker; //checks for end of file
            char buf_byte; //current byte being read from the file
            while(1) {
                eof_checker=read(fd_new[READ_END], temp+i, 1); //attempt to read into dst[i]
                if(eof_checker==-1) { //read error
                    perror("read");
                    free(temp);
                    close(fd_new[READ_END]);
                    exit(EXIT_FAILURE);
                }
                else if(eof_checker==0) { //if we've reached end of file...
                    break; //...break from loop!
                }
                buf_byte=*((char*)temp+i); //access the most recently read byte
                if(buf_byte=='\n') { //if the read byte is a newline...
                    matches++; //...increment the matches counter!
                }
                i++; //increment counter
                if(i%128==0) { //if we've reached a size limit...
                    temp=realloc(temp, 128+i); //...then reallocate an additional 128 bytes
                }
            }
            //code above from hw4

            if(write(STDOUT_FILENO, temp, i)==-1) { //write all of the read bytes to stdout
                perror("write");
                free(temp);
                close(fd_new[READ_END]);
                exit(EXIT_FAILURE);
            }
            printf("Total matches: %d\n", matches); //print the total matches
            close(fd_new[READ_END]); //close new read end (unneeded)
            free(temp); //free the buffer
        }
    }
    exit(EXIT_SUCCESS);
}