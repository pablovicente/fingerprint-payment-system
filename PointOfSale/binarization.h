#ifndef BINARIZAR_H
#define BINARIZAR_H

#include <opencv2/opencv.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include "angle.h"
#include "ConstantsFingerprint.h"

/*!
 * \brief The Binarization class Clase que recoge la funcionalidad encargada de realizar la binarizacion de la imagen
 */
class Binarization
{
public:
    /*!
     * \brief Binarization
     */
    Binarization();
    /*!
     * \brief Binarization
     * \param h Entero que especifica el número de columnas del objeto cv::Mat que va a contoner la imagen binarizada
     * \param w Entero que especifica el número de columnas del objeto cv::Mat que va a contoner la imagen binarizada
     */
    Binarization(int h, int w);
    /*!
     * \brief binarize
     * \param src cv::Mat que contiene la imagen original que se va a binarizar
     * \param oiMatrix cv::Mat que contiene la orientacion de la imagen que se va a binarizar
     * \param segmentedMatrix cv::Mat que contiene la mascara de segmentación de la imagen normalizada
     * \param threshold Entero que indica el valor threshold utilizado para realizar la binarizacion
     * \param blockSize Entero que indica el tamaño del bloque utilizado en la orientacion
     */
    void binarize(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& segmentedMatrix, int threshold, int blockSize);
    /*!
     * \brief binMatrix cv::Mat que contiene la imagen binarizada
     */
    cv::Mat binMatrix;
};

#endif // BINARIZAR_H
