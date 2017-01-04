#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <opencv2/opencv.hpp>

#include <opencv2/imgproc/imgproc.hpp>
#include <QtCore>
#include "filter.h"
#include "ConstantsFingerprint.h"

/*!
 * \brief The Orientation class Clase que recoge la funcionalidad encargada de realizar la orientacion de la imagen
 */
class Orientation
{
public:
    /*!
     * \brief Orientation Constructor vacio
     */
    Orientation();
    /*!
     * \brief calculateOrientation Metodo encargado de calculo de la orientacion por bloques
     * \param src cv::Mat que contiene la imagen sobre la que se va a calcular la orientacion
     */
    void calculateOrientation(cv::Mat& src, int blockSize);
    /*!
     * \brief overlayOrientation Metodo que dibuja la orientacion sobre la matriz original
     * \param src cv::Mat que contiene la imagen original
     * \param oi cv::Mat que contine la orientacion de la imagen
     * \param blockSize Entero que almacena el tamaño del bloque de la orientacion
     */
    void overlayOrientation(cv::Mat& src, cv::Mat& oi, int blockSize);
    /*!
     * \brief overlayOrientationPixel Metodo que dibuja la orientacion sobre la matriz original
     * \param src cv::Mat que contiene la imagen original
     * \param oi cv::Mat que contine la orientacion de la imagen
     * \param blockSize Entero que almacena el tamaño del bloque de la orientacion
     */
    void overlayOrientationPixel(cv::Mat& src, cv::Mat& oi, int blockSize);
    /*!
     * \brief overlayOrientationBlock Metodo que dibuja la orientacion sobre la matriz original
     * \param src cv::Mat que contiene la imagen original
     * \param oi cv::Mat que contine la orientacion de la imagen
     * \param blockSize Entero que almacena el tamaño del bloque de la orientacion
     */
    void overlayOrientationBlock(cv::Mat& src, cv::Mat& oi, int blockSize);
    /*!
     * \brief calculateOrientationPixel Metodo encargado de calculo de la orientacion por pixeles
     * \param src cv::Mat que contiene la imagen sobre la que se va a calcular la orientacion
     * \param blockSize Entero que almacena el tamaño del bloque de la orientacion
     */
    void calculateOrientationPixel(cv::Mat& src, int blockSize);
    /*!
     * \brief calculateOrientationBlock Metodo encargado de calculo de la orientacion por bloques menos eficiente
     * \param src cv::Mat que contiene la imagen sobre la que se va a calcular la orientacion
     * \param blockSize Entero que almacena el tamaño del bloque de la orientacion
     */
    void calculateOrientationBlock(cv::Mat& src, int blockSize);
    /*!
     * \brief oiMatrix cv::Mat que almacena la orientacion calculada
     */
    cv::Mat oiMatrix;
    /*!
     * \brief oiMatrixPixel cv::Mat que almacena la orientacion calculada mediante el metodo de pixel
     */
    cv::Mat oiMatrixPixel;
    /*!
     * \brief oiMatrixBlock cv::Mat que almacena la orientacion calculada mediante el metodo de bloque menos eficiente
     */
    cv::Mat oiMatrixBlock;
};

#endif // Orientation_H
