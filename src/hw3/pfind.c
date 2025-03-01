/*
John Graham
I pledge my honor that I have abided by the Stevens Honor System

pfind
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


/**Recursively searches from the base directory for all files matching target_perms*/
void print_matches(__mode_t target_perms) {
    char* dirpath=getcwd(NULL, 0);
    DIR* curr_dir=opendir(dirpath); //opens cwd
    struct dirent* curr_ent;
    while((curr_ent=readdir(curr_dir))!=NULL) { //curr_ent = all files/directories within the current directory
        struct stat file;
        stat(curr_ent->d_name, &file); //grab current file info
        if(strcmp(curr_ent->d_name, ".")!=0 && strcmp(curr_ent->d_name, "..")!=0) { //avoiding making function calls on . and ..
            if(S_ISDIR(file.st_mode)) { //if current file is a directory...
                if(chdir(curr_ent->d_name)!=0) { //...we cd into that directory...
                    fprintf(stderr, "Error: Cannot open directory '%s%s%s'. Permission denied.\n", dirpath, "/", curr_ent->d_name); //...if we can't access it, then print error and skip :(
                }
                else {
                    print_matches(target_perms); //...otherwise, make another call now that we are in a new directory
                    chdir(".."); //return to original directory
                }
            }
            else { //...otherwise, if its a file
                __mode_t perms=file.st_mode & 0b0000111111111111; //extract the permission bits (12 rightmost bits)
                if(perms==target_perms) { //if the perms match...
                    printf("%s%s%s\n", dirpath, "/", curr_ent->d_name); //..then print the file path!
                }
            }
        }
    }
    free(dirpath); //freeing the space malloced by getcwd()
    closedir(curr_dir); //close the dir opened by opendir()
}

/**Main function, handles any input errors, then makes a call to print_matches*/
int main(int argc, char** argv) {
    char* perms=argv[2]; //permission string
    if(strlen(perms)!=9) { //print error if length!=9
        fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perms);
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<9; i++) { //loop for checking that the perm characters are correct
        if(i%3==0) { // r permission
            if(perms[i]!='r' && perms[i]!='-') {
                fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perms);
                exit(EXIT_FAILURE);
            }
        }
        else if(i%3==1) { // w permission
            if(perms[i]!='w' && perms[i]!='-') {
                fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perms);
                exit(EXIT_FAILURE);
            }
        }
        else { //i%3==2 -> x permission
            if(perms[i]!='x' && perms[i]!='-') {
                fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", perms);
                exit(EXIT_FAILURE);
            }
        }
    } //error checking complete (yay!)

    if(chdir(argv[1])!=0) { //cd into the directory specified in the command line...
        fprintf(stderr, "Error: Cannot open directory '%s'. Permission denied.\n", argv[1]);
        exit(EXIT_FAILURE); //...exit with an error if it's not readable
    }
    __mode_t target_perms=0;
    if(perms[0]!='-') { //user r
        target_perms+=0400; //preceeding '0' means octal number
    }
    if(perms[1]!='-') { //user w
        target_perms+=0200;
    }
    if(perms[2]!='-') { //user x
        target_perms+=0100;
    }
    if(perms[3]!='-') { //group r
        target_perms+=0040;
    }
    if(perms[4]!='-') { //group w
        target_perms+=0020;
    }
    if(perms[5]!='-') { //group x
        target_perms+=0010;
    }
    if(perms[6]!='-') { //other r
        target_perms+=0004;
    }
    if(perms[7]!='-') { //other w
        target_perms+=0002;
    }
    if(perms[8]!='-') { //other x
        target_perms+=0001;
    }

    print_matches(target_perms); //make a call to the print function
    exit(EXIT_SUCCESS); //finished!
}