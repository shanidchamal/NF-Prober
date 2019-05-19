#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intersectiontable.h"

static int *tuple_tbl=NULL;
static int *newtuple_tbl=NULL;
static int *set_tbl=NULL;
static int *set_visit=NULL;
static int noof_sets=0,noof_tuples=0;

void IntersectionTblINIT(int row_count) {
    noof_tuples=row_count+1;
    noof_sets=noof_tuples;

    tuple_tbl=new int[sizeof (int *)*noof_tuples]();
    set_tbl=new int[sizeof (int)*noof_sets]();
    set_visit=new int[sizeof (int)*noof_sets]();
    newtuple_tbl=new int[sizeof (int*)*noof_tuples]();

    /*tuple_tbl=(int *) malloc(sizeof (int *)*noof_tuples);
    set_tbl=(int *) malloc(sizeof (int *)*noof_sets);
    set_visit=(int *) malloc(sizeof(int)*noof_sets);
    newtuple_tbl=(int *) malloc(sizeof (int *)*noof_tuples);

    for(i=0;i<noof_tuples;i++) {
        tuple_tbl[i]=0;
        newtuple_tbl[i]=0;
    }
    for(i=0;i<noof_sets;i++) {
        set_tbl[i]=0;
        set_visit[i]=0;
    }*/
}

Partition *generatePartition(int *table,int row_count) {
    int i,k,base_index=1,set_index=0,element=0;
    Partition *partition=getNewPartition();

    for(i=0;i<row_count;i++)
        set_tbl[i]=0;
    for(i=1;i<row_count+1;i++) {
        if(set_tbl[table[i-1]]++ == 0) //count occurances of set
            set_visit[set_index++]=table[i-1]; //stores how many sets of values are there
    }

    /*
    printf("set_visit:\n");
    for(k=0;k<set_index;k++)
        printf("[%2d] == %d\n",k,set_visit[k]);
    //printf("set_tbl[%d]:%d\n",k,set_tbl[k]);
    */

    set_tbl[0]=0;
    for(k=0;k<set_index;k++) {
        if(set_visit[k]==0) //no sets present
            continue;
        if(set_tbl[set_visit[k]]==1) { //set element count is 1
            //printf("set_tbl[set_visit[k]=1:%d\n",set_visit[k]);
            set_tbl[set_visit[k]]=0;
            set_visit[k]=0;
            continue;
        }
        base_index+=set_tbl[set_visit[k]];
        set_tbl[set_visit[k]]=base_index-set_tbl[set_visit[k]]; //stroes set starting index
    }

    /*
    printf("set_visit:\n");
    for(k=0;k<set_index;k++)
        printf("[%2d]==%d set_tbl[%d]==%d\n",k,set_visit[k],set_visit[k],set_tbl[set_visit[k]]);
    */

    for(i=1;i<row_count+1;i++) {
        //checks starting index of each set
        if(set_tbl[table[i-1]]==0) // only 1 element set whose starting index set to 0
            continue;
        element=set_tbl[table[i-1]]++; //go on generating elements for the set
        newtuple_tbl[element-1]=i;
        partition->element_count++;
    }

    /*
    printf("newtuple_tbl:\n");
    for(i=0;i<partition->element_count;i++)
        printf("[%2d]==%d\n",i,newtuple_tbl[i]);
    for(k=0;k<set_index+1;k++)
        printf("new set_tbl[%d]=%d\n",k,set_tbl[k]);
    */

    memcpy(table,newtuple_tbl,sizeof (int)*partition->element_count);

    for(k=0;k<set_index;k++) {
        if(set_visit[k]==0) //no sets present
            continue;
        table[set_tbl[set_visit[k]]-2] |= endmarker; //for marking the end of set
        partition->set_count++;

        set_tbl[set_visit[k]]=0;
    }
    partition->elements=table;
    return partition;
}

void IntersectionTblLOAD(Partition *partition) {
    int i=0, set_no=1;
    while(i<partition->element_count) {
        while(1) {
            if(partition->elements[i] & endmarker)
                break;
            tuple_tbl[(partition->elements[i++])-1]=set_no;
        }
        tuple_tbl[(partition->elements[i++] & ~endmarker)-1]=set_no;
        set_no++;
    }
    /*
    printf("tuple_tble:\n");
    for(i=0;i<partition->element_count;i++)
        printf("[%d]==%d\n",i,tuple_tbl[i]);
    */

    //printf("\nnoof_sets:%d",noof_sets);
    noof_sets=set_no-1;
    /*
    printf("\nset_no:%d",set_no);
    printf("\nnoof_sets:%d",noof_sets);
    printf("\nset_tbl[noof_sets]:%d",set_tbl[noof_sets]);
    */
    set_tbl[noof_sets+1]=1;
    //printf("\nset_tbl[noof_sets+1]:%d",set_tbl[noof_sets+1]);
}

Partition *Intersection(Partition *partition) {
    int i=0,j=0,k=0,base_index=1,set_index=0,element=0;
    Partition *par=getNewPartition();

    while(i<partition->element_count) {
        set_index=0;
        while((partition->elements[i] & endmarker) ==0) {
            if(set_tbl[tuple_tbl[partition->elements[i++]-1]]++ ==0)
                set_visit[set_index++] = tuple_tbl[partition->elements[i-1]-1];
        }
        partition->elements[i] &= ~endmarker;
        if(set_tbl[tuple_tbl[partition->elements[i++]-1]]++ ==0)
            set_visit[set_index++]=tuple_tbl[partition->elements[i-1]-1];

        set_tbl[0]=0;
        for(k=0;k<set_index;k++) {
            if(set_visit[k]==0)
                continue;
            if(set_tbl[set_visit[k]]==1) {
                set_tbl[set_visit[k]]=0;
                set_visit[k]=0;
                continue;
            }
            base_index+=set_tbl[set_visit[k]];
            set_tbl[set_visit[k]]=base_index-set_tbl[set_visit[k]];
        }

        for(;j<i;j++) {
            if(set_tbl[tuple_tbl[partition->elements[j]-1]] ==0)
                continue;
            element=set_tbl[tuple_tbl[partition->elements[j]-1]]++;
            newtuple_tbl[element-1]=partition->elements[j];
            par->element_count++;
        }
        partition->elements[i-1] |= endmarker;

        for(k=0;k<set_index;k++) {
            if(set_visit[k]==0)
                continue;
            newtuple_tbl[set_tbl[set_visit[k]]-2] |= endmarker;
            par->set_count++;
            set_tbl[set_visit[k]]=0;
        }
    }
    par->elements=(int *) malloc(sizeof (int)*par->element_count);
    memcpy(par->elements,newtuple_tbl,sizeof (int)*par->element_count);
    /*int tmp;
    tmp=par->element_count-par->set_count;
    printf("\ninside Intersection:%d\n",tmp);*/
    /*if(par->element_count) {
        //par->elements=newtuple_tbl;
        par->elements=(int *) malloc(sizeof (int)*par->element_count);
        memcpy(par->elements,newtuple_tbl,sizeof (int)*par->element_count);
    }*/

    return par;
}

void IntersectionTblUNLOAD(Partition *partition) {
    int i;
    for(i=0;i<partition->element_count;i++)
        tuple_tbl[(partition->elements[i] & ~endmarker)-1]=0;
    set_tbl[noof_sets+1]=0;
}
