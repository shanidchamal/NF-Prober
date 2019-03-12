#include "dialogfilein.h"
#include "ui_dialogfilein.h"

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
