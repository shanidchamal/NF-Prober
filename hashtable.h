#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "candidate.h"

typedef struct HashTable {
    int size;
    int key_count;
    Candidate **table;
}HashTable;

#endif // HASHTABLE_H
