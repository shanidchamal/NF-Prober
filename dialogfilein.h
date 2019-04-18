#ifndef DIALOGFILEIN_H
#define DIALOGFILEIN_H

#include <QDialog>
#include "dialogfileview.h"
#include "dialogfileconfirm.h"
#include <QFile>

extern QString file_name;
extern QFile file;

namespace Ui {
class DialogFileIn;
}

class DialogFileIn : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFileIn(QWidget *parent = nullptr);
    ~DialogFileIn();

private slots:
    void on_f_selectButton_clicked();

    void on_f_viewButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::DialogFileIn *ui;
    DialogFileView *dialogfileview;
    DialogFileConfirm * dialogfileconfirm;
};

#endif // DIALOGFILEIN_H
