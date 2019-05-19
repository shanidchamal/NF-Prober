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
int cand_count[ATTRIBUTES]={0},level;

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

    printf("\n----------------FDs-----------------------\n\n");

    level=1;
    while(level<(attr_count+1) && cand_count[level]>0)
        calculateFDs();
}

Dependencies::~Dependencies()
{
    delete ui;
}

void Dependencies::calculateFDs() {
    compute_rhscand(level);

    //clean prev levels
    free(C[level-1]);
    destroyHashTable(C_sub[level-1]);

    level+=1;
    generate_candidates(level);
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
            if(checkHashTable(C_sub[level-1],XA,&sub)) {
                //find intersection
                X->rhs &= sub->rhs;
            }
            element=getNext(X->name,element);
        }
    }

    for(i=0;i<cand_count[level];i++) {
        X=&C[level][i];
        A=X->name;
        //intersection
        A &= X->rhs;
        //get actual name of x->name
        element=getNext(A,0);
        while(element > 0) {
            XA=X->name;
                //remove XA, set to 0
                XA &= ~(1 << (element-1));
                if(checkHashTable(C_sub[level-1],XA,&sub)) {
                    if(FD(sub,X)) {
                        R=X->name;
                        //R=R-sub_name (MINUS)
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
                            XB |= (1 << (element1-1));
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
            element=getNext(A,element);
        }
    }
}

void Dependencies::generate_candidates(int level) {
    int i_x=0,i_y=0,prefix=0,element=0;
    int loaded=0,notfound=0,lev_size=0;
    Candidate *X=NULL,*Y=NULL,*candidate=NULL,*sub=NULL;
    int XY=0,R=0;
    
    //define level size and get hashtable and candidates
    lev_size=(cand_count[level-1]*(attr_count-(level-1)))/level;
    C[level]=(Candidate *) malloc(sizeof (Candidate)*lev_size);
    C_sub[level]=getNewHashTable(lev_size);
    
    for(i_x=0;i_x<cand_count[level-1];i_x++) {
        X=&C[level-1][i_x];
        
        //keys and full rhs pruning
        //key pruning
        if(X->identity==0) {
            //R = 2^attr_count -1 (inserts all combination)
            R = ~(~0 << attr_count);
            // R = R-X->name
            R &= ~X->name;
            //intersection
            R &= X->rhs;
            
            element=getNext(R,0);
            while(element > 0) {
                printBitset(X->name);
                printf("-> %d   (key)\n",element);
                element=getNext(R,element);
            }
            continue;
        }
        //full rhs
        if(X->rhs==0)
            continue;
        
        for(i_y=i_x+1;i_y<cand_count[level-1];i_y++) {
            Y=&C[level-1][i_y];
            prefix=getPrefix(X->name,Y->name);
            if(prefix+1 != (level-1))
                break;
            
            if(Y->identity==0 || Y->rhs ==0) {
                continue;
            }
            
            //new candidate XY
            XY=X->name | Y->name;
            notfound=0;
            element=getNext(XY,0);
            while(element > 0) {
                R=XY;
                //remove
                R &= ~(1 << (element-1));
                if(checkHashTable(C_sub[level-1],R,&sub)) {
                    if(sub->identity==0 || sub->rhs==0) {
                        notfound=1;
                        break;
                    }
                    if(sub!=X && sub!=Y)
                        if(sub->identity < Y->identity) {
                            Y=sub;
                        }
                }
                else
                    notfound=1;              
                element=getNext(XY,element);
            }
            if(notfound)
                continue;
            if(!loaded) {
                IntersectionTblLOAD(X->partition);
                loaded=1;
            }
            //generate new level candidates
            candidate=&C[level][cand_count[level]++];
            candidate->name=XY;
            candidate->partition=Intersection(Y->partition);
            //candidate->rhs = 2^attr_count -1 (inserts all combination)
            candidate->rhs=~(~0 << attr_count);
            candidate->identity=candidate->partition->element_count-candidate->partition->set_count;
            insertHashTable(C_sub[level],candidate->name,candidate);
        }
        if(loaded) {
            IntersectionTblUNLOAD(X->partition);
            loaded=0;
        }
        destroyPartition(X->partition);
        X->partition=NULL;
    }
}
