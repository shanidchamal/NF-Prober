#include "dependencies.h"
#include "ui_dependencies.h"
#include "dialogfileconfirm.h"
#include "data2int.h"
#include "candidate.h"
#include "hashtable.h"
#include "intersectiontable.h"
#include "bitset.h"

#include <QDebug>
#include <stdio.h>

Candidate **C=NULL;
HashTable **C_sub=NULL;
int cand_count[ATTRIBUTES]={0};

Dependencies::Dependencies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dependencies)
{
    ui->setupUi(this);

    int *tables[ATTRIBUTES],i,level;
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

    cand_count[0]=1;
    cand_count[1]=attr_count;

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

    for(level=1;attr_count+1;level++)
        calculateFDs(level);
}

Dependencies::~Dependencies()
{
    delete ui;
}

void Dependencies::calculateFDs(int level) {
    compute_rhscand(level);

    //clean prev levels
    free(C[level-1]);
    destroyHashTable(C_sub[level-1]);

    //generate_candidates(level);
}

void Dependencies::compute_rhscand(int level) {
    int i=0, element=0, element1=0;
    Candidate *X=NULL, *sub=NULL;
    int XA=0, XB=0, A=0, R=0;

    for(i=0;i<cand_count[level];i++) {
        X=&C[level][i];
        element=getNext(X->name,0); //to get actual name of x->name
        while(element>0) {
            XA=X->name;
            //remove XA, set to 0
            XA &= ~(1 << (element-1));
            if(checkHashTable(C_sub[level-1],XA,&sub))
                //find intersection
                X->rhs &= sub->rhs;
        }
        element=getNext(X->name,element);
    }

    for(i=0;i<cand_count[level];i++) {
        X=&C[level][i];
        A=X->name;
        //intersection
        A &= X->rhs;
        //get actual name of x->name
        element=getNext(A,0);
        while(element > 0) {
            XA=X->name;{
                //remove XA, set to 0
                XA &= ~(1 << (element-1));
                if(checkHashTable(C_sub[level-1],XA,&sub)) {
                    if(FD(sub,X)) {
                        R=X->name;
                        //R=R-sub_name (MINUS) // 8-8=0;
                        R &= ~sub->name;
                        printBitset(sub->name);
                        printf("-->");
                        printBitset(R);
                        printf("\n");

                        //remove XA, set to 0
                        X->rhs &= ~(1 << (element-1));

                        //R = 2^attr_count -1 (inserts all combination)
                        R=~(~0 << attr_count);

                        //R=R-X->name (MINUS)
                        R &= ~X->name;

                        //X->rhs=X->rhs-R (MINUS)
                        X->rhs &= ~R;

                        //R = 2^attr_count -1 (inserts all combination)
                        R=~(~0 << attr_count);

                        //R=R-X->name (MINUS)
                        R &= ~X->name;
                        element1=getNext(R,0);
                        while(element1 > 0) {
                            XB=X->name;
                            //insert (2^element-1)
                            XB |= ~(1 << (element1-1));
                            //remove XB, with element
                            XB &= ~(1 << (element-1));
                            if(checkHashTable(C_sub[level],XB,&sub)) {
                                //remove sub->rhs
                                sub->rhs &= ~(1 << (element-1));
                            }
                            element1=getNext(R,element1);
                        }
                    }
                }
            }
            element=getNext(A,element);
        }
    }
}

void Dependencies::generate_candidates(int level) {

}
