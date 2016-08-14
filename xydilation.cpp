#include "xydilation.h"
#include "qdebug.h"
#include <QQueue>

void Dilation::dilate(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth)
{
    if (depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(image->pixel(ii,jj))==255)
                {
                    for (int k1=0; k1<3; k1++)
                    {
                        for (int k2=0; k2<3; k2++)
                        {
                           if(k[k1][k2])
                           {
                               newimage->setPixel(ii-1+k2, jj-1+k1, qRgb(255, 255, 255));
                               //qDebug()<<ii<<","<<jj<<endl<<k1<<","<<k2;
                           }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(image->pixel(ii,jj))==255)
                {
                    for (int k1=0; k1<3; k1++)
                    {
                        for (int k2=0; k2<3; k2++)
                        {
                           if(k[k1][k2])
                           {
                               newimage->setPixel(ii-1+k2, jj-1+k1, 255);
                               //qDebug()<<ii<<","<<jj<<endl<<k1<<","<<k2;
                           }
                        }
                    }
                }
            }
        }
    }
}

void Dilation::erosion(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth)
{
    bool mark=false;

    if(depth==32)
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(image->pixel(ii,jj))==255)
                {
                    mark=true;

                    for (int k1=0; k1<3; k1++)
                    {
                        for (int k2=0; k2<3; k2++)
                        {
                           if(k[k1][k2])
                           {
                               if(!qRed(image->pixel(ii-1+k2, jj-1+k1)))
                               {
                                mark=false;
                               }
                           }
                        }
                    }

                    if(mark)
                    {
                        newimage->setPixel(ii, jj, qRgb(255, 255, 255));//can be removed
                    }
                    else
                    {
                        newimage->setPixel(ii, jj, qRgb(0, 0, 0));
                    }
                }
            }
        }
    }
    else
    {
        for (int ii=1; ii<width-1; ii++)
        {
            for (int jj=1; jj<height-1; jj++)
            {
                if (qRed(image->pixel(ii,jj))==255)
                {
                    mark=true;

                    for (int k1=0; k1<3; k1++)
                    {
                        for (int k2=0; k2<3; k2++)
                        {
                           if(k[k1][k2])
                           {
                               if(!qRed(image->pixel(ii-1+k2, jj-1+k1)))
                               {
                                mark=false;
                               }
                           }
                        }
                    }

                    if(mark)
                    {
                        newimage->setPixel(ii, jj, 255);//can be removed
                    }
                    else
                    {
                        newimage->setPixel(ii, jj, 0);
                    }
                }
            }
        }
    }
}

int Dilation::distance(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth)
{
    int gray=1;
    bool mark;
    bool stop;

    QImage temp0 = *(image);
    QImage temp1 = temp0;
    //QImage temp2 = temp1;

    if(depth==32)
    {
        while(1)
        {
            stop = true;
            for (int ii=1; ii<width-1; ii++)
            {
                for (int jj=1; jj<height-1; jj++)
                {
                    //qDebug()<<"OK";
                    if (qRed(temp0.pixel(ii,jj))==255)
                    {
                        stop=false;
                        mark=false;
                        //qDebug()<<"OK";

                        for (int k1=0; k1<3; k1++)
                        {
                            for (int k2=0; k2<3; k2++)
                            {
                               if(k[k1][k2])
                               {
                                   if(!qRed(temp0.pixel(ii-1+k2, jj-1+k1)))
                                   {
                                    mark=true;
                                   }
                               }
                            }
                        }

                        if(mark)
                        {
                            temp1.setPixel(ii, jj, qRgb(0, 0, 0));
                            newimage->setPixel(ii,jj,qRgb(gray, gray, gray));
                        }
                    }
                }
            }
            temp0=temp1;
            if(stop)
            {
                break;
            }
            gray=gray+1;
        }
    }
    else
    {
        while(1)
        {
            stop = true;
            for (int ii=1; ii<width-1; ii++)
            {
                for (int jj=1; jj<height-1; jj++)
                {
                    //qDebug()<<"OK";
                    if (qRed(temp0.pixel(ii,jj))==255)
                    {
                        stop=false;
                        mark=false;
                        //qDebug()<<"OK";

                        for (int k1=0; k1<3; k1++)
                        {
                            for (int k2=0; k2<3; k2++)
                            {
                               if(k[k1][k2])
                               {
                                   if(!qRed(temp0.pixel(ii-1+k2, jj-1+k1)))
                                   {
                                    mark=true;
                                   }
                               }
                            }
                        }

                        if(mark)
                        {
                            temp1.setPixel(ii, jj, 0);
                            newimage->setPixel(ii,jj,gray);
                        }
                    }
                }
            }
            temp0=temp1;
            if(stop)
            {
                break;
            }
            gray=gray+1;
        }
    }
    return gray;
}


