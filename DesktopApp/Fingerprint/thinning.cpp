#include "thinning.h"

Thinning::Thinning()
{
}


void removeSpurs(cv::Mat& thinMatrix)
{

    int w      = thinMatrix.cols;
    int h      = thinMatrix.rows;
    int j, i, n, t, c;

    c = 0;

    do
    {
        n = 0;
        for (i=1; i<h-1; i++)
            for (j=1; j<w-1; j++)
            {
                if( thinMatrix.at<uchar>(j,i)==0)
                {
                    t=0;
                    if (thinMatrix.at<uchar>(j+1,i-1)==WHITE && thinMatrix.at<uchar>(j,i-1)!=WHITE && thinMatrix.at<uchar>(j+1,i)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j+1,i+1)==WHITE && thinMatrix.at<uchar>(j+1,i)!=WHITE && thinMatrix.at<uchar>(j,i+1)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j-1,i+1)==WHITE && thinMatrix.at<uchar>(j,i+1)!=WHITE && thinMatrix.at<uchar>(j-1,i)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j-1,i-1)==WHITE && thinMatrix.at<uchar>(j-1,i)!=WHITE && thinMatrix.at<uchar>(j,i-1)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j+1,i-1)!=WHITE && thinMatrix.at<uchar>(j+1,i)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j+1,i+1)!=WHITE && thinMatrix.at<uchar>(j,i+1)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j-1,i+1)!=WHITE && thinMatrix.at<uchar>(j-1,i)==WHITE) t++;
                    if (thinMatrix.at<uchar>(j-1,i-1)!=WHITE && thinMatrix.at<uchar>(j,i-1)==WHITE) t++;
                    if (t==1)
                    {
                        thinMatrix.at<uchar>(j,i) = 127;
                        n++;
                    }
                }
            }

        for (i=1; i<h-1; i++)   {
            for (j=1; j<w-1; j++)
            {
                if( thinMatrix.at<uchar>(j,i)==127)
                    thinMatrix.at<uchar>(j,i) = WHITE;
            }
        }
    } while (n>0 && ++c < 5);

}


void Thinning::thin(cv::Mat& src)
{
    int w      = src.cols;
    int h      = src.rows;
    int j,i;
    bool changed=true;

    thinMatrix = src.clone();

    while (changed==true)
    {
        changed = false;
        for (i=1; i<h-1; i++)   {
            for (j=1; j<w-1; j++) {
                if (thinMatrix.at<uchar>(j,i)==BLACK)   {
                    /*!
                     *   WHITE       BLACK
                     *   WHITE BLACK BLACK
                     *   WHITE       BLACK
                     */

                    if (thinMatrix.at<uchar>(j-1,i-1)==WHITE && thinMatrix.at<uchar>(j-1,i)==WHITE && thinMatrix.at<uchar>(j-1,i+1)==WHITE &&
                        thinMatrix.at<uchar>(j+1,i-1)!=WHITE && thinMatrix.at<uchar>(j+1,i)!=WHITE && thinMatrix.at<uchar>(j+1,i+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }

                    /*!
                     *    WHITE WHITE WHITE
                     *          BLACK
                     *    BLACK BLACK BLACK
                     */

                    if (thinMatrix.at<uchar>(j-1,i+1)==WHITE && thinMatrix.at<uchar>(j,i+1)==WHITE && thinMatrix.at<uchar>(j+1,i+1)==WHITE &&
                        thinMatrix.at<uchar>(j-1,i-1)!=WHITE && thinMatrix.at<uchar>(j,i-1)!=WHITE && thinMatrix.at<uchar>(j+1,i-1)!=WHITE)

                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }

                    /*!
                     *    BLACK       WHITE
                     *    BLACK BLACK WHITE
                     *    BLACK       WHITE
                     */


                    if (thinMatrix.at<uchar>(j+1,i-1)==WHITE && thinMatrix.at<uchar>(j+1,i)==WHITE && thinMatrix.at<uchar>(j+1,i+1)==WHITE &&
                        thinMatrix.at<uchar>(j-1,i-1)!=WHITE && thinMatrix.at<uchar>(j-1,i)!=WHITE && thinMatrix.at<uchar>(j-1,i+1)!=WHITE)

                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }


                    /*!
                     *   BLACK BLACK BLACK
                     *         BLACK
                     *   WHITE WHITE WHITE
                     */
                    if (thinMatrix.at<uchar>(j-1,i-1)==WHITE && thinMatrix.at<uchar>(j,i-1)==WHITE && thinMatrix.at<uchar>(j+1,i-1)==WHITE &&
                        thinMatrix.at<uchar>(j-1,i+1)!=WHITE && thinMatrix.at<uchar>(j,i+1)!=WHITE && thinMatrix.at<uchar>(j+1,i+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }

                    /*!
                     *     BLACK BLACK
                     *     BLACK BLACK WHITE
                     *           WHITE
                     */

                    if (thinMatrix.at<uchar>(j-1,i+1)==WHITE && thinMatrix.at<uchar>(j-1,i)==WHITE && thinMatrix.at<uchar>(j,i+1)==WHITE &&
                            thinMatrix.at<uchar>(j+1,i)!=WHITE && thinMatrix.at<uchar>(j,i-1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }

                    /*!
                                 WHITE
                     *     BLACK BLACK WHITE
                     *     BLACK BLACK
                     */

                    if (thinMatrix.at<uchar>(j-1,i-1)==WHITE && thinMatrix.at<uchar>(j,i-1)==WHITE && thinMatrix.at<uchar>(j-1,i)==WHITE &&
                            thinMatrix.at<uchar>(j+1,i)!=WHITE && thinMatrix.at<uchar>(j,i+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }

                    /*!
                     *          WHITE
                     *    WHITE BLACK BLACK
                     *          BLACK BLACK
                     */

                    if (thinMatrix.at<uchar>(j,i-1)==WHITE && thinMatrix.at<uchar>(j+1,i-1)==WHITE && thinMatrix.at<uchar>(j+1,i)==WHITE &&
                            thinMatrix.at<uchar>(j-1,i)!=WHITE && thinMatrix.at<uchar>(j,i+1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }

                    /*!
                     *         BLACK BLACK
                     *   WHITE BLACK BLACK
                     *         WHITE
                     */

                    if (thinMatrix.at<uchar>(j+1,i+1)==WHITE && thinMatrix.at<uchar>(j+1,i)==WHITE && thinMatrix.at<uchar>(j,i+1)==WHITE &&
                            thinMatrix.at<uchar>(j-1,i)!=WHITE && thinMatrix.at<uchar>(j,i-1)!=WHITE)
                    {
                        thinMatrix.at<uchar>(j,i)=WHITE;
                        changed = true;
                    }
                }
            }
        }
    }

    removeSpurs(thinMatrix);


}
