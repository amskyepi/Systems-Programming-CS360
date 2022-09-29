#include "getWord.h"
#include "crc64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Linked List Definition
typedef struct _node{
    unsigned int count; //counts occurances of word pair
    char *word; //create space for word pair
    struct _node *next; //points to tail of LL
}NODE;

//function prototypes//

//newItem takes in a hash table, the size of the hash table, and the sequential pair which
//needs to be added. The function will check to see if there is an existing linked list in
//the index associated with the hash key produced by the given sequential pair(char *).
//Then the function sends the current bucket info along with the sequential pair to the 
//newNode function.
void newItem(NODE **, unsigned long long ,char *);

//newNode takes a pointer to the current head of the linked list which was selected via newItem.
//It also passes a pointer to a char which is the sequential pair being added to the hash table.
//If the sequential pair is already in the linked list, the counter is incremented.
void newNode(NODE **, char *);

//getHT will ingest a specified tablesize, and return an array of NODEs. This is used as 
//the hash table in the program. 
NODE **getHT(unsigned long long);

//dumpHash prints out all of the contents of the hashtable
void dumpHash(NODE **, unsigned long long);

//sortFun is a compare function which is used for the qsort() function
//This results in an array which is sorted in decending order.
int sortFun(const void *, const void *);
