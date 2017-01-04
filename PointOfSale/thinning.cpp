#include "thinning.h"

Thinning::Thinning()
{
}


void removeSpurs(cv::Mat& thinMatrix)
{

    int w      = thinMatrix.cols;
    int h      = thinMatrix.rows;
    int x, y, n, t, c;

    c = 0;

    do
    {
        n = 0;
        for (y=1; y<h-1; y++)
            for (x=1; x<w-1; x++)
            {
                if( thinMatrix.at<uchar>(x,y)==0)
                {
                    t=0;
                    if (thinMatrix.at<uchar>(x+1,y-1)==WHITE && thinMatrix.at<uchar>(x,y-1)!=WHITE && thinMatrix.at<uchar>(x+1,y)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x+1,y+1)==WHITE && thinMatrix.at<uchar>(x+1,y)!=WHITE && thinMatrix.at<uchar>(x,y+1)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x-1,y+1)==WHITE && thinMatrix.at<uchar>(x,y+1)!=WHITE && thinMatrix.at<uchar>(x-1,y)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x-1,y-1)==WHITE && thinMatrix.at<uchar>(x-1,y)!=WHITE && thinMatrix.at<uchar>(x,y-1)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x+1,y-1)!=WHITE && thinMatrix.at<uchar>(x+1,y)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x+1,y+1)!=WHITE && thinMatrix.at<uchar>(x,y+1)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x-1,y+1)!=WHITE && thinMatrix.at<uchar>(x-1,y)==WHITE) t++;
                    if (thinMatrix.at<uchar>(x-1,y-1)!=WHITE && thinMatrix.at<uchar>(x,y-1)==WHITE) t++;
                    if (t==1)
                    {
                        thinMatrix.at<uchar>(x,y) = 127;
                        n++;
                    }
                }
            }

        for (y=1; y<h-1; y++)   {
            for (x=1; x<w-1; x++)
            {
                if( thinMatrix.at<uchar>(x,y)==127)
                    thinMatrix.at<uchar>(x,y) = WHITE;
            }
        }
    } while (n>0 && ++c < 5);

}


void Thinning::thin(cv::Mat& src)
{
    int w      = src.cols;
    int h      = src.rows;
    int x,y;
    bool changed=true;

    thinMatrix = src.clone();

    while (changed==true)
    {
        changed = false;
        for (y=1; y<h-1; y++)
            for (x=1; x<w-1; x++)
            {
                if (thinMatrix.at<uchar>(x,y)==0)
                {
                    /*!
                     *   1   0
                     *   1 1 0
                     *   1   0
                     */

                    if (thinMatrix.at<uchar>(x-1,y-1)==WHITE && thinMatrix.at<uchar>(x-1,y)==WHITE && thinMatrix.at<uchar>(x-1,y+1)==WHITE &&
                        thinMatrix.at<uchar>(x+1,y-1)!=WHITE && thinMatrix.at<uchar>(x+1,y)!=WHITE && thinMatrix.at<uchar>(x+1,y+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }

                    /*!
                     *    1 1 1
                     *      1
                     *    0 0 0
                     */

                    if (thinMatrix.at<uchar>(x-1,y+1)==WHITE && thinMatrix.at<uchar>(x,y+1)==WHITE && thinMatrix.at<uchar>(x+1,y+1)==WHITE &&
                        thinMatrix.at<uchar>(x-1,y-1)!=WHITE && thinMatrix.at<uchar>(x,y-1)!=WHITE && thinMatrix.at<uchar>(x+1,y-1)!=WHITE)

                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }

                    /*!
                     *    0   1
                     *    0 1 1
                     *    0   1
                     */


                    if (thinMatrix.at<uchar>(x+1,y-1)==WHITE && thinMatrix.at<uchar>(x+1,y)==WHITE && thinMatrix.at<uchar>(x+1,y+1)==WHITE &&
                        thinMatrix.at<uchar>(x-1,y-1)!=WHITE && thinMatrix.at<uchar>(x-1,y)!=WHITE && thinMatrix.at<uchar>(x-1,y+1)!=WHITE)

                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }


                    /*!
                     *   0 0 0
                     *     1
                     *   1 1 1
                     */
                    if (thinMatrix.at<uchar>(x-1,y-1)==WHITE && thinMatrix.at<uchar>(x,y-1)==WHITE && thinMatrix.at<uchar>(x+1,y-1)==WHITE &&
                        thinMatrix.at<uchar>(x-1,y+1)!=WHITE && thinMatrix.at<uchar>(x,y+1)!=WHITE && thinMatrix.at<uchar>(x+1,y+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }

                    /*!
                     *     0 0
                     *     0 1 1
                     *         1
                     */

                    if (thinMatrix.at<uchar>(x-1,y+1)==WHITE && thinMatrix.at<uchar>(x-1,y)==WHITE && thinMatrix.at<uchar>(x,y+1)==WHITE &&
                            thinMatrix.at<uchar>(x+1,y)!=WHITE && thinMatrix.at<uchar>(x,y-1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }

                    /*!
                             1
                     *     0 1 1
                     *     0 0
                     */

                    if (thinMatrix.at<uchar>(x-1,y-1)==WHITE && thinMatrix.at<uchar>(x,y-1)==WHITE && thinMatrix.at<uchar>(x-1,y)==WHITE &&
                            thinMatrix.at<uchar>(x+1,y)!=WHITE && thinMatrix.at<uchar>(x,y+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }

                    /*!
                     *      1
                     *    1 1 0
                     *      0 0
                     */

                    if (thinMatrix.at<uchar>(x,y-1)==WHITE && thinMatrix.at<uchar>(x+1,y-1)==WHITE && thinMatrix.at<uchar>(x+1,y)==WHITE &&
                            thinMatrix.at<uchar>(x-1,y)!=WHITE && thinMatrix.at<uchar>(x,y+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }

                    /*!
                     *     0 0
                     *   1 1 0
                     *     1
                     */

                    if (thinMatrix.at<uchar>(x+1,y+1)==WHITE && thinMatrix.at<uchar>(x+1,y)==WHITE && thinMatrix.at<uchar>(x,y+1)==WHITE &&
                            thinMatrix.at<uchar>(x-1,y)!=WHITE && thinMatrix.at<uchar>(x,y-1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(x,y)=WHITE;
                        changed = true;
                    }
                }
            }
    }

    removeSpurs(thinMatrix);


}
