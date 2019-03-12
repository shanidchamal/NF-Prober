#include "dialogfileview.h"
#include "ui_dialogfileview.h"
#include "dialogfilein.h"
#include <QTextStream>
#include <QMessageBox>

DialogFileView::DialogFileView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFileView)
{
    ui->setupUi(this);
    QFile temp_file(file_name);
    if(!temp_file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(this,"File Open Status","File not open!!");
    }
    QTextStream in(&temp_file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
    ui->plainTextEdit->setReadOnly(true);;
    in.flush();
    temp_file.close();
}

DialogFileView::~DialogFileView()
{
    delete ui;
}

void DialogFileView::on_closeButton_clicked()
{
    this->destroy();
}
