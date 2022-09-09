/***********************************************************************
Name: Amethyst Skye
    readable -- recursively count readable files.
Description:
    See CS 360 Files and Directories lectures for details.
***********************************************************************/

/* Includes and definitions */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

/**********************************************************************
Take some path as input. Recursively count the files that are readable.
If a file is not readable, do not count it. Return the negative value
of any error codes you may get. However, consider what errors you want
to respond to.
**********************************************************************/

int readable(char* inputPath) {

    DIR *dir;
    struct stat s;
    struct dirent *dirp;
    int count = 0; //count num of reg files
    char buffer[PATH_MAX + 1];
    char *cwd = getcwd(buffer, sizeof(buffer));

    if (inputPath == NULL){ //if no path is given, we default to cwd
        if (access(cwd, R_OK | X_OK) == -1) return(-errno);
        else inputPath = cwd;
    }
    //otherwise, path is present
    if (lstat(inputPath, &s) == 0){
        if (s.st_mode & S_IFREG) {
            if (access(inputPath, R_OK) == -1) return(-errno); //file not readable
            else return 1;
        }
    }
    dir = opendir(inputPath);
    if(dir == NULL) return(-errno);
    else {
        if((chdir(inputPath)) != 0) return(-errno);
    }

    while ((dirp = readdir(dir)) != NULL){
        //if we encounter a reg file
        if ((dirp->d_type & DT_REG) && (access(dirp->d_name, R_OK) == 0) )  count++; //incr count

        //if we encounter another directory
        else if(dirp->d_type & DT_DIR){
            cwd = getcwd(buffer, sizeof(buffer));
            strcat(cwd, "/");
            strcat(cwd, dirp->d_name); //cwd = path name

            if((access(cwd, R_OK | X_OK) == 0) && (strcmp(dirp->d_name, ".") != 0) && (strcmp(dirp->d_name, "..") != 0)){
                count = count + readable(dirp->d_name);

            }
        }
    }
    chdir("..");
    closedir(dir);
    return count;
}

int main(){
    printf("Total files: %d\n", readable("/home/amskye"));
    return 0;
}
