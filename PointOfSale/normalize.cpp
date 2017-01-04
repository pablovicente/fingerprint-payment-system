#include "normalize.h"
#include "mathoperation.h"

#include <QDebug>

Normalize::Normalize()
{
}

void Normalize::normalizacionMask(cv::Mat& src)
{
    cv::Mat normalizationMask;
    cv::Scalar meanScalar, varianceScalar;
    cv::Scalar desiredMeanScalar, desiredVarianceScalar;
    cv::Scalar intensity, temp;

    normalizationMask = cv::Mat::zeros(src.size(), CV_8UC1);

    desiredMeanScalar = 100;
    desiredVarianceScalar = 125;
    MathOperation mathImage(src.rows*src.cols, src);

    meanScalar = cv::mean(src);
    varianceScalar = mathImage.CalculateVariane();


    for(int i=0; i < src.rows; i++) {
        for(int j=0; j< src.cols; j++) {

            intensity = src.at<u_char>(i,j);
            temp = pow((intensity.val[0]-meanScalar.val[0]),2);
            temp = sqrt((desiredVarianceScalar.val[0]*temp.val[0])/varianceScalar.val[0]);

            if(intensity.val[0] > meanScalar.val[0])    {
                normalizationMask.at<uchar>(i,j) = desiredMeanScalar.val[0] + temp.val[0];
            }
            else    {
                normalizationMask.at<uchar>(i,j) = desiredMeanScalar.val[0] - temp.val[0];
            }
        }
    }

}

void Normalize::normalizacion(cv::Mat& src)
{
    equalizeHist( src, src );
}
