#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <algorithm>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mannual = false;
    isEntropy = false;
    isOtsu = false;

    processing = 0;

/*
    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(0.05);

    histLine1 = histscene1->addLine(0, 490, 0, 400.5 , bluePen);

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);//top left corner
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    //ui->slider->setTracking(false);
    //----------------load image from file----------------------------
    QString imagePath = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    imageObject = new QImage();
    imageObject->load(imagePath);

    newImage = new QImage();
    newImage->load(imagePath);

    int gray;

    QSize sizeImage = imageObject->size();
    width = sizeImage.width(), height = sizeImage.height();
    histwidth = 297;
    histheight = 150;
//    int x = ui->Hist->x();
//    int y = ui->Hist->y();

 //   QByteArray Format = readimage.imageFormat(imagePath);
 //   qDebug(Format);

    //-------------------read image pixel values and convert to grayscale image----------------

    grayimage = imageObject->isGrayscale();
    depth = imageObject->depth();

    if (!grayimage)
    {
        QRgb color;
        for (int i=0; i<256; i++)
        {
            histogram1.setHistvalue(i,0);
        }

        for (int ii=0; ii<width; ii++)
        {
            for (int jj=0; jj<height; jj++)
            {
                color = imageObject->pixel(ii, jj);
                gray = (qRed(color) + qGreen(color) + qBlue(color))/3;
                //Histogram1.histvalue++;
 //               histogram1.histvalue[gray] ++;
                histogram1.setHistvalue(gray, histogram1.getHistvalue(gray) + 1);
                imageObject->setPixel(ii, jj, qRgb(gray, gray, gray));
            }
        }
    }
    else
    {
     QRgb color;
     for (int i=0; i<256; i++)
     {
         histogram1.setHistvalue(i,0);
     }

     for (int ii=0; ii<width; ii++)
     {
         for (int jj=0; jj<height; jj++)
         {
             color = imageObject->pixel(ii, jj);
             gray = qRed(color);
             histogram1.setHistvalue(gray, histogram1.getHistvalue(gray) + 1);
         }
     }

    }


    //-------------------calculate and show image & histogram----------------------

    histogram1.setBarsize(histwidth, histheight);

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
//    scene->setSceneRect(image.rect());

//    ui->graphicsView->setTransformationAnchor(QGraphicsView::ViewportAnchor::NoAnchor);
//    ui->graphicsView->centerOn(50,50);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    ui->graphicsView2->setScene(scene);
    ui->graphicsView2->fitInView(scene->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histscene = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram1.getBin());

    for (int i=0; i<256; i++)
    {
        histLine = histscene->addLine(histogram1.getBin()*i, 490,
                                      histogram1.getBin()*i,
                                      490 - histogram1.getUnitHeight()*histogram1.getHistvalue(i) ,
                                      bluePen);
    }

//    histLine = histscene->addLine(0, 490, 0, 400.5 , bluePen);
//    histLine = histscene->addLine(297, 340, 297, 340 + 150 , bluePen);
//    qDebug()<<histogram1.getUnitHeight();

    ui->Hist->setScene(histscene);

    ui->Hist->setSceneRect(24,340,250,100);//top left corner

    lineExist = false;
//    mannual = false;
    //------------------otsu's method----------------
    if(isOtsu)
    {
        int T;
        T = otsu.findThreshold(histogram1, width, height);

        qDebug()<<T;

        int gray = T;

        QRgb color;

        for (int i=0; i<256; i++)
        {
            histogram2.setHistvalue(i,0);
        }

        for (int ii=0; ii<width; ii++)
        {
            for (int jj=0; jj<height; jj++)
            {
                color = imageObject->pixel(ii, jj);
                if (qRed(color) < gray)
                {
                    if (depth==32)
                    {
                        newImage->setPixel(ii, jj, qRgb(0, 0, 0));
                    }
                    else
                    {
                        newImage->setPixel(ii, jj, 0);
                    }
                    histogram2.setHistvalue(0, histogram2.getHistvalue(0) + 1);
                }
                else
                {
                    if (depth==32)
                    {
                        newImage->setPixel(ii, jj, qRgb(255, 255, 255));
                    }
                    else
                    {
                        newImage->setPixel(ii, jj, 255);
                    }
                    histogram2.setHistvalue(255, histogram2.getHistvalue(255) + 1);
                }
            }
        }

        newPixmap = QPixmap::fromImage(*newImage);

        proImage = *newImage;

        scene1 = new QGraphicsScene(this);
        scene1->addPixmap(newPixmap);

        ui->graphicsView2->setScene(scene1);
        ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

        histwidth = 297;
        histheight = 150;
        histogram2.setBarsize(histwidth, histheight);

        histscene1 = new QGraphicsScene(this);

        QPen bluePen(Qt::blue);
        bluePen.setWidth(histogram2.getBin());

        for (int i=0; i<256; i++)
        {
            histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                          histogram2.getBin()*i,
                                          490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                          bluePen);
        }

        ui->Hist1->setScene(histscene1);
        ui->Hist1->setSceneRect(24,340,250,100);
    }

    //----------------maximal entropy's method-----------------------
    if(isEntropy)
    {
        int T;
        T = entropy.findThreshold(histogram1, width, height);

        qDebug()<<T;

        int gray = T;

        QRgb color;

        for (int i=0; i<256; i++)
        {
            histogram2.setHistvalue(i,0);
        }

        for (int ii=0; ii<width; ii++)
        {
            for (int jj=0; jj<height; jj++)
            {
                color = imageObject->pixel(ii, jj);
                if (qRed(color) < gray)
                {
                    if (depth==32)
                    {
                        newImage->setPixel(ii, jj, qRgb(0, 0, 0));
                    }
                    else
                    {
                        newImage->setPixel(ii, jj, 0);
                    }
                    histogram2.setHistvalue(0, histogram2.getHistvalue(0) + 1);
                }
                else
                {
                    if (depth==32)
                    {
                        newImage->setPixel(ii, jj, qRgb(255, 255, 255));
                    }
                    else
                    {
                        newImage->setPixel(ii, jj, 255);
                    }
                    histogram2.setHistvalue(255, histogram2.getHistvalue(255) + 1);
                }
            }
        }

        newPixmap = QPixmap::fromImage(*newImage);
        proImage = *newImage;

        scene1 = new QGraphicsScene(this);
        scene1->addPixmap(newPixmap);

        ui->graphicsView2->setScene(scene1);
        ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

        histwidth = 297;
        histheight = 150;
        histogram2.setBarsize(histwidth, histheight);

        histscene1 = new QGraphicsScene(this);

        QPen bluePen(Qt::blue);
        bluePen.setWidth(histogram2.getBin());

        for (int i=0; i<256; i++)
        {
            histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                          histogram2.getBin()*i,
                                          490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                          bluePen);
        }

        ui->Hist1->setScene(histscene1);
        ui->Hist1->setSceneRect(24,340,250,100);
        ui->actionManual->setChecked(false);
        ui->actionOtsu->setChecked(false);
    }

}

void MainWindow::on_actionSave_triggered()
{
    QString imagePath = QFileDialog::getSaveFileName(this,
        tr("Save Image"), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));

    proImage = image.toImage();
    proImage.save(imagePath);
}

void MainWindow::on_slider_sliderMoved(int position)
{
    sliderPos = position;

    if (lineExist)
    {
       histscene->removeItem(threshLine);
    }


    QPen redPen(Qt::red);
    redPen.setWidth(0.01);

    threshLine = histscene->addLine(position, 490, position, 310 , redPen);

    ui->Hist->setScene(histscene);


    lineExist = true;


    //ui->Hist->setSceneRect(24,340,250,100);//top left corner
}

void MainWindow::on_slider_sliderReleased()
{
    if (mannual)
    {
        int gray = int(double(sliderPos) / 299.0 * 255.0);

        QRgb color;

        for (int i=0; i<256; i++)
        {
            histogram2.setHistvalue(i,0);
        }

        for (int ii=0; ii<width; ii++)
        {
            for (int jj=0; jj<height; jj++)
            {
                color = imageObject->pixel(ii, jj);
                if (qRed(color) < gray)
                {
                    if (depth==32)
                    {
                        newImage->setPixel(ii, jj, qRgb(0, 0, 0));
                    }
                    else
                    {
                        newImage->setPixel(ii, jj, 0);
                    }
                    histogram2.setHistvalue(0, histogram2.getHistvalue(0) + 1);
                }
                else
                {
                    if (depth==32)
                    {
                        newImage->setPixel(ii, jj, qRgb(255, 255, 255));
                    }
                    else
                    {
                        newImage->setPixel(ii, jj, 255);
                    }
                    histogram2.setHistvalue(255, histogram2.getHistvalue(255) + 1);
                }
            }
        }

        newPixmap = QPixmap::fromImage(*newImage);
        proImage = *newImage;

        scene1 = new QGraphicsScene(this);
        scene1->addPixmap(newPixmap);

        ui->graphicsView2->setScene(scene1);
        ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

        histwidth = 297;
        histheight = 150;
        histogram2.setBarsize(histwidth, histheight);

        histscene1 = new QGraphicsScene(this);

        QPen bluePen(Qt::blue);
        bluePen.setWidth(histogram2.getBin());

        for (int i=0; i<256; i++)
        {
            histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                          histogram2.getBin()*i,
                                          490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                          bluePen);
        }

        ui->Hist1->setScene(histscene1);
        ui->Hist1->setSceneRect(24,340,250,100);//top left corner
//        qDebug()<<histogram2.getBin()<<" "<<histogram2.getUnitHeight()<<" "<<histogram2.getHistvalue(0);
    }
}

void MainWindow::on_actionManual_triggered()
{
    mannual = true;
    isOtsu = false;
    isEntropy = false;
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);
}

void MainWindow::on_actionOtsu_triggered()
{
    mannual = false;
    isOtsu = true;
    isEntropy = false;
    int T;
    T = otsu.findThreshold(histogram1, width, height);

    qDebug()<<depth;

    int gray = T;

    QRgb color;

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    for (int ii=0; ii<width; ii++)
    {
        for (int jj=0; jj<height; jj++)
        {
            color = imageObject->pixel(ii, jj);
            if (qRed(color) < gray)
            {
                //newImage->setPixel(ii, jj, 255);
                if (depth==32)
                {
                    newImage->setPixel(ii, jj, qRgb(0, 0, 0));
                }
                else
                {
                    newImage->setPixel(ii, jj, 0);
                }
                histogram2.setHistvalue(0, histogram2.getHistvalue(0) + 1);
            }
            else
            {
                if (depth==32)
                {
                    newImage->setPixel(ii, jj, qRgb(255, 255, 255));
                }
                else
                {
                    newImage->setPixel(ii, jj, 255);
                }
                histogram2.setHistvalue(255, histogram2.getHistvalue(255) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
    ui->actionManual->setChecked(false);
    ui->actionEntropy->setChecked(false);

}

void MainWindow::on_actionOtsu_toggled(bool arg1)
{
    ;
}

void MainWindow::on_actionEntropy_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = true;

    int T;
    T = entropy.findThreshold(histogram1, width, height);

    qDebug()<<T;

    int gray = T;

    QRgb color;

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    for (int ii=0; ii<width; ii++)
    {
        for (int jj=0; jj<height; jj++)
        {
            color = imageObject->pixel(ii, jj);
            if (qRed(color) < gray)
            {
                if (depth==32)
                {
                    newImage->setPixel(ii, jj, qRgb(0, 0, 0));
                }
                else
                {
                    newImage->setPixel(ii, jj, 0);
                }
                histogram2.setHistvalue(0, histogram2.getHistvalue(0) + 1);
            }
            else
            {
                if (depth==32)
                {
                    newImage->setPixel(ii, jj, qRgb(255, 255, 255));
                }
                else
                {
                    newImage->setPixel(ii, jj, 255);
                }
                histogram2.setHistvalue(255, histogram2.getHistvalue(255) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);


}

void MainWindow::on_actionGx_3_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

//    qDebug()<<qRed(imageObject->pixel(2, 2) - imageObject->pixel(1, 1));

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii-1, jj+1));
                color2 = qRed(imageObject->pixel(ii, jj+1));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii, jj-1));
                color6 = qRed(imageObject->pixel(ii+1, jj-1));

                int value = color1 + 2*color2 + color3 - color4 - 2*color5 - color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }
    }
    else
    {
//        qDebug()<<imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii-1, jj+1));
                color2 = qRed(imageObject->pixel(ii, jj+1));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii, jj-1));
                color6 = qRed(imageObject->pixel(ii+1, jj-1));

                int value = color1 + 2*color2 + color3 - color4 - 2*color5 - color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_actionGx_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

//    qDebug()<<qRed(imageObject->pixel(2, 2) - imageObject->pixel(1, 1));

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    if(depth==32)
    {
        for (int ii=0; ii<width-1; ii++)
        {
            for (int jj=0; jj<height-1; jj++)
            {
                int color1, color2;

                color1 = qRed(imageObject->pixel(ii+1, jj+1));
                color2 = qRed(imageObject->pixel(ii, jj));

                int value = color1 - color2;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }
    }
    else
    {
//        qDebug()<<imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
        for (int ii=0; ii<width-1; ii++)
        {
            for (int jj=0; jj<height-1; jj++)
            {
                int color1, color2;

                color1 = qRed(imageObject->pixel(ii+1, jj+1));
                color2 = qRed(imageObject->pixel(ii, jj));

                int value = color1 - color2;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_actionGy_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

//    qDebug()<<qRed(imageObject->pixel(2, 2) - imageObject->pixel(1, 1));

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    if(depth==32)
    {
        for (int ii=0; ii<width-1; ii++)
        {
            for (int jj=0; jj<height-1; jj++)
            {
                int color1, color2;
                color1 = qRed(imageObject->pixel(ii, jj+1));
                color2 = qRed(imageObject->pixel(ii+1, jj));

                int value = color1 - color2;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }
    }
    else
    {
//        qDebug()<<imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
        for (int ii=0; ii<width-1; ii++)
        {
            for (int jj=0; jj<height-1; jj++)
            {
                int color1, color2;
                color1 = qRed(imageObject->pixel(ii, jj+1));
                color2 = qRed(imageObject->pixel(ii+1, jj));

                int value = color1 - color2;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_actionGx_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

//    qDebug()<<qRed(imageObject->pixel(2, 2) - imageObject->pixel(1, 1));

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii-1, jj+1));
                color2 = qRed(imageObject->pixel(ii, jj+1));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii, jj-1));
                color6 = qRed(imageObject->pixel(ii+1, jj-1));

                int value = color1 + color2 + color3 - color4 -color5 -color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }
    }
    else
    {
//        qDebug()<<imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii-1, jj+1));
                color2 = qRed(imageObject->pixel(ii, jj+1));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii, jj-1));
                color6 = qRed(imageObject->pixel(ii+1, jj-1));

                int value = color1 + color2 + color3 - color4 -color5 -color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_actionGy_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

//    qDebug()<<qRed(imageObject->pixel(2, 2) - imageObject->pixel(1, 1));

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii+1, jj-1));
                color2 = qRed(imageObject->pixel(ii+1, jj));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii-1, jj));
                color6 = qRed(imageObject->pixel(ii-1, jj+1));

                int value = color1 + color2 + color3 - color4 - color5 - color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }
    }
    else
    {
//        qDebug()<<imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii+1, jj-1));
                color2 = qRed(imageObject->pixel(ii+1, jj));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii-1, jj));
                color6 = qRed(imageObject->pixel(ii-1, jj+1));

                int value = color1 + color2 + color3 - color4 - color5 - color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_actionGy_3_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

//    qDebug()<<qRed(imageObject->pixel(2, 2) - imageObject->pixel(1, 1));

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii+1, jj-1));
                color2 = qRed(imageObject->pixel(ii+1, jj));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii-1, jj));
                color6 = qRed(imageObject->pixel(ii-1, jj+1));

                int value = color1 + 2*color2 + color3 - color4 - color5*2 - color6;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }

//        qDebug()<<newImage->pixel(126,287)<<endl<<newImage->pixel(130,349)<<endl<<newImage->pixel(155,417);

    }
    else
    {
//        color = imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
//        qDebug()<<qRed(color);
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int color1, color2, color3, color4, color5, color6;

                color1 = qRed(imageObject->pixel(ii+1, jj-1));
                color2 = qRed(imageObject->pixel(ii+1, jj));
                color3 = qRed(imageObject->pixel(ii+1, jj+1));
                color4 = qRed(imageObject->pixel(ii-1, jj-1));
                color5 = qRed(imageObject->pixel(ii-1, jj));
                color6 = qRed(imageObject->pixel(ii-1, jj+1));

                int value = color1 + 2*color2 + color3 - color4 - color5*2 - color6;

                //int value = qRed(color);

                if (value>255) { value = 255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
          //qDebug()<<color1+color2+color3;
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_action3x3_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    int color1, color2, color3, color4, color5, color6, color7, color8, color9;

    int value;

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                color1 = qRed(imageObject->pixel(ii-1, jj-1));
                color2 = qRed(imageObject->pixel(ii, jj-1));
                color3 = qRed(imageObject->pixel(ii+1, jj-1));
                color4 = qRed(imageObject->pixel(ii-1, jj));
                color5 = qRed(imageObject->pixel(ii, jj));
                color6 = qRed(imageObject->pixel(ii+1, jj));
                color7 = qRed(imageObject->pixel(ii-1, jj+1));
                color8 = qRed(imageObject->pixel(ii, jj+1));
                color9 = qRed(imageObject->pixel(ii+1, jj+1));

                value = color1 + 2*color2 + color3 + 2*color4 + 4*color5 + 2*color6
                        + color7 + 2*color8 + color9;

                value = value / 16;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }

//        qDebug()<<newImage->pixel(126,287)<<endl<<newImage->pixel(130,349)<<endl<<newImage->pixel(155,417);

    }
    else
    {
//        color = imageObject->pixel(60, 60) - imageObject->pixel(0, 0);
//        qDebug()<<qRed(color);
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                color1 = qRed(imageObject->pixel(ii-1, jj-1));
                color2 = qRed(imageObject->pixel(ii, jj-1));
                color3 = qRed(imageObject->pixel(ii+1, jj-1));
                color4 = qRed(imageObject->pixel(ii-1, jj));
                color5 = qRed(imageObject->pixel(ii, jj));
                color6 = qRed(imageObject->pixel(ii+1, jj));
                color7 = qRed(imageObject->pixel(ii-1, jj+1));
                color8 = qRed(imageObject->pixel(ii, jj+1));
                color9 = qRed(imageObject->pixel(ii+1, jj+1));

                value = color1 + 2*color2 + color3 + 2*color4 + 4*color5 + 2*color6
                        + color7 + 2*color8 + color9;

                value = value / 16;

                if (value>255) { value = 255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
          //qDebug()<<color1+color2+color3;
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_action5x5_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    int color1, color2, color3, color4, color5;
    int color6, color7, color8, color9, color10;
    int color11, color12, color13, color14, color15;
    int color16, color17, color18, color19, color20;
    int color21, color22, color23, color24, color25;

    int value;

    if(depth==32)
    {
        for (int ii=2; ii<width-2; ii++)
        {
            for (int jj=2; jj<height-2; jj++)
            {
                color1 = qRed(imageObject->pixel(ii-2, jj-2));
                color2 = qRed(imageObject->pixel(ii-1, jj-2));
                color3 = qRed(imageObject->pixel(ii, jj-2));
                color4 = qRed(imageObject->pixel(ii+1, jj-2));
                color5 = qRed(imageObject->pixel(ii+2, jj-2));
                color6 = qRed(imageObject->pixel(ii-2, jj-1));
                color7 = qRed(imageObject->pixel(ii-1, jj-1));
                color8 = qRed(imageObject->pixel(ii, jj-1));
                color9 = qRed(imageObject->pixel(ii+1, jj-1));
                color10 = qRed(imageObject->pixel(ii+2, jj-1));
                color11 = qRed(imageObject->pixel(ii-2, jj));
                color12 = qRed(imageObject->pixel(ii-1, jj));
                color13 = qRed(imageObject->pixel(ii, jj));
                color14 = qRed(imageObject->pixel(ii+1, jj));
                color15 = qRed(imageObject->pixel(ii+2, jj));
                color16 = qRed(imageObject->pixel(ii-2, jj+1));
                color17 = qRed(imageObject->pixel(ii-1, jj+1));
                color18 = qRed(imageObject->pixel(ii, jj+1));
                color19 = qRed(imageObject->pixel(ii+1, jj+1));
                color20 = qRed(imageObject->pixel(ii+2, jj+1));
                color21 = qRed(imageObject->pixel(ii-2, jj+2));
                color22 = qRed(imageObject->pixel(ii-1, jj+2));
                color23 = qRed(imageObject->pixel(ii, jj+2));
                color24 = qRed(imageObject->pixel(ii+1, jj+2));
                color25 = qRed(imageObject->pixel(ii+2, jj+2));

                value = color1 + 4*color2 + 7*color3 + 4*color4 + color5
                        + 4*color6 + 16*color7 + 26*color8 + 16*color9 + 4*color10
                        + 7*color11 + 26*color12 + 41*color13 + 26*color14 + 7*color15
                        + 4*color16 + 16*color17 + 26*color18 + 16*color19 + 4*color20
                        + color21 + 4*color22 + 7*color23 + 4*color24 + color25;

                value = value / 273;

                if (value>255) { value =255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }
    }
    else
    {
        for (int ii=2; ii<width-2; ii++)
        {
            for (int jj=2; jj<height-2; jj++)
            {
                color1 = qRed(imageObject->pixel(ii-2, jj-2));
                color2 = qRed(imageObject->pixel(ii-1, jj-2));
                color3 = qRed(imageObject->pixel(ii, jj-2));
                color4 = qRed(imageObject->pixel(ii+1, jj-2));
                color5 = qRed(imageObject->pixel(ii+2, jj-2));
                color6 = qRed(imageObject->pixel(ii-2, jj-1));
                color7 = qRed(imageObject->pixel(ii-1, jj-1));
                color8 = qRed(imageObject->pixel(ii, jj-1));
                color9 = qRed(imageObject->pixel(ii+1, jj-1));
                color10 = qRed(imageObject->pixel(ii+2, jj-1));
                color11 = qRed(imageObject->pixel(ii-2, jj));
                color12 = qRed(imageObject->pixel(ii-1, jj));
                color13 = qRed(imageObject->pixel(ii, jj));
                color14 = qRed(imageObject->pixel(ii+1, jj));
                color15 = qRed(imageObject->pixel(ii+2, jj));
                color16 = qRed(imageObject->pixel(ii-2, jj+1));
                color17 = qRed(imageObject->pixel(ii-1, jj+1));
                color18 = qRed(imageObject->pixel(ii, jj+1));
                color19 = qRed(imageObject->pixel(ii+1, jj+1));
                color20 = qRed(imageObject->pixel(ii+2, jj+1));
                color21 = qRed(imageObject->pixel(ii-2, jj+2));
                color22 = qRed(imageObject->pixel(ii-1, jj+2));
                color23 = qRed(imageObject->pixel(ii, jj+2));
                color24 = qRed(imageObject->pixel(ii+1, jj+2));
                color25 = qRed(imageObject->pixel(ii+2, jj+2));

                value = color1 + 4*color2 + 7*color3 + 4*color4 + color5
                        + 4*color6 + 16*color7 + 26*color8 + 16*color9 + 4*color10
                        + 7*color11 + 26*color12 + 41*color13 + 26*color14 + 7*color15
                        + 4*color16 + 16*color17 + 26*color18 + 16*color19 + 4*color20
                        + color21 + 4*color22 + 7*color23 + 4*color24 + color25;

                value = value / 273;

                if (value>255) { value = 255; }
                if (value<0) { value = 0; }

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
          //qDebug()<<color1+color2+color3;
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_actionMedian_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    for (int i=0; i<256; i++)
    {
        histogram2.setHistvalue(i,0);
    }

    int value;
    int colorArr[9];

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                colorArr[0] = qRed(imageObject->pixel(ii-1, jj-1));
                colorArr[1] = qRed(imageObject->pixel(ii, jj-1));
                colorArr[2] = qRed(imageObject->pixel(ii+1, jj-1));
                colorArr[3] = qRed(imageObject->pixel(ii-1, jj));
                colorArr[4] = qRed(imageObject->pixel(ii, jj));
                colorArr[5] = qRed(imageObject->pixel(ii+1, jj));
                colorArr[6] = qRed(imageObject->pixel(ii-1, jj+1));
                colorArr[7] = qRed(imageObject->pixel(ii, jj+1));
                colorArr[8] = qRed(imageObject->pixel(ii+1, jj+1));

                qSort(colorArr, colorArr + 9);

                value = colorArr[4];

                newImage->setPixel(ii, jj, qRgb(value, value, value));

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);


            }
        }

    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                int colorArr[9];
                colorArr[0] = qRed(imageObject->pixel(ii-1, jj-1));
                colorArr[1] = qRed(imageObject->pixel(ii, jj-1));
                colorArr[2] = qRed(imageObject->pixel(ii+1, jj-1));
                colorArr[3] = qRed(imageObject->pixel(ii-1, jj));
                colorArr[4] = qRed(imageObject->pixel(ii, jj));
                colorArr[5] = qRed(imageObject->pixel(ii+1, jj));
                colorArr[6] = qRed(imageObject->pixel(ii-1, jj+1));
                colorArr[7] = qRed(imageObject->pixel(ii, jj+1));
                colorArr[8] = qRed(imageObject->pixel(ii+1, jj+1));

                qSort(colorArr, colorArr + 9);

                value = colorArr[4];

                newImage->setPixel(ii, jj, value);

                histogram2.setHistvalue(value, histogram2.getHistvalue(value) + 1);
            }
        }
          //qDebug()<<color1+color2+color3;
    }

    newPixmap = QPixmap::fromImage(*newImage);
    proImage = *newImage;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    histwidth = 297;
    histheight = 150;
    histogram2.setBarsize(histwidth, histheight);

    histscene1 = new QGraphicsScene(this);

    QPen bluePen(Qt::blue);
    bluePen.setWidth(histogram2.getBin());

    for (int i=0; i<256; i++)
    {
        histLine1 = histscene1->addLine(histogram2.getBin()*i, 490,
                                      histogram2.getBin()*i,
                                      490 - histogram2.getUnitHeight()*histogram2.getHistvalue(i) ,
                                      bluePen);
    }

    ui->Hist1->setScene(histscene1);
    ui->Hist1->setSceneRect(24,340,250,100);
}

void MainWindow::on_action3x3_input_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 1;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();

   // qDebug()<<"OK";
    //Dialog dialog1;
    //dialog1.show();
}

void MainWindow::on_actionCircle_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing =1;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_action3x3_input_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 2;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_action3x3_input_3_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 3;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_action3x3_input_4_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 4;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_actionCircle_input_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 2;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_actionCircle_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 3;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_actionCircle_input_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 4;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_actionChessboard_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    int k[3][3]={{1,1,1},{1,1,1},{1,1,1}};

    QImage tempImage1=*imageObject;

    int max = d->distance(imageObject, &tempImage1, k, width, height, depth);

    for(int ii=1; ii<width-1; ii++)
    {
        for(int jj=1; jj<height-1; jj++)
        {
            int value=qRed(tempImage1.pixel(ii,jj))*255/max;
            tempImage1.setPixel(ii,jj,qRgb(value,value,value));
        }
    }

    //w->newPixmap = QPixmap::fromImage(*w->newImage);
    newPixmap = QPixmap::fromImage(tempImage1);
    proImage = tempImage1;
    //*newImage = tempImage1;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

}

void MainWindow::on_actionCity_block_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    int k[3][3]={{0,1,0},{1,1,1},{0,1,0}};

    qDebug()<<k[0][0]<<k[0][1]<<k[0][2]<<k[1][0]<<k[1][1]<<k[1][2];

    QImage tempImage1=*imageObject;

    int max = d->distance(imageObject, &tempImage1, k, width, height, depth);

    for(int ii=1; ii<width-1; ii++)
    {
        for(int jj=1; jj<height-1; jj++)
        {
            int value=qRed(tempImage1.pixel(ii,jj))*255/max;
            tempImage1.setPixel(ii,jj,qRgb(value,value,value));
        }
    }

    //w->newPixmap = QPixmap::fromImage(*w->newImage);
    newPixmap = QPixmap::fromImage(tempImage1);
    proImage = tempImage1;
    //*newImage = tempImage1;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionChessboard_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    processing = 5;

    int k[3][3]={{1,1,1},{1,1,1},{1,1,1}};

    bool mark;

    QImage tempImage1=*imageObject;

    max = d->distance(imageObject, &tempImage1, k, width, height, depth);

    QImage tempImage2=tempImage1;
    subset = tempImage1;

    if(depth=32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(tempImage1.pixel(ii,jj)))
                {
                    mark=true;
                    for (int k1=0; k1<3; k1++)
                    {
                        for (int k2=0; k2<3; k2++)
                        {
                         if(qRed(tempImage1.pixel(ii-1+k2, jj-1+k1))>qRed(tempImage1.pixel(ii,jj)))
                           {
                            mark=false;
                           }
                        }
                    }
                    if(mark)
                    {
                        tempImage2.setPixel(ii, jj, qRgb(255, 255, 255));
                        subset.setPixel(ii, jj, tempImage1.pixel(ii,jj));
                    }
                    else
                    {
                        tempImage2.setPixel(ii, jj, qRgb(0, 0, 0));
                        subset.setPixel(ii, jj, qRgb(0, 0, 0));
                    }
                }
            }
        }
    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(tempImage1.pixel(ii,jj)))
                {
                    mark=true;
                    for (int k1=0; k1<3; k1++)
                    {
                        for (int k2=0; k2<3; k2++)
                        {
                         if(qRed(tempImage1.pixel(ii-1+k2, jj-1+k1))>qRed(tempImage1.pixel(ii,jj)))
                           {
                            mark=false;
                           }
                        }
                    }
                    if(mark)
                    {
                        tempImage2.setPixel(ii, jj, 255);
                        subset.setPixel(ii, jj, qRed(tempImage1.pixel(ii,jj)));
                    }
                    else
                    {
                        tempImage2.setPixel(ii, jj, 0);
                        subset.setPixel(ii, jj, 0);
                    }
                }
            }
        }
    }

    newPixmap = QPixmap::fromImage(tempImage2);
    //newPixmap = QPixmap::fromImage(subset);
    proImage = tempImage2;
    //proImage = subset;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionCity_block_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    processing = 6;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    int k[3][3]={{0,1,0},{1,1,1},{0,1,0}};

    index=0;

    bool mark;
    //bool ttt=true;//

    QImage tempImage1=*imageObject;

    max = d->distance(imageObject, &tempImage1, k, width, height, depth);

    QImage tempImage2=tempImage1;
    subset = tempImage1;

    if(depth=32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(tempImage1.pixel(ii,jj)))
                {
                    mark=true;
                    for (int k2=1, k1=0; k1<3; k1++)
                    {
                     if(qRed(tempImage1.pixel(ii-1+k2, jj-1+k1))>qRed(tempImage1.pixel(ii,jj)))
                       {
                        mark=false;
                       }
                    }
                    for (int k1=1, k2=0; k2<3; k2++)
                    {
                     if(qRed(tempImage1.pixel(ii-1+k2, jj-1+k1))>qRed(tempImage1.pixel(ii,jj)))
                       {
                        mark=false;
                       }
                    }
                    if(mark)
                    {
                        tempImage2.setPixel(ii, jj, qRgb(255, 255, 255));
                        subset.setPixel(ii, jj, tempImage1.pixel(ii,jj));

                        //refreshview(tempImage2);
                        tempimage[index]=tempImage2;
                        index=index+1;

                      //  ttt=false;
                        //}
                    }
                    else
                    {
                        tempImage2.setPixel(ii, jj, qRgb(0, 0, 0));
                        subset.setPixel(ii, jj, qRgb(0, 0, 0));
                    }

                }
            }
        }
    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(tempImage1.pixel(ii,jj)))
                {
                    mark=true;
                    for (int k2=1, k1=0; k1<3; k1++)
                    {
                     if(qRed(tempImage1.pixel(ii-1+k2, jj-1+k1))>qRed(tempImage1.pixel(ii,jj)))
                       {
                        mark=false;
                       }
                    }
                    for (int k1=1, k2=0; k2<3; k2++)
                    {
                     if(qRed(tempImage1.pixel(ii-1+k2, jj-1+k1))>qRed(tempImage1.pixel(ii,jj)))
                       {
                        mark=false;
                       }
                    }
                    if(mark)
                    {
                        tempImage2.setPixel(ii, jj, 255);
                        subset.setPixel(ii, jj, qRed(tempImage1.pixel(ii,jj)));
                    }
                    else
                    {
                        tempImage2.setPixel(ii, jj, 0);
                        subset.setPixel(ii, jj, 0);
                    }
                }
            }
        }
    }
/*
    newPixmap = QPixmap::fromImage(tempImage2);
    proImage = tempImage2;
    //*newImage = tempImage2;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
    */
    proImage = tempImage2;
    maxindex=index-1;
    tempimage[maxindex]=tempImage2;
    index=0;
}