/*void Dilation::getTemplate(QImage* image, int k[3][3], int order, int x, int y, int width, int height){
	QQueue<SItem> s;
	int** color = new int*[height];
	for(int i = 0; i < height; i ++){
		color[i] = new int[width];
	}

	for(int i =0; i < height; i ++)
		for(int j = 0; j < width; j ++)
			color[i][j]=0;

	color[x][y]=1;
	s.push_back(SItem(x,y,order));
	while (!s.empty()){
		SItem t = s.front();
		s.pop_front();
		color[t.x][t.y]=2;
		image->setPixel(t.x, t.y, qRgb(255, 255, 255));

		if(t.order == 1) continue;

		//range of dilation
		for(int xx = t.x - 1; xx <= t.x + 1; xx ++){
			for(int yy = t.y - 1; yy <= t.y + 1; yy++){
				if(xx < 0 || xx >= width) continue;
				if(yy < 0 || yy >= height) continue;
				if(color[xx][yy]==0 && k[xx-t.x+1][yy-t.y+1]!=0){
					s.push_back(SItem(xx, yy, t.order - 1));
					color[xx][yy]=1;
				}
			}
		}
	}

	for(int i = 0; i < height; i ++){
		delete [] color[i];
	}
	delete [] color;
}

/* Parameter: 
 *			  image:	input image
 *			  newimage: output image
 *			  k:		template
 */
/*
void Dilation::restore(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth){
	QImage tempimage = *image;

	if(depth == 32){
		for (int x = 0; x < width; x ++){
			for (int y = 0; y < height; y ++){
				int value = qRed(image->pixel(x, y));
				if (value == 0) continue;

				this->getTemplate(newimage, k, value, x, y, width, height);
			}
		}
	}
}
*/

