#include "hashtable.h"
#include <stdio.h>
#include <malloc.h>

static int prime(int p);

static int prime(int p) {
    int i,j,flag=0;

    if(p==0||p==1)
        return 1;
    else if(p==2)
        return 3;
    else {
        i=p;
        while(1) {
            flag=0;
            for(j=2;j<=i/2;j++)
                if(i%j==0) {
                    flag=1;
                    break;
                }
            if(!flag)
                return i;
            i++;
        }
    }
}

HashTable *getNewHashTable(int size) {
    int i;
    HashTable *ht=NULL;
    Candidate **table=NULL;

    size=prime(size);

    ht=(HashTable *) malloc(sizeof(HashTable));
    ht->size=size;

    table=(Candidate **) malloc(sizeof(Candidate *)*ht->size);

    for(i=0;i<ht->size;i++)
        table[i]=NULL;

    ht->key_count=0;
    ht->table=table;

    return ht;
}

int insertHashTable(HashTable *ht,int name,Candidate *candidate) {
    Candidate *node=NULL;
    int hashkey=0;

    hashkey=name%ht->size;

    node=ht->table[hashkey];
    while(node!=NULL) {
        if(node->name==name) return(-100);
        node=node->next;
    }
    candidate->next=ht->table[hashkey];
    ht->table[hashkey]=candidate;
    ht->key_count++;

    return (0);
}