void MainWindow::on_pushButton_clicked()
{
    *imageObject=proImage;

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionRestoration_triggered()
{
    QImage tempImage=*imageObject;

    int k1[3][3]={{1,1,1},{1,1,1},{1,1,1}};
    int k2[3][3]={{0,1,0},{1,1,1},{0,1,0}};
    QImage *__image=&subset;
    QImage temp = subset;
    QImage __temp = subset;
    __temp.fill(qRgb(0,0,0));
    QImage *__newimage=&__temp;

    switch (processing)
    {
    case 5:
        index=0;
        ui->pushButton_2->show();
        //d->restore(&subset, &tempImage, k1, width, height, depth);
        maxindex=d->restore1(&subset, &__temp, tempimage, k1, width, height, depth);

        //QImage *newimage=image;

        //int index=0;


//        if(depth==32)
//        {
//            for(int ii=1; ii<width-1; ii++)
//            {
//                for(int jj=1; jj<height-1; jj++)
//                {
//                    if(int value=qRed(__image->pixel(ii, jj)))
//                    {
//                        //newimage->setPixel(ii, jj, qRgb(255, 255, 255));
//                        //initialize tempimage
//                        for(int tii=ii-value+2; tii<ii+value-1; tii++)
//                        {
//                            for(int tjj=jj-value+2; tjj<jj+value-1; tjj++)
//                            {
//                                temp.setPixel(tii,tjj,qRgb(0,0,0));
//                            }
//                        }

//                        int times = 0;

//                        temp.setPixel(ii, jj, qRgb(times+1, times+1, times+1));
//                        __newimage->setPixel(ii, jj, qRgb(255, 255, 255));

//                        for(int kk=0; kk<value-1; kk++)
//                        {
//                            times = times + 1;
//                            for(int kii=ii-kk; kii<=ii+kk; kii++)
//                            {
//                                for(int kjj=jj-kk; kjj<=jj+kk; kjj++)
//                                {
//                                    if(qRed(temp.pixel(kii,kjj))==times)
//                                    {
//                                        for(int k1=0; k1<3; k1++)
//                                        {
//                                            for(int k2=0; k2<3; k2++)
//                                            {
//                                                if(k[k1][k2])
//                                                {
//                                                    //qDebug()<<kii-1+k2<<" "<<kjj-1+k1<<endl;
//                                                    __newimage->setPixel(kii-1+k2, kjj-1+k1, qRgb(255, 255, 255));
//                                                    temp.setPixel(kii-1+k2, kjj-1+k1, qRgb(times+1, times+1, times+1));
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }

//                        tempimage[index]=*__newimage;
//                        index++;
//                    }
//                }
//            }
//        }
//        else
//        {
//            ;
//        }
//        maxindex=index-1;
//        index=0;
		
       // qDebug()<<maxindex;
        break;
    case 6:
        index=0;
        ui->pushButton_2->show();
        //d->restore(&subset, &tempImage, k1, width, height, depth);
        maxindex=d->restore1(&subset, &__temp, tempimage, k2, width, height, depth);
        //d->restore(&subset, &tempImage, k2, width, height, depth);
    default:
        break;
    }

//    newPixmap = QPixmap::fromImage(tempImage);
//    proImage = tempImage;
//    //*newImage = tempImage2;

//    scene1 = new QGraphicsScene(this);
//    scene1->addPixmap(newPixmap);

//    //w->ui->graphicsView2->close();
//    ui->graphicsView2->setScene(scene1);
//    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_action3x3_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 5;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_actionSquare_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 5;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_action3x3_3_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 6;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_actionSquare_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 6;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_action3x3_4_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 7;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_actionSquare_3_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 7;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_action3x3_5_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 8;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation1 = new Dialog(this, this);
    dilation1->show();
}

