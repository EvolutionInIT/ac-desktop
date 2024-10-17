#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "functions.h"
#include "error.h"

#include <locale>
#include <codecvt>
#include <qcoreevent.h>
#include <thread>
#include <chrono>
#include <ctime>

#include <iostream>
#include <iomanip>
#include <sstream>


#include <QFont>
#include <thread>
#include <chrono>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    func = new Functions;
    ui->label->setStyleSheet("font-size: 43px;");
    ui->pushButton->setStyleSheet("QPushButton{font-size: 32px;font-family: Arial;color: rgb(0, 0, 0);background-color: rgb(38,56,76);}");
    ui->pushButton_2->setStyleSheet("QPushButton{font-size: 32px;font-family: Arial;color: rgb(0, 0, 0);background-color: rgb(38,56,76);}");
    ui->pushButton_5->setStyleSheet("QPushButton{font-size: 32px;font-family: Arial;color: rgb(0, 0, 0);background-color: rgb(38,56,76);}");
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_pushButton_4_clicked);
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // MainWindow::play = true;
    // ui->label->setText(QString::number(play));
    if(MainWindow::play){
        time += 1;
        ui->label->setText(QString::number(time));
    }
    MainWindow::play = true;
}


void MainWindow::on_pushButton_2_clicked()
{
    MainWindow::play = false;
}


void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::Plus()
{
    time += 1;
    ui->label->setText(QString::fromStdString(func->convertMilliseconds(time)));
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label_2->setText(QString::fromStdString(func->GetActiveWindowProcess()));
    if(MainWindow::play){
        if(time % 200000 == 0 && time !=0){
            func->captureScreenshot("C:\\Users\\norma\\OneDrive\\Documents\\Final\\");
            std::cout<<"LOL"<<std::endl;
        }
        if(time % 100 == 0 && time !=0){
            long long limit = 70;
            //func->trackMouse(time, limit);
            func->Check();
            if(func->trackKeyboard(limit) or func->trackMouse(limit)){
                error.show();
            }
        }
        time += 1;
        emit sendData(time);
        ui->label->setText(QString::fromStdString(func->convertMilliseconds(time)));
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    time =0;
    ui->label->setText(QString::fromStdString(func->convertMilliseconds(time)));
}
