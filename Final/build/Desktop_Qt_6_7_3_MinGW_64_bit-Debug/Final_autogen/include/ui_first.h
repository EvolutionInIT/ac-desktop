/********************************************************************************
** Form generated from reading UI file 'first.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRST_H
#define UI_FIRST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_First
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *First)
    {
        if (First->objectName().isEmpty())
            First->setObjectName("First");
        First->resize(640, 480);
        pushButton = new QPushButton(First);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(230, 320, 131, 51));
        pushButton_2 = new QPushButton(First);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(230, 380, 131, 51));
        lineEdit = new QLineEdit(First);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 270, 311, 31));
        lineEdit_2 = new QLineEdit(First);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(140, 210, 311, 31));
        label = new QLabel(First);
        label->setObjectName("label");
        label->setGeometry(QRect(160, 165, 261, 21));
        label_2 = new QLabel(First);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 190, 49, 16));
        label_3 = new QLabel(First);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(140, 250, 49, 16));

        retranslateUi(First);

        QMetaObject::connectSlotsByName(First);
    } // setupUi

    void retranslateUi(QWidget *First)
    {
        First->setWindowTitle(QCoreApplication::translate("First", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("First", "sign in", nullptr));
        pushButton_2->setText(QCoreApplication::translate("First", "registration", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("First", "email", nullptr));
        label_3->setText(QCoreApplication::translate("First", "password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class First: public Ui_First {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRST_H
