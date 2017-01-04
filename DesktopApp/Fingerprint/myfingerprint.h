#ifndef MYFINGERPRINT_H
#define MYFINGERPRINT_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "minutia.h"

enum Hand
{
    Left,Right, None
};

//left hand
enum Finger
{
    Pinkie, Ring, Middle, Index, Thumb
};

class MyFingerprint
{
public:
    MyFingerprint();
    std::vector<Minutia> minutiaes;
    Finger fingerType;
    Hand handType;

    void clearMinutiae(void);
};

#endif // MYFINGERPRINT_H

