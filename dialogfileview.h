#ifndef DIALOGFILEVIEW_H
#define DIALOGFILEVIEW_H

#include <QDialog>

namespace Ui {
class DialogFileView;
}

class DialogFileView : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFileView(QWidget *parent = nullptr);
    ~DialogFileView();

private:
    Ui::DialogFileView *ui;
};

#endif // DIALOGFILEVIEW_H
