#include "main.h"

//MAIN//
int main(int argc, const char* argv[]){

    FILE *fp = fopen(argv[1], "r"); //saves file to pointer

    if(argc == 1){ //not enough arguments, need file to read in
        fprintf(stderr,"No file is specified. Please enter command as: program <-count> file1 <file2> <file3> ...\n");
        return (-1);
    }
	//initialize hash table
        unsigned long long size = 1000; //number of buckets, I know I didn't make it grow :(

        NODE **ht = getHT(size);
        for (int i = 0; i < size; i++){
            ht[i] = NULL;
        }
        char *pair, *tmp2, *tmp1 = getNextWord(fp);
        while((tmp2 = getNextWord(fp))){
            //malloc for concatenated pair
	    pair = malloc(strlen(tmp1)+strlen(tmp2)+2);
            strcpy(pair, tmp1);
            pair = strcat(pair, " ");
            pair = strcat(pair, tmp2);
            free(tmp1);
            //save tmp2 for next pair in loop
            tmp1 = tmp2;
            //send pair to be inserted
            newItem(ht,size,pair);
            }
        dumpHash(ht, size);
        free(tmp1);
        fclose(fp);
        free(ht);
    	return 0;
}


