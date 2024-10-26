#ifndef REG_H
#define REG_H

#include "functions.h"
#include <QWidget>
#include "mainwindow.h"
#include "functions.h"


namespace Ui {
class Reg;
}

class Reg : public QWidget
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = nullptr);
    ~Reg();
    MainWindow *Mainw;
    Functions *func;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Reg *ui;
};

#endif // REG_H
