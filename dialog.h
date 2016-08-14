#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindow;
class Dilation;
class Grayscale;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, MainWindow* w = 0);
    ~Dialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    MainWindow* w;

    Dilation* d;
    Grayscale* g;

};

#endif // DIALOG_H
