/********************************************************************************
** Form generated from reading UI file 'error.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERROR_H
#define UI_ERROR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Error
{
public:
    QLabel *label;

    void setupUi(QWidget *Error)
    {
        if (Error->objectName().isEmpty())
            Error->setObjectName("Error");
        Error->resize(640, 480);
        label = new QLabel(Error);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 130, 471, 141));

        retranslateUi(Error);

        QMetaObject::connectSlotsByName(Error);
    } // setupUi

    void retranslateUi(QWidget *Error)
    {
        Error->setWindowTitle(QCoreApplication::translate("Error", "Form", nullptr));
        label->setText(QCoreApplication::translate("Error", "<html><head/><body><p><span style=\" font-size:36pt;\">Are you sure you're</span></p><p><span style=\" font-size:36pt;\"> busy with work?</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Error: public Ui_Error {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERROR_H
