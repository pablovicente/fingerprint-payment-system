#include "binarization.h"


Binarization::Binarization()
{
}

Binarization::Binarization(int h, int w)
{
    binMatrix = cv::Mat(h, w,CV_8UC1);
    binMatrix(cv::Rect(0,0,h,w)) = cv::Scalar::all(255);
}


void Binarization::binarize(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& segmentedMatrix, int threshold, int blockSize)
{

    int value = src.rows - oiMatrix.rows*blockSize;
    int border = value >= blockSize ? value : blockSize;
    float temp;

    /*!
     * Todos los valores que sean menores que el threshold
     * y esten dentro de la mascara se ponen a 0
     */
    for(int i=blockSize; i<src.rows-border; i++)
        for(int j=blockSize; j<src.cols-border; j++)
        {
            if(src.at<float>(i,j) < threshold && segmentedMatrix.at<uchar>(i,j) != 255)
                binMatrix.at<uchar>(i,j) = BLACK;
        }


    /*!
     * Si el bloque en el que se encuentran los pixeles es nulo, se ponen a 255
     */
    for(int i=0; i<oiMatrix.rows; i++)
        for(int j=0; j<oiMatrix.cols; j++)
        {

            temp = oiMatrix.at<float>(i,j);
            if(oiMatrix.at<float>(i,j) >= 254.5 && oiMatrix.at<float>(i,j) <= 256)
            {
                for(int x=i*blockSize; x<i*blockSize+blockSize; x++)
                    for(int y=j*blockSize; y<j*blockSize+blockSize;y++)
                        binMatrix.at<uchar>(x,y) = WHITE;
            }
        }


}
