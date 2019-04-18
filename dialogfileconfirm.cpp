#include "dialogfileconfirm.h"
#include "ui_dialogfileconfirm.h"
#include "dialogfilein.h"
#include <QDebug>
#include <QTextStream>

int row_count,attr_count;
QString f_name;

DialogFileConfirm::DialogFileConfirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFileConfirm)
{
    ui->setupUi(this);
    if(file.isOpen()) {
        f_name = file.fileName();
        int j=0;
        QString temp;
        j = f_name.lastIndexOf("/");
        qDebug() << "found / at" << j;
        ui->label_fname->setText(f_name.mid(j+1));
        ui->label_f_path->setText(f_name.mid(0,j+1));
        QTextStream in(&file);
        while(!in.atEnd()) {
            temp = in.readLine();
            row_count++;
        }
        attr_count=temp.count(",")+1;
        ui->label_f_rows->setText(QString::number(row_count));
        ui->label_f_cols->setText(QString::number(attr_count));
    }
}

DialogFileConfirm::~DialogFileConfirm()
{
    delete ui;
}

void DialogFileConfirm::on_pushButton_clicked()
{
    hide();
    dependencies=new Dependencies(this);
    dependencies->show();
}
