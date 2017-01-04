#ifndef THINNING_H
#define THINNING_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "ConstantsFingerprint.h"

typedef std::pair<int, int> Point;

/*!
 * \brief The Thinning class Clase que recoge la funcionalidad encargada de realizar el adelgazamiento de la imagen
 */
class Thinning
{
public:
    /*!
     * \brief Thinning Constructor vacio
     */
    Thinning();
    /*!
     * \brief thin Metdo encargado de realizar el adelgazamiento de la imagen recibida como parametro
     * \param thinMatrix cv::Mat que recoge la imagen que se va a adelgazar
     */
    void thin(cv::Mat& thinMatrix);
    /*!
     * \brief thinMatrix cv::Mat que recoge la imagen que se va a adelgazar
     */
    cv::Mat thinMatrix;
private:

};

#endif // THINNING_H
