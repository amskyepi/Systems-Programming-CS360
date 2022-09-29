#include "main.h"

void newItem(NODE **ht, unsigned long long size, char *pair){
    unsigned long long hash = crc64(pair);
    int key = hash % size;

    if(ht[key] == NULL){
        NODE *head = NULL;
        newNode(&head, pair);
        ht[key] = head;
        return;
    }

    NODE *head = ht[key];
    newNode(&head, pair);
    return;
}

