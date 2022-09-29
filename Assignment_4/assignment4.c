/***********************************************************************
Name: Amethyst Skye

Description: assignment4 -- acts as a pipe using ":" to seperate programs.

***********************************************************************/

/* Includes and definitions */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>

/**********************************************************************
./assignment4 <arg1> : <arg2>

    Where: <arg1> and <arg2> are optional parameters that specify the programs
    to be run. If <arg1> is specified but <arg2> is not, then <arg1> should be
    run as though there was not a colon. Same for if <arg2> is specified but
    <arg1> is not.
**********************************************************************/

int main (int argc, char *argv[]){

    int fd[2], i = 1, cnt1 = 0, cnt2 = 0;
    char *prog1, *prog2;
    char *argsLeft[argc], *argsRight[argc];

    //check if there is a lefthand arg
    if (strcmp(argv[1], ":") != 0) prog1 = argv[1];

    //process command line args into arrays
    while (i < argc){ //deal with stuff before ":"
                if (strcmp(argv[i], ":") == 0) break;

                else{
                    argsLeft[cnt1] = argv[i];
                    cnt1++;
                    i++;

                }
            }
            argsLeft[cnt1++] = (char *)NULL;

    while (i < argc){ //deal with stuff after ":"
                if (strcmp(argv[i], ":") == 0){
                    i++;
                    prog2 = argv[i];
                }

                else{
                    argsRight[cnt2] = argv[i];
                    cnt2++;
                    i++;
                }
            }
            argsRight[cnt2++] = (char *)NULL;

    if (pipe(fd) < 0){
        fprintf(stdout, "%s\n", strerror(errno));
        return (-1);
    }

        int pid1 = fork();
        if (pid1 == -1){
            fprintf(stdout, "%s\n", strerror(errno));
            return (-1);
        }

        else if (pid1 == 0){ //first child process for lefthand side of args
            if (prog2 != NULL) dup2(fd[1], 1);
            close(fd[0]); close(fd[1]);
            if (prog1 != NULL){
                if((execvp(prog1, argsLeft)) == -1){
                    fprintf(stdout, "%s\n", strerror(errno));
                    return (-1);
                }
            }
        }

    if (prog2 != NULL){

        int pid2 = fork();
        if (pid2 == -1){
            fprintf(stdout, "%s\n", strerror(errno));
            return (-1);
        }

        if (pid2 == 0){ //second child process for righthand side of args
            dup2(fd[0], 0);
            close(fd[0]); close(fd[1]);
            if (prog2 != NULL){
                if((execvp(prog2, argsRight)) == -1){
                    fprintf(stdout, "%s\n", strerror(errno));
                    return (-1);
                }
            }
        }

        close(fd[0]);
        close(fd[1]); //close both ends of pipe
        waitpid(pid2, NULL, 0);
    }
        close(fd[0]);
        close(fd[1]); //close both ends of pipe
        waitpid(pid1, NULL, 0);
        return 0;
}
