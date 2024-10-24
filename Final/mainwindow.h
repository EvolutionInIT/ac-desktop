#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "functions.h"
#include "error.h"

#include <iostream>
#include <iomanip>
#include <sstream>


#include <QMainWindow>
#include <QPushButton>
#include <QFont>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Error error;
    QPushButton *btn;
    bool play = false;
    long long time =0;
    QTimer *timer;
    Functions *func;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void Plus();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

signals:
    void sendData(long long Lol);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
