#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialogfilein.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_homeButton_clicked();

private:
    Ui::MainWindow *ui;
    DialogFileIn *dialogfilein;
};

#endif // MAINWINDOW_H
