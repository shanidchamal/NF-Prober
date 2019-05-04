#include "data2int.h"
#include <stdio.h>
#include <QDebug>

#define MAX 500

static int get_dict_key(int index, char* str);
static void delete_dict();

data2int::data2int()
{

}

typedef struct vertex {
    char ch;
    int key;
    struct vertex *next;
    struct vertex *child;
} vertex;

static int *nextval;
static vertex *tries;
static int noofattr = 0;

void read_data(FILE *file, int **tables, int noof_rows, int noof_attr) {
    char line[MAX],*token;
    int i,j;

    //init dictionary
    nextval=(int*) malloc(noof_attr*sizeof(int));
    tries= (vertex*) malloc(noof_attr*sizeof(vertex));
    for(j=0;j<noof_attr;j++) {
        nextval[j]=1;
        tries[j].ch='\0';
        tries[j].key=0;
        tries[j].next=NULL;
        tries[j].child=NULL;
    }

    //double checking enough tuples are present
    for(i=0;i<noof_rows;i++) {
        qDebug() << "i:" << i;
        if(fgets(line,MAX,file)==NULL) {
            qDebug() << "not enough tuples!";
            exit(1);
        }
    token=strtok(line,",");

    //checking enough attributes are present on each line
    qDebug() << "attr_count:" << noof_attr;
    for(j=0;j<noof_attr;j++) {
        qDebug() << "j:" << j;
        if(token==NULL) {
            qDebug() << "Not enough attributes on line" << i+1;
            exit(1);
        }
    tables[j][i]=get_dict_key(j,token);
    token=strtok(NULL,",");
    }
    }
    delete_dict();
}

static int get_dict_key(int j,char* str) {
    vertex *parent, *curr;
    parent=&tries[j];
    while(*str) {
        curr=parent->child;
        while(curr!=NULL && curr->ch != *str)
            curr=curr->next;
        if(curr==NULL)
            break;
        parent=curr;
        ++str;
    }
    while(*str) {
        curr=(vertex*) malloc(sizeof(vertex));
        curr->ch=*str;
        curr->key=0;
        curr->next=parent->child;
        curr->child=NULL;
        parent->child=curr;
        parent=curr;
        ++str;
    }
    if(parent->key==0) {
        parent->key=nextval[j]++;
    }
    return parent->key;
}

static void delete_trie(vertex *parent) {
    if(parent!=NULL) {
        delete_trie(parent->child);
        delete_trie(parent->next);
        free(parent);
    }
}

static void delete_dict() {
    int j;
    for(j=0;j<noofattr;j++)
        delete_trie(tries[j].child);
    free(tries);
    free(nextval);
}

void print_table(int **tables, int noofrows, int noofattrs) {
    int i,j;
    for(i=0;i<noofattrs;i++) {
        for(j=0;j<noofrows;j++) {
            printf("%d\t",tables[i][j]);
        }
        printf("\n");
    }
}
