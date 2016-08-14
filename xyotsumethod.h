#ifndef XYOTSUMETHOD
#define XYOTSUMETHOD

#include "xyhistogram.h"

class Otsu
{
public:
    int findThreshold(Histogram& hist, int Width, int Height);
};

#endif // XYOTSUMETHOD

