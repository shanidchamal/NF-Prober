#ifndef DIALOGFILECONFIRM_H
#define DIALOGFILECONFIRM_H

#include <QDialog>
#include <dependencies.h>

extern int row_count,attr_count;
extern QString f_name;

namespace Ui {
class DialogFileConfirm;
}

class DialogFileConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFileConfirm(QWidget *parent = nullptr);
    ~DialogFileConfirm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogFileConfirm *ui;
    Dependencies *dependencies;
};

#endif // DIALOGFILECONFIRM_H
