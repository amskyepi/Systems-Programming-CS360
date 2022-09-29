#include "main.h"

NODE **getHT(unsigned long long tablesize){
    NODE **hashTable = calloc(tablesize, (sizeof(NODE) * tablesize));
    return hashTable;
}
