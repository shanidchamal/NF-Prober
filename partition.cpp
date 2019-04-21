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
