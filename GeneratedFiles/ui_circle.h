/********************************************************************************
** Form generated from reading UI file 'circle.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCLE_H
#define UI_CIRCLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Circle
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *textEdit;
    QLabel *label;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *Circle)
    {
        if (Circle->objectName().isEmpty())
            Circle->setObjectName(QStringLiteral("Circle"));
        Circle->resize(168, 130);
        buttonBox = new QDialogButtonBox(Circle);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 90, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        textEdit = new QTextEdit(Circle);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(87, 8, 41, 31));
        label = new QLabel(Circle);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 10, 51, 20));
        label->setTextFormat(Qt::AutoText);
        textEdit_2 = new QTextEdit(Circle);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(30, 50, 41, 31));
        textEdit_3 = new QTextEdit(Circle);
        textEdit_3->setObjectName(QStringLiteral("textEdit_3"));
        textEdit_3->setGeometry(QRect(100, 50, 41, 31));
        label_2 = new QLabel(Circle);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 21, 16));
        label_3 = new QLabel(Circle);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(80, 60, 21, 16));

        retranslateUi(Circle);
        QObject::connect(buttonBox, SIGNAL(accepted()), Circle, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Circle, SLOT(reject()));

        QMetaObject::connectSlotsByName(Circle);
    } // setupUi

    void retranslateUi(QDialog *Circle)
    {
        Circle->setWindowTitle(QApplication::translate("Circle", "Dialog", 0));
        label->setText(QApplication::translate("Circle", "radius", 0));
        label_2->setText(QApplication::translate("Circle", "x", 0));
        label_3->setText(QApplication::translate("Circle", "y", 0));
    } // retranslateUi

};

namespace Ui {
    class Circle: public Ui_Circle {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCLE_H
