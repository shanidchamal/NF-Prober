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

int getPrefix(int a, int b) {
    int prefix=0,pos_a=0,pos_b=0;
    pos_a=getNext(a,0);
    pos_b=getNext(b,0);
    while(pos_a>0 && pos_b>0) {
        if(pos_a != pos_b)
            break;
        prefix++;
        pos_a=getNext(a,pos_a);
        pos_b=getNext(b,pos_b);
    }
    return prefix;
}

void printBitset(int bitset) {
    int pos=0;
    pos=getNext(bitset,0);
    while(pos > -1) {
        printf("%d ",pos);
        pos=getNext(bitset,pos);
    }
}

