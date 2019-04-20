#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "partition.h"

typedef struct Candidate {
    unsigned int name;
    unsigned int rhs;
    Partition *partition;
    struct Candidate *next;
    int identity;
}Candidate;


#endif // CANDIDATE_H
