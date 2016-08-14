#ifndef XYGRAYSCALE
#define XYGRAYSCALE

#include "mainwindow.h"

class Grayscale
{
public:
    void dilate(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth);
    void dilate(QImage *image, QImage *newimage, int radius, int width, int height, int depth);
    void erose(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth);
    void erose(QImage *image, QImage *newimage, int radius, int width, int height, int depth);
    void OBR(QImage *mask, QImage *marker, QImage *dimage, int radius, int width, int height, int depth);
    void CBR(QImage *mask, QImage *marker, QImage *dimage, int radius, int width, int height, int depth);
};

#endif // XYGRAYSCALE