void MainWindow::on_actionSquare_4_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 8;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_actionStandard_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    QImage temp1=*imageObject;
    QImage temp2=temp1;
    QImage temp3=temp2;

    g->dilate(imageObject, &temp1, 1, width, height, depth);
    g->erose(imageObject, &temp2, 1, width, height, depth);

    int value=0;

    if(depth==32)
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=temp1.pixel(ii,jj)==temp2.pixel(ii,jj)?0:255;
                temp3.setPixel(ii,jj,qRgb(value,value,value));
            }
        }
    }
    else
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=temp1.pixel(ii,jj)==temp2.pixel(ii,jj)?0:255;
                temp3.setPixel(ii,jj,value);
            }
        }
    }

    newPixmap = QPixmap::fromImage(temp3);
    proImage = temp3;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionExternal_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    QImage temp1=*imageObject;
    QImage temp2=temp1;
    QImage temp3=temp1;

    g->dilate(imageObject, &temp1, 1, width, height, depth);

    int value=0;

    if(depth==32)
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=temp1.pixel(ii,jj)==temp2.pixel(ii,jj)?0:255;
                temp3.setPixel(ii,jj,qRgb(value,value,value));
            }
        }
    }
    else
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=temp1.pixel(ii,jj)==temp2.pixel(ii,jj)?0:255;
                temp3.setPixel(ii,jj,value);
            }
        }
    }

    newPixmap = QPixmap::fromImage(temp3);
    proImage = temp3;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionInternal_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    QImage temp1=*imageObject;
    QImage temp2=temp1;
    QImage temp3=temp1;

    g->erose(imageObject, &temp1, 1, width, height, depth);

    int value=0;

    if(depth==32)
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=temp1.pixel(ii,jj)==temp2.pixel(ii,jj)?0:255;
                temp3.setPixel(ii,jj,qRgb(value,value,value));
            }
        }
    }
    else
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=temp1.pixel(ii,jj)==temp2.pixel(ii,jj)?0:255;
                temp3.setPixel(ii,jj,value);
            }
        }
    }

    newPixmap = QPixmap::fromImage(temp3);
    proImage = temp3;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionStandard_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    QImage temp1=*imageObject;
    QImage temp2=temp1;
    QImage temp3=temp2;

    g->dilate(imageObject, &temp1, 1, width, height, depth);
    g->erose(imageObject, &temp2, 1, width, height, depth);

    int value=0;

    if(depth==32)
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=(qRed(temp1.pixel(ii,jj))-qRed(temp2.pixel(ii,jj)))/2;
                temp3.setPixel(ii,jj,qRgb(value,value,value));
            }
        }
    }
    else
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=(qRed(temp1.pixel(ii,jj))-qRed(temp2.pixel(ii,jj)))/2;
                temp3.setPixel(ii,jj,value);
            }
        }
    }

    newPixmap = QPixmap::fromImage(temp3);
    proImage = temp3;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionExternal_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    QImage temp1=*imageObject;
    QImage temp2=temp1;
    QImage temp3=temp1;

    g->dilate(imageObject, &temp1, 1, width, height, depth);

    int value=0;

    if(depth==32)
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=(qRed(temp1.pixel(ii,jj))-qRed(temp2.pixel(ii,jj)))/2;
                temp3.setPixel(ii,jj,qRgb(value,value,value));
            }
        }
    }
    else
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=(qRed(temp1.pixel(ii,jj))-qRed(temp2.pixel(ii,jj)))/2;
                temp3.setPixel(ii,jj,value);
            }
        }
    }

    newPixmap = QPixmap::fromImage(temp3);
    proImage = temp3;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionInternal_2_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    QImage temp1=*imageObject;
    QImage temp2=temp1;
    QImage temp3=temp1;

    g->erose(imageObject, &temp1, 1, width, height, depth);

    int value=0;

    if(depth==32)
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=(qRed(temp2.pixel(ii,jj))-qRed(temp1.pixel(ii,jj)))/2;
                temp3.setPixel(ii,jj,qRgb(value,value,value));
            }
        }
    }
    else
    {
        for(int ii=0; ii<width; ii++)
        {
            for(int jj=0; jj<height; jj++)
            {
                value=(qRed(temp1.pixel(ii,jj))-qRed(temp2.pixel(ii,jj)))/2;
                temp3.setPixel(ii,jj,value);
            }
        }
    }

    newPixmap = QPixmap::fromImage(temp3);
    proImage = temp3;

    scene1 = new QGraphicsScene(this);
    scene1->addPixmap(newPixmap);

    //w->ui->graphicsView2->close();
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
}

