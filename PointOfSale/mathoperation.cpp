#include "mathoperation.h"


MathOperation::MathOperation()
{

}

MathOperation::MathOperation(int elements)
{
    max = elements;
}

MathOperation::MathOperation(int elements, cv::Mat& mat)
{
    max = elements;
    values.assign(mat.datastart, mat.dataend);
}

double MathOperation::CalculateMean()
{
    double sum = 0;

    for(int i = 0; i < max; i++)
    {
        sum += values[i];
    }

    return (sum / max);
}

double MathOperation::CalculateVariane()
{
    mean = CalculateMean();

    double temp = 0;
    for(int i = 0; i < max; i++)
    {
        temp += (values[i] - mean) * (values[i] - mean) ;
    }
    return temp / max;
}

double MathOperation::GetStandardDeviation()
{
    return sqrt(CalculateVariane());
}


double MathOperation::ceil0( const double& value )
{
    double result = std::ceil( std::fabs( value ) );
    return (value < 0.0) ? -result : result;
}

double MathOperation::roundhalfup( const double& value )
{
    return std::floor( value +0.5 );
}

double MathOperation::roundhalfup0( const double& value )
{
    double result = roundhalfup( std::fabs( value ) );
    return (value < 0.0) ? -result : result;
}


double MathOperation::roundhalfeven(const double& value)
{
    const double& epsilon = EPSILON;

    if (value < 0.0) return -roundhalfeven(-value);

    double ipart;
    std::modf( value, &ipart );

    double temp = fabs(value -(ipart +0.5));
    if (temp < epsilon)
    {
        if (std::fmod( ipart, 2.0 ) < epsilon)
            return ipart;

        return ceil0( ipart +0.5 );
    }

    return roundhalfup0( value );
}


MathOperation::~MathOperation() {

}