void Dilation::restore(QImage *image, QImage *newimage, int k[3][3], int width, int height, int depth)
{
    //image:subset; newimage: skeleton;

    //qDebug()<<k[0][0]<<k[0][1]<<k[0][2];

    QImage tempimage=*image;


    if(depth==32)
    {
        for(int ii=1; ii<width-1; ii++)
        {
            for(int jj=1; jj<height-1; jj++)
            {
                if(int value=qRed(image->pixel(ii, jj)))
                {
                    //newimage->setPixel(ii, jj, qRgb(255, 255, 255));
                    //initialize tempimage
                    for(int tii=ii-value+2; tii<ii+value-1; tii++)
                    {
                        for(int tjj=jj-value+2; tjj<jj+value-1; tjj++)
                        {
                            tempimage.setPixel(tii,tjj,qRgb(0,0,0));
                        }
                    }

					int times = 0;

                    tempimage.setPixel(ii, jj, qRgb(times+1, times+1, times+1));
                    newimage->setPixel(ii, jj, qRgb(255, 255, 255));

                    for(int kk=0; kk<value-1; kk++)
                    {
						times = times + 1;
                        for(int kii=ii-kk; kii<=ii+kk; kii++)
                        {
                            for(int kjj=jj-kk; kjj<=jj+kk; kjj++)
                            {
                                if(qRed(tempimage.pixel(kii,kjj))==times)
                                {
                                    for(int k1=0; k1<3; k1++)
                                    {
                                        for(int k2=0; k2<3; k2++)
                                        {
                                            if(k[k1][k2])
                                            {
                                                //qDebug()<<kii-1+k2<<" "<<kjj-1+k1<<endl;
                                                newimage->setPixel(kii-1+k2, kjj-1+k1, qRgb(255, 255, 255));
                                                tempimage.setPixel(kii-1+k2, kjj-1+k1, qRgb(times+1, times+1, times+1));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
		for(int ii=1; ii<width-1; ii++)
		{
			for(int jj=1; jj<height-1; jj++)
			{
				if(int value=qRed(image->pixel(ii, jj)))
				{
					//newimage->setPixel(ii, jj, qRgb(255, 255, 255));
					//initialize tempimage
					for(int tii=ii-value+2; tii<ii+value-1; tii++)
					{
						for(int tjj=jj-value+2; tjj<jj+value-1; tjj++)
						{
							tempimage.setPixel(tii,tjj,0);
						}
					}

					int times = 0;

					tempimage.setPixel(ii, jj, times+1);
					newimage->setPixel(ii, jj, 255);

					for(int kk=0; kk<value-1; kk++)
					{
						times = times + 1;
						for(int kii=ii-kk; kii<=ii+kk; kii++)
						{
							for(int kjj=jj-kk; kjj<=jj+kk; kjj++)
							{
								if(qRed(tempimage.pixel(kii,kjj))==times)
								{
									for(int k1=0; k1<3; k1++)
									{
										for(int k2=0; k2<3; k2++)
										{
											if(k[k1][k2])
											{
												//qDebug()<<kii-1+k2<<" "<<kjj-1+k1<<endl;
												newimage->setPixel(kii-1+k2, kjj-1+k1, 255);
												tempimage.setPixel(kii-1+k2, kjj-1+k1, times+1);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
    }
}

int Dilation::restore1(QImage *image, QImage *newimage, QImage temp[200], int k[3][3], int width, int height, int depth)
{
    QImage tempimage=*image;
    //QImage *newimage=image;

    int index=0;


    if(depth==32)
    {
        for(int ii=1; ii<width-1; ii++)
        {
            for(int jj=1; jj<height-1; jj++)
            {
                if(int value=qRed(image->pixel(ii, jj)))
                {
                    //newimage->setPixel(ii, jj, qRgb(255, 255, 255));
                    //initialize tempimage
                    for(int tii=ii-value+2; tii<ii+value-1; tii++)
                    {
                        for(int tjj=jj-value+2; tjj<jj+value-1; tjj++)
                        {
                            tempimage.setPixel(tii,tjj,qRgb(0,0,0));
                        }
                    }

                    int times = 0;

                    tempimage.setPixel(ii, jj, qRgb(times+1, times+1, times+1));
                    newimage->setPixel(ii, jj, qRgb(255, 255, 255));

                    for(int kk=0; kk<value-1; kk++)
                    {
                        times = times + 1;
                        for(int kii=ii-kk; kii<=ii+kk; kii++)
                        {
                            for(int kjj=jj-kk; kjj<=jj+kk; kjj++)
                            {
                                if(qRed(tempimage.pixel(kii,kjj))==times)
                                {
                                    for(int k1=0; k1<3; k1++)
                                    {
                                        for(int k2=0; k2<3; k2++)
                                        {
                                            if(k[k1][k2])
                                            {
                                                //qDebug()<<kii-1+k2<<" "<<kjj-1+k1<<endl;
                                                newimage->setPixel(kii-1+k2, kjj-1+k1, qRgb(255, 255, 255));
                                                tempimage.setPixel(kii-1+k2, kjj-1+k1, qRgb(times+1, times+1, times+1));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    temp[index]=*newimage;
                    index++;
                }
            }
        }
    }
    else
    {
        for(int ii=1; ii<width-1; ii++)
        {
            for(int jj=1; jj<height-1; jj++)
            {
                if(int value=qRed(image->pixel(ii, jj)))
                {
                    //newimage->setPixel(ii, jj, qRgb(255, 255, 255));
                    //initialize tempimage
                    for(int tii=ii-value+2; tii<ii+value-1; tii++)
                    {
                        for(int tjj=jj-value+2; tjj<jj+value-1; tjj++)
                        {
                            tempimage.setPixel(tii,tjj,0);
                        }
                    }

                    int times = 0;

                    tempimage.setPixel(ii, jj, times+1);
                    newimage->setPixel(ii, jj, 255);

                    for(int kk=0; kk<value-1; kk++)
                    {
                        times = times + 1;
                        for(int kii=ii-kk; kii<=ii+kk; kii++)
                        {
                            for(int kjj=jj-kk; kjj<=jj+kk; kjj++)
                            {
                                if(qRed(tempimage.pixel(kii,kjj))==times)
                                {
                                    for(int k1=0; k1<3; k1++)
                                    {
                                        for(int k2=0; k2<3; k2++)
                                        {
                                            if(k[k1][k2])
                                            {
                                                //qDebug()<<kii-1+k2<<" "<<kjj-1+k1<<endl;
                                                newimage->setPixel(kii-1+k2, kjj-1+k1, 255);
                                                tempimage.setPixel(kii-1+k2, kjj-1+k1, times+1);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int maxindex=index-1;
    index=0;

    return (maxindex);
}

void Dilation::cond_dilate(QImage *mask, QImage *newimage, int seedx, int seedy, int depth)
{

QQueue<SItem> s;
//bool mark;
SItem t;

s.push_back(SItem(seedx,seedy));

if(depth==32)
{
    newimage->fill(qRgb(0,0,0));

    mask->setPixel(seedx,seedy,qRgb(100,100,100));
    newimage->setPixel(seedx,seedy,qRgb(255,255,255));
    //100 represents the pixel has been visited;
    //255 represents unvisited but should be;
    //150 represents about to be visited.

    while(1)
    {
       // mark=true;

        for(int i=-1;i<=1;i++)
        {
            for(int j=-1;j<=1;j++)
            {
                if(qRed(mask->pixel(seedx+i,seedy+j))==255)
                {
                    //mark=false;
                    mask->setPixel(seedx+i,seedy+j,qRgb(150,150,150));
                    s.push_back(SItem(seedx+i,seedy+j));
                    newimage->setPixel(seedx+i,seedy+j,qRgb(255,255,255));
                }

            }
        }

        s.pop_front();

        if(!s.empty())
        {
            t=s.front();
            seedx=t.x;
            seedy=t.y;
            mask->setPixel(seedx,seedy,qRgb(100,100,100));
        }
        else
        {
            break;
        }

    }
}
else
{
    newimage->fill(0);

    mask->setPixel(seedx,seedy,qRgb(100,100,100));
    newimage->setPixel(seedx,seedy,255);
    //100 represents the pixel has been visited;
    //255 represents unvisited but should be;
    //150 represents about to be visited.

    while(1)
    {
       // mark=true;

        for(int i=-1;i<=1;i++)
        {
            for(int j=-1;j<=1;j++)
            {
                if(qRed(mask->pixel(seedx+i,seedy+j))==255)
                {
                    //mark=false;
                    mask->setPixel(seedx+i,seedy+j,qRgb(150,150,150));
                    s.push_back(SItem(seedx+i,seedy+j));
                    newimage->setPixel(seedx+i,seedy+j,255);
                }

            }
        }

        s.pop_front();

        if(!s.empty())
        {
            t=s.front();
            seedx=t.x;
            seedy=t.y;
            mask->setPixel(seedx,seedy,qRgb(100,100,100));
        }
        else
        {
            break;
        }

    }
}

}
