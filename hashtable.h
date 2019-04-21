#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "candidate.h"

typedef struct HashTable {
    int size;
    int key_count;
    Candidate **table;
}HashTable;

HashTable *getNewHashTable(int size);
int insertHashTable(HashTable *ht,int name,Candidate *candidate);

#endif // HASHTABLE_H
