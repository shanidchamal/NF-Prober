#include <stdio.h>
#include "bitset.h"

int getNext(int bitset,int position) {
    int temp=bitset >> position;
    if(temp==0)
        return (-1);
    while(1) {
        position++;
        if(temp&1)
            return position;
        temp >>= 1;
    }
}

void printBitset(int bitset) {
    int pos=0;
    pos=getNext(bitset,0);
    while(pos > -1) {
        printf("%d ",pos);
        pos=getNext(bitset,pos);
    }
}

