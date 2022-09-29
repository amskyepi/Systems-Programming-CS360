#include "main.h"

//takes in the current head of the linked list along with the associated word pair
//inserts a node to the tail of the list if it has the same key but does not match other 
//nodes in list.

void newNode(NODE **head, char *pair){
    //create new node - make space and initilaize it
    NODE *new = malloc(sizeof(NODE));
    new->word = pair;
    new->count = 0;
    new->next = NULL;
    new->count++;

    //for new head of linked list
    if(*head == NULL){
        *head = new;
        return;
    }
    //otherwise, if head already exists - traverse it and add new to tail
    //unless matching pair is found, where we incr counter instead
    NODE *curr = *head;
    while(curr != NULL){
        if(strcmp(curr->word, new->word) == 0){
            curr->count++;
	    free(new->word);
            free(new); //we don't need new after all
            return;
        }
        if(curr->next == NULL){
            curr->next = new;
            return;
        }
        curr = curr->next;
    }
}

