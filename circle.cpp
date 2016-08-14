#include "circle.h"
#include "ui_circle.h"

Circle::Circle(QWidget *parent, MainWindow* w) :
    QDialog(parent), w(w),
    ui(new Ui::Circle)
{
    ui->setupUi(this);

    ui->textEdit->setText(w->Radius);
    ui->textEdit_2->setText(QString::number(w->width,10));
    ui->textEdit_3->setText(QString::number(w->height,10));
}

Circle::~Circle()
{
    delete ui;
}

void Circle::on_buttonBox_accepted()
{
    w->Radius = ui->textEdit->toPlainText();
    w->seedx = ui->textEdit_2->toPlainText();
    w->seedy = ui->textEdit_3->toPlainText();

    //ui->textEdit->setText("t1");

    int r = w->Radius.toInt();
    int x = w->seedx.toInt();
    int y = w->seedy.toInt();
    int k[3][3];

    k[0][0] = 1;
    k[0][1] = 1;
    k[0][2] = 1;
    k[1][0] = 1;
    k[1][1] = 1;
    k[1][2] = 1;
    k[2][0] = 1;
    k[2][1] = 1;
    k[2][2] = 1;

    QImage tempImage1;
    QImage tempImage2=*(w->imageObject);
    //QImage proImage;

    switch (w->processing) {
    case 1:
        for(int i=0; i<r; i++)
        {
            tempImage1 = tempImage2;
            d->dilate(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        }
        break;
    case 2:
        for(int i=0; i<r; i++)
        {
            tempImage1 = tempImage2;
            d->erosion(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        }
        break;
    case 3:
        for(int i=0; i<r; i++)
        {
            tempImage1 = tempImage2;
            d->erosion(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
            //tempImage1 = *(w->newImage);
        }
        for(int i=0; i<r; i++)
        {
            tempImage1 = tempImage2;
            d->dilate(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
        }
        break;
    case 4:
        for(int i=0; i<r; i++)
        {
            for(int i=0; i<r; i++)
            {
                tempImage1 = tempImage2;
                d->dilate(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
                //tempImage1 = *(w->newImage);
            }
            for(int i=0; i<r; i++)
            {
                tempImage1 = tempImage2;
                d->erosion(&tempImage1, &tempImage2, k, w->width, w->height, w->depth);
            }
        }
        break;
    case 5:
        g->dilate(w->imageObject, &tempImage2, r, w->width, w->height, w->depth);
        break;
    case 6:
        g->erose(w->imageObject, &tempImage2, r, w->width, w->height, w->depth);
    case 7:
        g->erose(w->imageObject, &tempImage2, r, w->width, w->height, w->depth);
        tempImage1=tempImage2;
        g->dilate(&tempImage1, &tempImage2, r, w->width, w->height, w->depth);
        break;
    case 8:
        g->dilate(w->imageObject, &tempImage2, r, w->width, w->height, w->depth);
        tempImage1=tempImage2;
        g->erose(&tempImage1, &tempImage2, r, w->width, w->height, w->depth);
        break;
    case 9:
        d->cond_dilate(w->imageObject, &tempImage2, x, y, w->depth);
        break;
    case 10:
        g->erose(w->imageObject, &tempImage2, r, w->width, w->height, w->depth);
        tempImage1=tempImage2;
        g->dilate(&tempImage1, &tempImage2, r, w->width, w->height, w->depth);
        w->processing=11;
        //proImage=tempImage2;
        //new Circle(this, this);
        show();
        break;
    case 11:
        tempImage1=w->proImage;
        //tempImage1=*w->imageObject;
        //tempImage2=tempImage1;
        //g->dilate(&tempImage1, &tempImage2, r, w->width, w->height, w->depth);
        g->OBR(w->imageObject, &tempImage1, &tempImage2, r, w->width, w->height, w->depth);
        break;
    case 12:
        g->dilate(w->imageObject, &tempImage2, r, w->width, w->height, w->depth);
        tempImage1=tempImage2;
        g->erose(&tempImage1, &tempImage2, r, w->width, w->height, w->depth);
        w->processing=11;
        show();
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

}