void MainWindow::on_actionConditional_dilation_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 9;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::on_actionOBR_triggered()
{

    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 10;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();

}

void MainWindow::on_actionCBR_triggered()
{
    mannual = false;
    isOtsu = false;
    isEntropy = false;
    processing = 12;

    ui->actionManual->setChecked(false);
    ui->actionOtsu->setChecked(false);
    ui->actionEntropy->setChecked(false);

    dilation2 = new Circle(this, this);
    dilation2->show();
}

void MainWindow::refreshview(QImage image)
{
    newPixmap = QPixmap::fromImage(image);
    //proImage = tempImage2;
    //*newImage = tempImage2;

    //if(ttt)
    //{

    scene1 = new QGraphicsScene(this);
    //scene1 = ui->graphicsView2->scene();
    //ui->graphicsView2->update;
    //MainWindow::scene1->setSceneRect(0,0,tempImage2.width(),tempImage2.height());
    /*QList<QGraphicsItem> items=scene1->items();
    for(int i=0;i<items.size();i++)
    {
        scene1->removeItem(items[i]);
        delete items[i];
    }
    */
    scene1->addPixmap(MainWindow::newPixmap);
    ui->graphicsView2->setScene(scene1);
    ui->graphicsView2->fitInView(scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);
//    QTime n=QTime::currentTime();
//    QTime now;
//    do{
//        now=QTime::currentTime();
//    }while(n.msecsTo(now)<=100);
}

void MainWindow::on_pushButton_2_clicked()
{
    //qDebug()<<index<<" "<<maxindex<<endl;
    if(index>=maxindex)
    {
        ui->pushButton_2->hide();
        refreshview(tempimage[maxindex]);
    }
    else
    {
        refreshview(tempimage[index]);
    }
    index=index+5;//speed
}
