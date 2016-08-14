#include "xyotsumethod.h"
#include <cmath>
#include <QDebug>
using namespace std;

int Otsu::findThreshold(Histogram& hist, int Width, int Height)
{

    double p[256], interVar[256];
    double sumP1[256] = {0.0};
    double sumP2[256] = {0.0};
    double mean1[256] = {0.0};
    double mean2[256] = {0.0};
    double sumipi = 0;
    int T=0; //threshold

    int pixNum = Width * Height;
    int sum = 0;

    p[0] = hist.getHistvalue(0) / double(pixNum);
    sumP1[0] = p[0];
    sumP2[0] = 1 - p[0];

    for (int i=1; i<256; i++)
    {
     sum += i * hist.getHistvalue(i);
    }

    double mean = double(sum) / pixNum;

    mean2[0] = ( mean - mean1[0] * sumP1[0] ) / sumP2[0];
    interVar[0] = sumP1[0] * sumP2[0] * pow( mean1[0] - mean2[0], 2 );

    for (int i=1; i<256; i++)
    {
     p[i] = hist.getHistvalue(i) / double(pixNum);
     sumP1[i] = sumP1[i-1] + p[i];
     sumP2[i] = 1.0 - sumP1[i];
     sumipi += i * p[i];
     if (sumP1[i]==0)
     {
         mean1[i]=0;
     }
     else
     {
        mean1[i] = sumipi / sumP1[i];
     }
     if (sumP2[i]==0)
     {
         mean2[i]=0;
     }
     else
     {
        mean2[i] = ( mean - mean1[i] * sumP1[i] ) / sumP2[i];
     }
     interVar[i] = sumP1[i] * sumP2[i] * pow( mean1[i] - mean2[i], 2 );
    }

    double maxVar = interVar[0];

    //qDebug()<<hist.getHistvalue(150)<<" "<<hist.getHistvalue(151)<<" "<<pixNum;
    //qDebug()<<p[150]<<" "<<p[151];
    //qDebug()<<sumP1[1]<<" "<<sumP2[1];
    //qDebug()<<mean;
    //qDebug()<<mean1[1]<<" "<<mean2[1]<<pow( mean1[1] - mean2[1], 2 );
    //qDebug()<<interVar[0]<<" "<<interVar[1]<<" "<<interVar[2];

    for (int i=1; i<256; i++)
    {
     if (interVar[i]>maxVar)
     {
         T = i;
         maxVar = interVar[i];
     }
    }

    return T;



    //for (int i)

}
