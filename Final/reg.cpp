#include "reg.h"
#include "ui_reg.h"

Reg::Reg(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Reg)
{
    ui->setupUi(this);
}

Reg::~Reg()
{
    delete ui;
}

void Reg::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text() == "" or ui->lineEdit->text() == ""){
        ui->label->setText("Please fill in all fields");
    }else{
        QString email = ui->lineEdit_2->text();
        QString password = ui->lineEdit->text();
        func->createJsonFile(email.toStdString(), password.toStdString(), "", "");
        Mainw = new MainWindow;
        Mainw->show();
        this->close();
    }
}

