#include "dialogfilein.h"
#include "ui_dialogfilein.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

QString file_name;
QFile file;

DialogFileIn::DialogFileIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFileIn)
{
    ui->setupUi(this);
}

DialogFileIn::~DialogFileIn()
{
    delete ui;
}

void DialogFileIn::on_f_selectButton_clicked()
{
    QString filter = " Text File (*.txt *.dat *.csv) ";
    file_name = QFileDialog::getOpenFileName(this,"Open FILE",QDir::homePath(),filter);
    //file_name="/home/shanid/dataset/test.dat";
    file.setFileName(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this,"File Open Status","File not open!!");
        ui->label_f_status->setText("Select a file!!");
        file.close();
    }
    else {
        ui->label_f_status->setText("File Selected :" + file_name);
    }
}
void DialogFileIn::on_f_viewButton_clicked()
{
    if(file.isOpen()) {
        dialogfileview = new DialogFileView(this);
        dialogfileview->show();
    }
    else {
        QMessageBox::information(this,"File Open Status","File not open!!");
    }
}

void DialogFileIn::on_nextButton_clicked()
{
    if(file.isOpen()) {
        dialogfileconfirm = new DialogFileConfirm(this);
        dialogfileconfirm->show();
    }
    else {
        QMessageBox::information(this,"File Open Status","File not open!!");
    }
}
