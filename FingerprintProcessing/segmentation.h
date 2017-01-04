#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "mathoperation.h"
#include <QDebug>
#include <math.h>
#include "ConstantsFingerprint.h"

/*!
 * \brief The Segmentation class Clase que recoge la funcionalidad encargada de realizar la segmentacion de la imagen
 */
class Segmentation
{
public:
    /*!
     * \brief Segmentation Constructor vacio
     */
    Segmentation();
    /*!
     * \brief segmentOrientationImage Metodo que calcula la mascara de segmentacion de la matriz de orientacion
     * \param src cv::Mat que contiene la imagen original
     * \param orientation cv::Mat que contiene la orientacion de la imagen
     */
    void segmentOrientationImage(cv::Mat& src, cv::Mat& orientation, int blockSize);

    /*!
     * \brief Segmentation::recoverLostBlocks
     * \param previousOi
     * \param newOi
     */
    void recoverLostBlocks(cv::Mat& previousOi, cv::Mat& newOi);
    /*!
     * \brief enhanceOrientationImage Metodo que mejora la mascara de segmentacion de la matriz de orientacion
     * \param oi cv::Mat que contiene la orientacion de la imagen
     * \param blockSize Tamaño del bloque
     */
    void enhanceOrientationImage(cv::Mat& newOi);
    /*!
     * \brief segmentSourceImage Metodo que calcula la mascara de segmentacion de la imagen original
     * \param src cv::Mat que contiene la imagen original
     * \param orientation cv::Mat que contiene la orientacion de la imagen
     * \param blockSize Tamaño del bloque
     * \return cv::Mat que contiene la mascara
     */
    cv::Mat segmentSourceImage(cv::Mat& src, cv::Mat& orientation, int blockSize);

};

#endif // Segmentation_H
