#include "xyentropy.h"
#include <Cmath>
#include <QDebug>

int Entropy::findThreshold(Histogram& hist, int Width, int Height)
{
    double p[256]={0.0};
    double pt[256]={0.0};
    double entropy1[256]={0.0};
    double entropy2[256]={0.0};
    double entropy[256]={0,0};

    int pixNum = Width * Height;

    int T = 0; //Threshold

    p[0] = double(hist.getHistvalue(0)) / double(pixNum);
    pt[0] = p[0];

    if (p[0]!=0.0)
    {
        entropy1[0] = log(p[0]) / log(2.0) * p[0];
    }

    for(int i=1; i<256; i++)
    {
        p[i] = double(hist.getHistvalue(i)) / double(pixNum);
        pt[i] = p[i] + pt[i-1];

        if (p[i]!=0.0)
        {
            entropy1[i] = entropy1[i-1] + log(p[i]) / log(2.0) * p[i];
        }
        else
        {
            entropy1[i] = entropy1[i-1];
        }

    }

    for(int i=0; i<256; i++)
    {
        entropy2[i] = entropy1[255] - entropy1[i];
        if (pt[i]!=0.0 && pt[i] != 1.0)
        {
            entropy[i] = log(pt[i]) / log(2.0)
                    + log(1 - pt[i]) / log(2.0)
                    - entropy1[i] / pt[i]
                    - entropy2[i] / (1 - pt[i]);
        }
    }

    //qDebug()<<entropy1[176]<<" "<<entropy1[177];
    //qDebug()<<entropy2[176]<<" "<<entropy2[177];
    //qDebug()<<p[176]<<" "<<p[177]<<" "<<log(p[176]) / log(2.0) * p[176];
    //qDebug()<<pt[176]<<" "<<pt[177];
    //qDebug()<<entropy[176]<<" "<<entropy[177];

    double maxEntropy = 0.0;

    for (int i=0; i<256; i++)
    {
        if (entropy[i] > maxEntropy)
        {
            maxEntropy = entropy[i];
            T = i;
        }
    }

    return T;

}
