#include "dialogfileview.h"
#include "ui_dialogfileview.h"

DialogFileView::DialogFileView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFileView)
{
    ui->setupUi(this);
}

DialogFileView::~DialogFileView()
{
    delete ui;
}
