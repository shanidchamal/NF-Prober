#ifndef PARTITION_H
#define PARTITION_H

typedef struct Partition {
    int set_count;
    int element_count;
    unsigned int *elements;
}Partition;

Partition *getNewPartition();


#endif // PARTITION_H
