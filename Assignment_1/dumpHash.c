#include "main.h"

void dumpHash(NODE **ht, unsigned long long size){

unsigned int count = 0; //used to count number of entries in hashtable

//for loop interates through each index in the hash array
    for(int i = 0; i < size; i++){
        NODE *curr;
    //skip any empty indicies
        if (ht[i] == NULL) continue;
        curr = ht[i];
    //traverse the linked list associated with current array index
        while(curr != NULL){
            count++; //increment counter to find the total number of entries in hashtable
            curr = curr->next;
        }
    }
//this will save all entries into a 1 dimensional array for qsort
    NODE array[count];
    unsigned int i = 0;
    NODE *curr;
        for(int j = 0; j < size; j++){
            if(ht[j] == NULL) continue;
            curr = ht[j];
	    while(curr != NULL){ //once we reach the end of the LL, we break out of loop
                array[i].count = curr->count;
                array[i].word = curr->word;
                i++;
                if(i == count) break;
                curr = curr->next;
            }
        }


    qsort(array, count, sizeof(NODE), sortFun);
//print out sorted entries
    for (int n = 0; n < count; n++){
        printf("%10d %s\n", array[n].count, array[n].word);
    }
//one last iteration to free each node from the hashtable
    for (int i = 0; i < size; i++){
        NODE *next, *curr;
        if (ht[i] == NULL) continue;
        curr = ht[i];
        while(curr != NULL){
	    next = curr->next;
            free(curr->word);
            free(curr);
            curr = next;
        }
    }
}



