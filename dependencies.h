#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <QDialog>
#define ATTRIBUTES 32

namespace Ui {
class Dependencies;
}

class Dependencies : public QDialog
{
    Q_OBJECT

public:
    explicit Dependencies(QWidget *parent = nullptr);
    ~Dependencies();

private:
    Ui::Dependencies *ui;
};

#endif // DEPENDENCIES_H
