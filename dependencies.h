#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <QDialog>
#define ATTRIBUTES 32
#define FD(a,b) (a->identity == b->identity)

namespace Ui {
class Dependencies;
}

class Dependencies : public QDialog
{
    Q_OBJECT

public:
    explicit Dependencies(QWidget *parent = nullptr);
    ~Dependencies();
    void calculateFDs();
    void compute_rhscand(int);
    void generate_candidates(int);

private:
    Ui::Dependencies *ui;
};

#endif // DEPENDENCIES_H
