/***********************************************************************
Name: Amethyst Skye

Assignment 2: lineNum -- see if a word is in the online dictionary

Description:

This function returns the line number where a specified word exists in the
dictionary which is passed to it. Using a binary search, this function will start by
searching at the very middle of the dictionary, and then moving to the left or right
of the dictionary depending on the value of the word which is being searched.

Return:

- If the return value is positive, this indicates that the specified word was found.
The number represents the line number that the word was found on.

- If the return value is negative, this indicates that the specified word was not
found. The number represents the line number that the function left off on when
attempting to search for the word.

***********************************************************************/

/* Includes and definitions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/**********************************************************************
Search for given word in dictionary using file descriptor fd.
Return the line number the word was found on, negative of the last line searched
if not found, or the error number if an error occurs.
**********************************************************************/

int lineNum(char *dictionaryName, char *word, int dictWidth) {

    char buffer[dictWidth]; //holds word from read

    //file descriptor will read the dictionaryName
    int fd = open(dictionaryName, O_RDONLY);

    //check if dict name exists
    if (fd < 0) { //should not return negative number
        fprintf (stderr, "Can't open %s for reading -- %s.\n", dictionaryName, strerror(errno));
        return(errno);
    }

    //add a space where there isn't in order to match the dict word format
    char passedWord[dictWidth];
    int i = 0;
    if (strlen(word) >= dictWidth){
        while(i < (dictWidth)){
            passedWord[i] = word[i]; //fill in chars
            i++;
        }
        passedWord[dictWidth -1] = '\0';
    }
    else{
        i = 0;
        while (i < strlen(word)){
            passedWord[i] = word[i]; //fill in chars
            i++;
        }
        i = strlen(word); //counter for elements in each string
        while (i < dictWidth - 1){
            passedWord[i] = ' '; //fill in spaces
            i++;
        }
        passedWord[i] = '\0'; //null terminate new word string with added spaces
    }

    int low = 0; //variable to keep track of lseek position
    int high = lseek(fd, low, SEEK_END);    //stores the total number of bytes in dict
    int mid = high/2 - dictWidth; //middle of file
    int loc = lseek(fd, mid, SEEK_SET); //starting location at middle of dict

    //compare each element of passedWord and buffer until a match is found. otherwise, exit
    while(low < mid && mid < high){
        lseek(fd, loc, SEEK_SET);
        read(fd, &buffer, dictWidth); //read string at loc in fd
        buffer[dictWidth - 1] = '\0';

        //if words match, exit
        if (strcmp(buffer, passedWord) == 0) return (loc/dictWidth + 1);

        //if buffer is greater than passedWord, go left
        else if (strcmp(buffer, passedWord) > 0){ //go to left for new buffer
            high = mid;
            mid = (low + high)/2;
            loc = mid - (mid%dictWidth);
            }

        //if buffer is less than passedWord, go right
        else if (strcmp(buffer, passedWord) < 0){ //go to right for new buffer
            low = mid;
            mid = (low + high)/2;
            loc = mid - (mid%dictWidth);
            }
    }

    close(fd);
    return (-loc/dictWidth -1);
}
