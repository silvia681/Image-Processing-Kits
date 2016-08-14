#ifndef CIRCLE_H
#define CIRCLE_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindow;
class Grayscale;

namespace Ui {
class Circle;
}

class Circle : public QDialog
{
    Q_OBJECT

public:
    explicit Circle(QWidget *parent = 0, MainWindow* w = 0);
    ~Circle();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Circle *ui;
    MainWindow *w;

    Dilation *d;
    Grayscale *g;
};

#endif // CIRCLE_H
