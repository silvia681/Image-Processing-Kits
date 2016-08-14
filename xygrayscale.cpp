#include"xygrayscale.h"

void Grayscale::dilate(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth)
{
    int value=0;
    int newvalue=0;

    if (depth==32)
    {
        for (int ii=150; ii<width-1; ii++)
        {
            for (int jj=225; jj<height-1; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=0; k1<3; k1++)
                {
                    for (int k2=0; k2<3; k2++)
                    {
						newvalue=qRed(image->pixel(ii+1-k2, jj+1-k1));
                       if(k[k1][k2]&&(newvalue+k[k1][k2])>value)
                       {
                           //value=qRed(image->pixel(ii+1-k2, jj+1-k1));
                           value=newvalue;
                       }
                    }
                }
                if(value>255) value=255;

                newimage->setPixel(ii, jj, qRgb(value, value, value));
            }
        }
    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=0; k1<3; k1++)
                {
                    for (int k2=0; k2<3; k2++)
                    {
                        if(k[k1][k2]&&(newvalue=qRed(image->pixel(ii+1-k2, jj+1-k1))+k[k1][k2])>value)
                        {
                            //value=qRed(image->pixel(ii+1-k2, jj+1-k1));
                            value=newvalue;
                        }
                    }
                }
                if(value>255) value=255;

                newimage->setPixel(ii, jj, value);
            }
        }
    }
}

void Grayscale::dilate(QImage *image, QImage *newimage, int radius, int width, int height, int depth)
{
    int value=0;

    if (depth==32)
    {
        for (int ii=radius; ii<width-radius; ii++)
        {
            for (int jj=radius; jj<height-radius; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=ii-radius; k1<=ii+radius; k1++)
                {
                    for (int k2=jj-radius; k2<=jj+radius; k2++)
                    {
                       if(qRed(image->pixel(k1, k2))>value)
                       {
                           value=qRed(image->pixel(k1, k2));
                       }
                    }
                }

                newimage->setPixel(ii, jj, qRgb(value, value, value));
            }
        }
    }
    else
    {
        for (int ii=radius; ii<width-radius; ii++)
        {
            for (int jj=radius; jj<height-radius; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=ii-radius; k1<=ii+radius; k1++)
                {
                    for (int k2=jj-radius; k2<=jj+radius; k2++)
                    {
                       if(qRed(image->pixel(k1, k2))>value)
                       {
                           value=qRed(image->pixel(k1, k2));
                       }
                    }
                }

                newimage->setPixel(ii, jj, value);
            }
        }
    }
}

void Grayscale::erose(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth)
{
    int value=0;
    int newvalue=0;

    if (depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=0; k1<3; k1++)
                {
                    for (int k2=0; k2<3; k2++)
                    {
                       if(k[k1][k2]&&(newvalue=qRed(image->pixel(ii-1+k2, jj-1+k1))-k[k1][k2])<value)
                       {
                           value=newvalue;
                       }
                    }
                }
                if(value<0) value=0;

                newimage->setPixel(ii, jj, qRgb(value, value, value));
            }
        }
    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=0; k1<3; k1++)
                {
                    for (int k2=0; k2<3; k2++)
                    {
                       if(k[k1][k2]&&(newvalue=qRed(image->pixel(ii-1+k2, jj-1+k1))-k[k1][k2])<value)
                       {
                           value=newvalue;
                       }
                    }
                }
                if(value<0) value=0;

                newimage->setPixel(ii, jj, value);
            }
        }
    }
}

void Grayscale::erose(QImage *image, QImage *newimage, int radius, int width, int height, int depth)
{
    int value=0;

    if (depth==32)
    {
        for (int ii=radius; ii<width-radius; ii++)
        {
            for (int jj=radius; jj<height-radius; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=ii-radius; k1<=ii+radius; k1++)
                {
                    for (int k2=jj-radius; k2<=jj+radius; k2++)
                    {
                       if(qRed(image->pixel(k1, k2))<value)
                       {
                           value=qRed(image->pixel(k1, k2));
                       }
                    }
                }

                newimage->setPixel(ii, jj, qRgb(value, value, value));
            }
        }
    }
    else
    {
        for (int ii=radius; ii<width-radius; ii++)
        {
            for (int jj=radius; jj<height-radius; jj++)
            {
                value=qRed(image->pixel(ii, jj));

                for (int k1=ii-radius; k1<=ii+radius; k1++)
                {
                    for (int k2=jj-radius; k2<=jj+radius; k2++)
                    {
                       if(qRed(image->pixel(k1, k2))<value)
                       {
                           value=qRed(image->pixel(k1, k2));
                       }
                    }
                }

                newimage->setPixel(ii, jj, value);
            }
        }
    }
}

void Grayscale::OBR(QImage *mask, QImage *marker, QImage *dimage, int radius, int width, int height, int depth)
{
    //mask:imageobject
    //marker:
    bool mark;

    QImage temp = *dimage;

    while(1)
    {
        mark = true;

        dilate(marker, dimage, radius, width, height, depth);

        if(depth==32)
        {
            for (int ii=0; ii<width; ii++)
            {
                for (int jj=0; jj<height; jj++)
                {
                    if(qRed(dimage->pixel(ii,jj))>qRed(mask->pixel(ii,jj)))
                    {
                        //mark = false;
                        dimage->setPixel(ii,jj,mask->pixel(ii,jj));
                    }
                    if(qRed(dimage->pixel(ii,jj))!=qRed(temp.pixel(ii,jj)))
                    {
                        mark = false;
                    }
                }
            }

            *marker = *dimage;
            temp = *dimage;

            //mark=true;

            if(mark)
            {
                break;
            }
        }
        else
        {
            for (int ii=0; ii<width; ii++)
            {
                for (int jj=0; jj<height; jj++)
                {
                    if(qRed(dimage->pixel(ii,jj))>qRed(mask->pixel(ii,jj)))
                    {
                        //mark = false;
                        dimage->setPixel(ii,jj,qRed(mask->pixel(ii,jj)));
                    }
                    if(qRed(dimage->pixel(ii,jj))!=qRed(temp.pixel(ii,jj)))
                    {
                        mark = false;
                    }
                }
            }

            *marker = *dimage;
            temp = *dimage;

            //mark=true;

            if(mark)
            {
                break;
            }
        }

    }

}
