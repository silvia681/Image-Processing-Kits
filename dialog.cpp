#include "dialog.h"
#include "ui_dialog.h"
#include "qdebug.h"

Dialog::Dialog(QWidget *parent, MainWindow* w) :
    QDialog(parent), w(w),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //qDebug()<<MainWindow::t1.toInt();

    ui->textEdit->setText(w->t1);
    ui->textEdit_2->setText(w->t2);
    ui->textEdit_3->setText(w->t3);
    ui->textEdit_4->setText(w->t4);
    ui->textEdit_5->setText(w->t5);
    ui->textEdit_6->setText(w->t6);
    ui->textEdit_7->setText(w->t7);
    ui->textEdit_8->setText(w->t8);
    ui->textEdit_9->setText(w->t9);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{
    w->t1 = ui->textEdit->toPlainText();
    w->t2 = ui->textEdit_2->toPlainText();
    w->t3 = ui->textEdit_3->toPlainText();
    w->t4 = ui->textEdit_4->toPlainText();
    w->t5 = ui->textEdit_5->toPlainText();
    w->t6 = ui->textEdit_6->toPlainText();
    w->t7 = ui->textEdit_7->toPlainText();
    w->t8 = ui->textEdit_8->toPlainText();
    w->t9 = ui->textEdit_9->toPlainText();

    //ui->textEdit->setText("t1");

    int k[3][3];

    k[0][0] = w->t1.toInt();
    k[0][1] = w->t2.toInt();
    k[0][2] = w->t3.toInt();
    k[1][0] = w->t4.toInt();
    k[1][1] = w->t5.toInt();
    k[1][2] = w->t6.toInt();
    k[2][0] = w->t7.toInt();
    k[2][1] = w->t8.toInt();
    k[2][2] = w->t9.toInt();

    QImage tempImage1;
    QImage tempImage2=*(w->imageObject);

    switch (w->processing) {
    case 1:
        d->dilate(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 2:
        d->erosion(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 3:
        d->erosion(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        //tempImage1 = *(w->newImage);
        tempImage1 = tempImage2;
        d->dilate(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 4:
        d->dilate(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        //tempImage1 = *(w->newImage);
        tempImage1 = tempImage2;
        d->erosion(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 5:
        g->dilate(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 6:
        g->erose(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 7:
        g->erose(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        //tempImage1 = *(w->newImage);
        tempImage1 = tempImage2;
        g->dilate(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        break;
    case 8:
        g->dilate(w->imageObject, &tempImage2, k, w->width, w->height, w->depth);
        //tempImage1 = *(w->newImage);
        tempImage1 = tempImage2;
        g->erose(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        break;
    default:
        break;
    }

    //w->newPixmap = QPixmap::fromImage(*w->newImage);

    w->proImage = tempImage2;
    *(w->newImage) = tempImage2;

    w->newPixmap = QPixmap::fromImage(tempImage2);

    w->scene1 = new QGraphicsScene(this);
    w->scene1->addPixmap(w->newPixmap);

    //w->ui->graphicsView2->close();
    w->ui->graphicsView2->setScene(w->scene1);
    w->ui->graphicsView2->fitInView(w->scene1->itemsBoundingRect(),Qt::IgnoreAspectRatio);

    //qDebug()<<k[2][0]<<" "<<k[2][1]<<" "<<k[2][2];

}
