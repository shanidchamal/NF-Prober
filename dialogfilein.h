#ifndef DIALOGFILEIN_H
#define DIALOGFILEIN_H

#include <QDialog>

namespace Ui {
class DialogFileIn;
}

class DialogFileIn : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFileIn(QWidget *parent = nullptr);
    ~DialogFileIn();

private:
    Ui::DialogFileIn *ui;
};

#endif // DIALOGFILEIN_H
