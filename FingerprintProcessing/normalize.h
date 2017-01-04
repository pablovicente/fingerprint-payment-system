#ifndef NORMALIZE_H
#define NORMALIZE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ConstantsFingerprint.h"
#include "mathoperation.h"

/*!
 * \brief The Normalize class Clase que recoge la funcionalidad encargada de realizar la normalizacion de la imagen
 */
class Normalize
{
public:
    /*!
     * \brief Normalize Contructor vacio
     */
    Normalize();
    /*!
     * \brief normalizacion Metodo que realiza el calculo de la normalizacion de la imagen recibida como parametro
     * \param src cv::Mat de entrada
     */
    void normalizacion(cv::Mat& src);
    /*!
     * \brief normalizacionMask Metodo que calcula la mascara de normalizacion a partir de la varianza
     * \param src cv::Mat de entrada
     */
    void normalizacionMask(cv::Mat& src);
};

#endif // NORMALIZAR_H
