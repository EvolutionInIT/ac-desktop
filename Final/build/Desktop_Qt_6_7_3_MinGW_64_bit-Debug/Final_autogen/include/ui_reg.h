/********************************************************************************
** Form generated from reading UI file 'reg.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_H
#define UI_REG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Reg
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLabel *label_4;

    void setupUi(QWidget *Reg)
    {
        if (Reg->objectName().isEmpty())
            Reg->setObjectName("Reg");
        Reg->resize(640, 480);
        lineEdit = new QLineEdit(Reg);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(170, 250, 311, 31));
        pushButton_2 = new QPushButton(Reg);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(260, 300, 131, 51));
        label_2 = new QLabel(Reg);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(170, 170, 49, 16));
        label_3 = new QLabel(Reg);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(170, 230, 49, 16));
        lineEdit_2 = new QLineEdit(Reg);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(170, 190, 311, 31));
        label = new QLabel(Reg);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 80, 261, 21));
        lineEdit_3 = new QLineEdit(Reg);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(170, 130, 311, 31));
        label_4 = new QLabel(Reg);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(170, 110, 49, 16));

        retranslateUi(Reg);

        QMetaObject::connectSlotsByName(Reg);
    } // setupUi

    void retranslateUi(QWidget *Reg)
    {
        Reg->setWindowTitle(QCoreApplication::translate("Reg", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Reg", "registration", nullptr));
        label_2->setText(QCoreApplication::translate("Reg", "email", nullptr));
        label_3->setText(QCoreApplication::translate("Reg", "password", nullptr));
        label->setText(QString());
        lineEdit_3->setText(QString());
        label_4->setText(QCoreApplication::translate("Reg", "name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Reg: public Ui_Reg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_H
