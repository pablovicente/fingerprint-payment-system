#include "angle.h"
#include "math.h"



Angle::Angle()
{
}

double Angle::computeAngleInRadians(float dY, float dX)
{    
    double angle = atan2(dY,dX);

    if(angle >= 0)  {
        angle = M_PI - angle;
    }
    else    {
        angle = fabs(angle) - M_PI; //Poner el signo mas para tener angulos positivos
    }

    return angle;
}

double Angle::toRadians(float deg)
{
    return deg * M_PI / 180;
}

double Angle::toDegrees(float rad)
{
    return rad * 180 / M_PI;
}

double Angle::differencePi(double angleA, double angleB)
{
    double diff = fabs(angleB - angleA);
    return fmin(diff, 2 * M_PI - diff);
}
