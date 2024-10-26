#include "first.h"
#include "ui_first.h"
#include "QString"

First::First(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::First)
{
    ui->setupUi(this);
    ui->lineEdit_2->setText(QString::fromStdString(func->getValueFromJson( "email")));
    ui->lineEdit->setText(QString::fromStdString(func->getValueFromJson("password")));
}

First::~First()
{
    delete ui;
}

void First::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text() == "" or ui->lineEdit->text() == ""){
        ui->label->setText("Please fill in all fields");
        // QString email = ui->lineEdit_2->text();
        // QString password = ui->lineEdit->text();
        // func->createJsonFile("C:\\Users\\norma\\OneDrive\\Documents\\Final\\reg.json", email.toStdString(), password.toStdString(), "", "");
        // Mainw->show();
        // this->close();
    }else{
        QString email = ui->lineEdit_2->text();
        QString password = ui->lineEdit->text();
        func->insertIntoJson("email", email.toStdString());
        func->insertIntoJson("password", password.toStdString());
        Mainw = new MainWindow;
        Mainw->show();
        this->close();
    }
}


void First::on_pushButton_2_clicked()
{
    reg = new Reg;
    reg->show();
    this->close();
}

