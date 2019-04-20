#include "dependencies.h"
#include "ui_dependencies.h"
#include "dialogfileconfirm.h"
#include "data2int.h"
#include <QDebug>
#include <stdio.h>

Dependencies::Dependencies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dependencies)
{
    ui->setupUi(this);

    int *tables[ATTRIBUTES],i;
    FILE *fp = NULL;

    if((fp=fopen(f_name.toStdString().c_str(),"r"))==NULL) {
        qDebug() << "error opening file!";
    }

    for(i=0;i<row_count;i++)
        tables[i]=(int *)malloc(row_count*sizeof(int)+1);

    //generate sequence of data occurances
    read_data(fp,tables,row_count,attr_count);
    print_table(tables,row_count,attr_count);


}

Dependencies::~Dependencies()
{
    delete ui;
}
