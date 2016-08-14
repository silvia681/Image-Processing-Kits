#include "xyhistogram.h"

void Histogram::setHistvalue(unsigned int index, int value)
{
    this->histvalue[ index ] = value;
}

void Histogram::setBarsize(unsigned int width, unsigned int height)
{
    bin = (double)width / 255.0;
    int maxhvalue = histvalue[0];

    for(int i=1; i<256; i++)
    {
        if(histvalue[i] > maxhvalue)
        {
            maxhvalue = histvalue[i];
        }
    }

    unitHeight = double(height) / double(maxhvalue);
}
