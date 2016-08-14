#ifndef XYENTROPY
#define XYENTROPY

#include "xyhistogram.h"

class Entropy
{
public:
    int findThreshold(Histogram& hist, int Width, int Height);
};

#endif // XYENTROPY

