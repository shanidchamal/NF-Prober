#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "candidate.h"
#include "bitset.h"

typedef struct HashTable {
    int size;
    int key_count;
    Candidate **table;
}HashTable;

HashTable *getNewHashTable(int size);
void destroyHashTable(HashTable *ht);
int insertHashTable(HashTable *ht,int name,Candidate *candidate);
int checkHashTable(HashTable *ht,int name,Candidate **candidate);

void printHashTable(HashTable *ht);

#endif // HASHTABLE_H
