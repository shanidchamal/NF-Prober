#include "dependencies.h"
#include "ui_dependencies.h"
#include "dialogfileconfirm.h"
#include "data2int.h"
#include "candidate.h"
#include "hashtable.h"
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

    for(i=0;i<row_count;i++)
        tables[i]=(int *)malloc(row_count*sizeof(int)+1);

    //generate sequence of data occurances
    read_data(fp,tables,row_count,attr_count);
    print_table(tables,row_count,attr_count);

    //Candidate info variables and memory allocation
    C=(Candidate **) malloc(sizeof(Candidate *)*(attr_count+1));
    C_sub=(HashTable **) malloc(sizeof(HashTable *)*(attr_count+1));

    C[0]=(Candidate *) malloc(sizeof(Candidate));
    C[1]=(Candidate *) malloc(sizeof(Candidate));

    C_sub[0]=(HashTable *) malloc(sizeof(HashTable));
    C_sub[1]=(HashTable *) malloc(sizeof(HashTable));

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


}

Dependencies::~Dependencies()
{
    delete ui;
}
