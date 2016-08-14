#ifndef XYDILATION
#define XYDILATION

#include "mainwindow.h"

class SItem{
public:
    SItem(){}
    SItem(int x, int y):x(x),y(y){}
    int x, y;
};

class Dilation
{
public:
    void dilate(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth);
    void erosion(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth);
    int distance(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth);
    void restore(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth);
    int restore1(QImage *image, QImage *newimage, QImage temp[200], int k[3][3], int width, int height, int depth);
    void cond_dilate(QImage *mask, QImage *newimage, int seedx, int seedy, int depth);
private:
	void getTemplate(QImage* image, int k[3][3], int order, int x, int y, int width, int height);
//	short **vis;
};

#endif // XYDILATION

