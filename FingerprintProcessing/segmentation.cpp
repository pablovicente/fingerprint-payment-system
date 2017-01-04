#include "segmentation.h"

Segmentation::Segmentation()
{
}

void Segmentation::segmentOrientationImage(cv::Mat& src, cv::Mat& orientation, int blockSize)
{
    cv::Mat varianceMatrix;
    float threshold, blockVariance, max, min;
    cv::Mat previousOi = orientation.clone();

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
            if((orientation.at<float>(i,j) != NOT_ORIENTED) && (varianceMatrix.at<float>(i,j) <= threshold))
                orientation.at<float>(i,j) = NOT_ORIENTED;
        }
    }

   recoverLostBlocks(previousOi, orientation);
   enhanceOrientationImage(orientation);
}

void Segmentation::recoverLostBlocks(cv::Mat& previousOi, cv::Mat& newOi)
{

    int neighbors = 0;

    for (int i = 0; i < newOi.rows; i++)
        for (int j = 0; j < newOi.cols; j++)
            if (newOi.at<float>(i, j) == NOT_ORIENTED)
            {
                neighbors = 0;
                for (int u = i - 1; u <= i + 1; u++)
                    for (int v = j - 1; v <= j + 1; v++)
                        if (i>=0 && i<=(newOi.rows - 1) && j>=0 && j<=(newOi.rows - 1) && newOi.at<float>(u, v) != NOT_ORIENTED)
                            neighbors++;

                if(neighbors >= 8)
                     newOi.at<float>(i, j) = previousOi.at<float>(i, j);
            }

}

void Segmentation::enhanceOrientationImage(cv::Mat& newOi)
{    

    cv::Mat neighborsMatrix;
    neighborsMatrix = cv::Mat::zeros(newOi.size(), CV_8UC1);
    bool remove;

    for (int i = 0; i < newOi.rows; i++)
        for (int j = 0; j < newOi.cols; j++)
            if (newOi.at<float>(i, j) != NOT_ORIENTED)
            {
                for (int u = i - 1; u <= i + 1; u++)
                    for (int v = j - 1; v <= j + 1; v++)
                        if (i>=0 && i<=(newOi.rows - 1) && j>=0 && j<=(newOi.rows - 1) && newOi.at<float>(u, v) != NOT_ORIENTED)
                            neighborsMatrix.at<uchar>(u, v)++;
            }


    for (int i = 0; i < newOi.rows; i++)
        for (int j = 0; j < newOi.cols; j++)
            if (newOi.at<float>(i, j) != 255)
            {
                remove = true;
                for (int u = i - 1; u <= (i + 1) && remove ; u++)
                    for (int v = j - 1; v <= (j + 1) && remove; v++)
                        if (i>=0 && i<=(newOi.rows - 1) && j>=0 && j<=(newOi.rows - 1) && neighborsMatrix.at<uchar>(u, v)== 9)
                            remove = false;

                if (remove && newOi.at<float>(i,j) != NOT_ORIENTED)
                    newOi.at<float>(i, j) = NOT_ORIENTED;
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
            varianceMatrix.at<float>(i,j) = roundf(NORMALIZATION_MAX * (varianceMatrix.at<float>(i,j) - min) / (max - min));
        }
    }

    for(int i = 0; i < orientation.rows; i++)   {
        for(int j = 0; j < orientation.cols; j++) {
            if((orientation.at<float>(i,j) == NOT_ORIENTED) && (varianceMatrix.at<float>(i,j) <= threshold))
            {
                for(int x = i*BLOCK_SIZE; x < i*BLOCK_SIZE+BLOCK_SIZE; x++)
                    for(int y = j*BLOCK_SIZE; y < j*BLOCK_SIZE+BLOCK_SIZE; y++) {
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

