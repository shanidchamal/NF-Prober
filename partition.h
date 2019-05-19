#ifndef PARTITION_H
#define PARTITION_H

typedef struct Partition {
    int set_count;
    int element_count;
    int *elements;
}Partition;

Partition *getNewPartition();
void destroyPartition(Partition *par);
void printPartition(Partition *par);

#define endmarker (1 << 31)

#endif // PARTITION_H
