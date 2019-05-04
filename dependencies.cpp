#include "dependencies.h"
#include "ui_dependencies.h"
#include "dialogfileconfirm.h"
#include "data2int.h"
#include "candidate.h"
#include "hashtable.h"
#include "intersectiontable.h"

#include <QDebug>
#include <stdio.h>

Candidate **C=NULL;
HashTable **C_sub=NULL;

Dependencies::Dependencies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dependencies)
{
    ui->setupUi(this);

    int *tables[ATTRIBUTES],i;
    FILE *fp = NULL;
    Candidate *candidate=NULL;

    if((fp=fopen(f_name.toStdString().c_str(),"r"))==NULL) {
        qDebug() << "error opening file!";
    }

    for(i=0;i<attr_count;i++)
        tables[i]=(int *)malloc(row_count*sizeof(int)+1);

    //generate sequence of data occurances
    read_data(fp,tables,row_count,attr_count);
    print_table(tables,row_count,attr_count);

    //Candidate info variables and memory allocation
    C=(Candidate **) malloc(sizeof(Candidate *)*(attr_count+1));
    C_sub=(HashTable **) malloc(sizeof(HashTable *)*(attr_count+1));

    C[0]=(Candidate *) malloc(sizeof(Candidate));
    C[1]=(Candidate *) malloc(sizeof(Candidate)*attr_count);

    //init new hashtable
    C_sub[0]=getNewHashTable(1);
    C_sub[1]=getNewHashTable(attr_count);

    //populate candidate 0
    candidate=&C[0][0];
    candidate->name=0;
    candidate->rhs=0;
    candidate->partition=getNewPartition();
    candidate->partition->element_count=row_count;
    candidate->partition->set_count=1;
    candidate->identity=row_count-1;
    //candidate->rhs = 2^attr_count -1 (inserts all combination)
    candidate->rhs=~(~0 << attr_count);
    insertHashTable(C_sub[0],candidate->name,candidate);
    printHashTable(C_sub[0]);
    printf("\n\n");

    IntersectionTblINIT(row_count);

    //populate candidate at level 1
    for(i=1;i<attr_count+1;i++) {
        candidate=&C[1][i-1];
        candidate->partition=generatePartition(tables[i-1],row_count);
        printf("candidate->partition:\n");
        printPartition(candidate->partition);
        candidate->name=0;
        //candidate->name = 2*i
        candidate->name |= (1 << (i-1));
        printf("candidate->name:%d\n",candidate->name);
        //candidate->rhs = 2^attr_count -1 (inserts all combination)
        candidate->rhs=~(~0 << attr_count);
        printf("candidate->rhs:%d\n",candidate->rhs);
        candidate->identity=candidate->partition->element_count-candidate->partition->set_count;
        printf("candidate->identity:%d\n",candidate->identity);
        insertHashTable(C_sub[1],candidate->name,candidate);
        printHashTable(C_sub[1]);
        printf("\n\n");
    }
}

Dependencies::~Dependencies()
{
    delete ui;
}
