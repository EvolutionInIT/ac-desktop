#ifndef FIRST_H
#define FIRST_H

#include <QWidget>
#include "mainwindow.h"
#include "reg.h"
#include "functions.h"
#include "iostream"


namespace Ui {
class First;
}

class First : public QWidget
{
    Q_OBJECT

public:
    explicit First(QWidget *parent = nullptr);
    ~First();
    Reg *reg;
    MainWindow *Mainw;
    Functions *func;
    bool WasIt=false;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::First *ui;
};

#endif // FIRST_H
