#include "segmentation.h"

Segmentation::Segmentation()
{
}

void Segmentation::segmentOrientationImage(cv::Mat& src, cv::Mat& orientation, int blockSize)
{
    cv::Mat varianceMatrix;
    float threshold, blockVariance, max, min;

    /// Load image
    varianceMatrix = cv::Mat::zeros(orientation.size(), CV_32F);

    /// Initialize values
    threshold = SEGMENTATION_THRESHOLD;
    max = 0;
    min = std::numeric_limits<float>::max();
    MathOperation mathSegmentation(blockSize*blockSize);


    for(int i = 0; i < src.rows/blockSize; i++)   {
        for(int j = 0; j < src.cols/blockSize; j++) {

            for(int u=i*blockSize; u < i*blockSize + blockSize; u++)    {
                for(int v=j*blockSize; v< j*blockSize + blockSize; v++)     {
                    mathSegmentation.values.push_back(src.at<uchar>(u,v));
                }
            }

            blockVariance = mathSegmentation.CalculateVariane();
            mathSegmentation.values.clear();

            varianceMatrix.at<float>(i,j) = blockVariance;

            if(varianceMatrix.at<float>(i,j) > max)
                max = varianceMatrix.at<float>(i,j);
            if(varianceMatrix.at<float>(i,j) < min)
                min = varianceMatrix.at<float>(i,j);
        }
    }

    for(int i = 0; i < varianceMatrix.rows; i++)   {
        for(int j = 0; j < varianceMatrix.cols; j++) {
            varianceMatrix.at<float>(i,j) = roundf(254.0 * (varianceMatrix.at<float>(i,j) - min) / (max - min));
        }
    }

    for(int i = 0; i < orientation.rows; i++)   {
        for(int j = 0; j < orientation.cols; j++) {
            if((orientation.at<float>(i,j) != 255) && (varianceMatrix.at<float>(i,j) <= threshold))
                orientation.at<float>(i,j) = 255;
        }
    }

   enhanceOrientationImage(orientation);
}

void Segmentation::enhanceOrientationImage(cv::Mat& oi)
{

    cv::Mat neighborsMatrix;
    neighborsMatrix = cv::Mat::zeros(oi.size(), CV_8UC1);

    for (int i0 = 0; i0 < oi.rows; i0++)
        for (int j0 = 0; j0 < oi.cols; j0++)
            if (oi.at<float>(i0, j0) != 255)
            {
                int lowRow = qMax(0, i0 - 1);
                int lowCol = qMax(0, j0 - 1);
                int highRow = qMin(i0 + 1, oi.rows - 1);
                int highCol = qMin(j0 + 1, oi.cols - 1);
                for (int i1 = lowRow; i1 <= highRow; i1++)
                    for (int j1 = lowCol; j1 <= highCol; j1++)
                        if (oi.at<float>(i1, j1) != 255)
                            neighborsMatrix.at<uchar>(i1, j1)++;
            }


    for (int i0 = 0; i0 < oi.rows; i0++)
        for (int j0 = 0; j0 < oi.cols; j0++)
            if (oi.at<float>(i0, j0) != 255)
            {
                bool shouldRemove = true;
                int lowRow = qMax(0, i0 - 1);
                int lowCol = qMax(0, j0 - 1);
                int highRow = qMin(i0 + 1, oi.rows - 1);
                int highCol = qMin(j0 + 1, oi.cols - 1);
                for (int i1 = lowRow; i1 <= highRow && shouldRemove; i1++)
                    for (int j1 = lowCol; j1 <= highCol && shouldRemove; j1++)
                        if (neighborsMatrix.at<uchar>(i1, j1)== 9)
                            shouldRemove = false;
                if (shouldRemove)
                    oi.at<float>(i0, j0) = 255;
            }
}



cv::Mat Segmentation::segmentSourceImage(cv::Mat& src, cv::Mat& orientation, int blockSize)
{
    cv::Mat segmentationMask, varianceMatrix;
    float threshold, blockVariance, max, min;

    varianceMatrix = cv::Mat::zeros(orientation.size(), CV_32F);
    segmentationMask = cv::Mat(src.size(), CV_8UC1);
    segmentationMask(cv::Rect(0,0,src.rows,src.cols)) = cv::Scalar::all(255);
    segmentationMask(cv::Rect(blockSize,blockSize,src.rows-blockSize*2,src.cols-blockSize*2)) = cv::Scalar::all(0);

    /// Initialize values
    threshold = SEGMENTATION_THRESHOLD;
    max = 0;
    min = std::numeric_limits<float>::max();
    MathOperation mathSegmentation(blockSize*blockSize);


    for(int i = 0; i < orientation.rows; i++)   {
        for(int j = 0; j < orientation.cols; j++) {

            for(int u=i*blockSize; u < i*blockSize + blockSize; u++) {
                for(int v=j*blockSize; v< j*blockSize + blockSize; v++) {
                    mathSegmentation.values.push_back(src.at<uchar>(u,v));
                }
            }

            blockVariance = mathSegmentation.CalculateVariane();
            mathSegmentation.values.clear();

            varianceMatrix.at<float>(i,j) = blockVariance;

            if(varianceMatrix.at<float>(i,j) > max)
                max = varianceMatrix.at<float>(i,j);
            if(varianceMatrix.at<float>(i,j) < min)
                min = varianceMatrix.at<float>(i,j);
        }
    }

    for(int i = 0; i < varianceMatrix.rows; i++)   {
        for(int j = 0; j < varianceMatrix.cols; j++) {
            varianceMatrix.at<float>(i,j) = roundf(254.0 * (varianceMatrix.at<float>(i,j) - min) / (max - min));
        }
    }

    for(int i = 0; i < orientation.rows; i++)   {
        for(int j = 0; j < orientation.cols; j++) {
            if((orientation.at<float>(i,j) == NOT_ORIENTED) && (varianceMatrix.at<float>(i,j) <= threshold))
            {
                for(int x = i*16; x < i*16+16; x++)
                    for(int y = j*16; y < j*16+16; y++) {
                        segmentationMask.at<uchar>(x,y) = 255;
                    }
            }
        }
    }



    /*!
     * Proceso de apertura y clausura de la imagen
     */

    int morph_size = 8;

    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size( 2*morph_size + 1, 2*morph_size+1 ), cv::Point( morph_size, morph_size ) );

    /// Clausura
    cv::morphologyEx( segmentationMask, segmentationMask, cv::MORPH_CLOSE, element );

    /// Apertura
    cv::morphologyEx( segmentationMask, segmentationMask, cv::MORPH_OPEN, element );

    return segmentationMask;

}

