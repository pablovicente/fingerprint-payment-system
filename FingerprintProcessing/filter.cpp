#include "filter.h"


Filter::Filter()
{
}

float gabor(float x, float y, float phi, float freq, float std2)
{
    phi += M_PI/2;
    float x2 = -x*sin(phi) + y*cos(phi);
    float y2 = x*cos(phi) + y*sin(phi);
    float t1 = (x2*x2)/std2;
    float t2 = (y2*y2)/std2;
    float exponential = exp(-0.5*(t1 + t2));
    return exponential*cos(2*M_PI*x2*freq);
}


void Filter::applyGaborFilter(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& freqMatrix, cv::Mat& gaborMatrix, int blockSize)
{
    int i,j,x,y,u,v;
    int halfBlockSize = blockSize/2;
    float sum, freq, orientation;
    float std = 4.0*4.0;

    for (i = halfBlockSize; i < src.rows-halfBlockSize; i++)
        for (j = halfBlockSize; j < src.cols-halfBlockSize; j++)
        {
            sum = 0.0;
            x = i/blockSize >= (blockSize+2) ? (blockSize+1) : i/blockSize;
            y = j/blockSize >= (blockSize+2) ? (blockSize+1) : j/blockSize;
            orientation = oiMatrix.at<float>(x,y);
            freq = freqMatrix.at<float>(x,y);

            if(orientation < (NOT_ORIENTED-1))  {

                for (u = -halfBlockSize; u <= halfBlockSize; u++)
                    for (v = -halfBlockSize; v <= halfBlockSize; v++)
                    {
                        sum +=  src.at<uchar>((i-u),(j-v))*gabor(u,v,orientation,freq,std);
                    }
            }

            if (sum > (float)WHITE) sum = (float)WHITE;
            if (sum < (float)BLACK) sum = (float)BLACK;

            gaborMatrix.at<float>(i,j) = sum;
        }

}



void Filter::applyGaborFilterToChunk(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& freqMatrix, cv::Mat& gaborMatrix, int min, int max, int blockSize)
{
    int i,j,x,y,u,v;
    int halfBlockSize = blockSize/2;
    float sum, freq, orientation;
    float std = 4.0*4.0;

    for (i = min; i < max; i++) {
        for (j = halfBlockSize; j < src.cols-halfBlockSize; j++)
        {
            sum = 0.0;
            x = i/blockSize >= (blockSize+2) ? (blockSize+1) : i/blockSize;
            y = j/blockSize >= (blockSize+2) ? (blockSize+1) : j/blockSize;
            orientation = oiMatrix.at<float>(x,y);
            freq = freqMatrix.at<float>(x,y);

            if(orientation < (NOT_ORIENTED-1))  {

                for (u = -halfBlockSize; u <= halfBlockSize; u++)
                    for (v = -halfBlockSize; v <= halfBlockSize; v++)
                    {
                        sum +=  src.at<uchar>((i-u),(j-v))*gabor(u,v,orientation,freq,std);
                    }
            }

            if (sum > (float)WHITE) sum = (float)WHITE;
            if (sum < (float)BLACK) sum = (float)BLACK;

            gaborMatrix.at<float>(i,j) = sum;
        }
    }

}


cv::Mat Filter::applySobelFilterX(cv::Mat& src)
{
    cv::Mat xGradients = cv::Mat(src.rows, src.cols, CV_32F);

    int sobelX[SOBEL_SIZE][SOBEL_SIZE] = { {-1,0,1},
                                           {-2,0,2},
                                           {-1,0,1} };

    int dy = SOBEL_SIZE / 2;
    int dx = SOBEL_SIZE / 2;    
    int sum;
    double value;
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++)
        {
            sum = 0;
            for (int yi = i - dy, yj = 0; yi <= i + dy; yi++, yj++)
                for (int xi = j - dx, xj = 0; xi <= j + dx; xi++, xj++)
                    if (yi >= 0 && yi < src.rows && xi >= 0 && xi < src.cols)
                        sum += src.at<uchar>(yi, xi) * sobelX[yj][xj];
                    else
                        sum += WHITE * sobelX[yj][xj];

            value = 1.0 * sum;
            xGradients.at<float>(i, j) = roundf(value);
        }
    }
    return xGradients;
}

cv::Mat Filter::applySobelFilterY(cv::Mat& src)
{
    cv::Mat yGradients = cv::Mat(src.rows, src.cols, CV_32F);
    int sobelY[SOBEL_SIZE][SOBEL_SIZE] = { {-1,-2,-1},
                                           {0,0,0},
                                           {1,2,1}};

    int dy = SOBEL_SIZE / 2;
    int dx = SOBEL_SIZE / 2;    
    int sum;
    double value;
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++)
        {
            sum = 0;
            for (int yi = i - dy, yj = 0; yi <= i + dy; yi++, yj++)
                for (int xi = j - dx, xj = 0; xi <= j + dx; xi++, xj++)
                    if (yi >= 0 && yi < src.rows && xi >= 0 && xi < src.cols)
                        sum += src.at<uchar>(yi, xi) * sobelY[yj][xj];
                    else
                        sum += 255 * sobelY[yj][xj];

            value = 1.0 * sum;
            yGradients.at<float>(i, j) = roundf(value);
        }
    }
    return yGradients;
}
