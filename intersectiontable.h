#ifndef INTERSECTIONTABLE_H
#define INTERSECTIONTABLE_H

#include "partition.h"

void IntersectionTblINIT(int row_count);
void IntersectionTblLOAD(Partition *partition);
void IntersectionTblUNLOAD(Partition *partition);
Partition *Intersection(Partition *partition);
Partition *generatePartition(int *table,int row_count);

#endif // INTERSECTIONTABLE_H
