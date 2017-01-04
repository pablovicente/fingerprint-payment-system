#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ConstantsFingerprint.h"

/*!
 * \brief The Frequency class Clase que recoge la funcionalidad encargada de realizar el calculo de la frecuencia de la imagen
 */

class Frequency
{
public:
    /*!
     * \brief Frequency Constructor vacio
     */
    Frequency();
    /*!
     * \brief calculateFrequencyBlock Metodo que va a realizar el calculo de la frecuencia de la imagen recibida
     * \param src cv::Mat que contiene la imagen de la que se va a calcular la frecuencia
     * \param oiMatrix cv::Mat que contiene la orientacion imagen de la que se va a calcular la frecuencia
     * \param blockSize Entero que indica el tamaño de bloque a usar en el cálculo de la frecuencia
     */
    void calculateFrequencyBlock(cv::Mat& src, cv::Mat& oiMatrix, int blockSize);
    /*!
     * \brief freqMatrix cv::Mat que contiene frecuencia de la imagen
     */
    cv::Mat freqMatrix;
};

#endif // FREQUENCY_H
