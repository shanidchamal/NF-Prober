#include "partition.h"
#include <stdio.h>
#include <malloc.h>

Partition *getNewPartition() {
    Partition *self=NULL;

    self=(Partition *) malloc(sizeof(Partition));
    self->set_count=0;
    self->element_count=0;
    self->elements=NULL;
    return self;
}

void printPartition(Partition *par) {
    int i;
    for(i=0;i<par->element_count;i++) {
        printf("%d ",par->elements[i] & ~endmarker);
        if(par->elements[i] & endmarker)
            printf("\n");
    }
}
