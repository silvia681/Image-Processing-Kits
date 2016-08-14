#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QImage>
#include <QIconEngine>
#include <QImageReader>
#include <QLineF>
#include <QGraphicsLineItem>
#include <QSlider>
#include "xyotsumethod.h"
#include "xyhistogram.h"
#include "xyentropy.h"
#include "xydilation.h"
#include "dialog.h"
#include "circle.h"
#include "xygrayscale.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class Dialog;
    friend class Circle;

 //   static int windowID;
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();


private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_slider_sliderMoved(int position);

    void on_slider_sliderReleased();

    void on_actionManual_triggered();

    void on_actionOtsu_triggered();

    void on_actionOtsu_toggled(bool arg1);

    void on_actionEntropy_triggered();

    void on_actionGx_3_triggered();

    void on_actionGx_triggered();

    void on_actionGy_triggered();

    void on_actionGx_2_triggered();

    void on_actionGy_2_triggered();

    void on_actionGy_3_triggered();

    void on_action3x3_triggered();

    void on_action5x5_triggered();

    void on_actionMedian_triggered();

    void on_action3x3_input_triggered();

    void on_actionCircle_triggered();

    void on_action3x3_input_2_triggered();

    void on_action3x3_input_3_triggered();

    void on_action3x3_input_4_triggered();

    void on_actionCircle_input_triggered();

    void on_actionCircle_2_triggered();

    void on_actionCircle_input_2_triggered();

    void on_actionChessboard_triggered();

    void on_actionCity_block_triggered();

    void on_actionChessboard_2_triggered();

    void on_actionCity_block_2_triggered();

    void on_pushButton_clicked();

    void on_actionRestoration_triggered();

    void on_action3x3_2_triggered();

    void on_actionSquare_triggered();

    void on_action3x3_3_triggered();

    void on_actionSquare_2_triggered();

    void on_action3x3_4_triggered();

    void on_actionSquare_3_triggered();

    void on_action3x3_5_triggered();

    void on_actionSquare_4_triggered();

    void on_actionStandard_triggered();

    void on_actionExternal_triggered();

    void on_actionInternal_triggered();

    void on_actionStandard_2_triggered();

    void on_actionExternal_2_triggered();

    void on_actionInternal_2_triggered();

    void on_actionConditional_dilation_triggered();

    void on_actionOBR_triggered();

    void on_actionCBR_triggered();

    void refreshview(QImage image);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene, *histscene;
    QGraphicsScene *scene1, *histscene1;

    QImage *imageObject;
    QPixmap image;
//    QImageReader readimage;

    QImage *newImage;
    QPixmap newPixmap;

    QGraphicsLineItem *histLine, *threshLine;
    QGraphicsLineItem *histLine1;

    Histogram histogram1, histogram2;

    Otsu otsu;

    Entropy entropy;

    QPen bluePen;
    QPen redPen;

    Dialog *dilation1;
    Circle *dilation2;

    QString t1, t2, t3, t4, t5, t6, t7, t8, t9;
    QString Radius,seedx,seedy;

    Dilation *d;
    Grayscale *g;

    QImage subset, proImage;
    QImage tempimage[1000];

//    QSlider *slider;

    int sliderPos;
    int width, height;
    int histwidth, histheight;
    int depth;
    bool lineExist, mannual, isOtsu, isEntropy;
    bool grayimage;
    int processing;
    int max;
    int index,maxindex;

};

#endif // MAINWINDOW_H
