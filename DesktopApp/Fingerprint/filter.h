#ifndef FILTER_H
#define FILTER_H

#define SOBEL_SIZE 3

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "ConstantsFingerprint.h"

/*!
 * \brief The Filter class Clase que recoge la funcionalidad encargada de realizar los distintos filtros sobre la imagen
 */
class Filter
{
public:
    /*!
     * \brief Filter Constructor vacio
     */
    Filter();
    /*!
     * \brief applyGaborFilter Metodo utilizado para la aplicación de los filtros de Gabor sobre una imagen
     * \param src cv::Mat que contiene la imagen original que se va a filtrar
     * \param oiMatrix cv::Mat que contiene la orientacion de la imagen que se va a filtrar
     * \param freqMatrix cv::Mat que contiene la frecuencia de la imagen que se va a filtrar
     * \param gaborMatrix cv::Mat que va a contener la imagen filtrada
     * \param blockSize cv:: Tamaño de bloque que se va a usar en el proceso de filtrado
     */
    void applyGaborFilter(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& freqMatrix, cv::Mat& gaborMatrix, int blockSize);
    /*!
     * \brief applyGaborFilterToChunk Metodo utilizado para la aplicación de los filtros de Gabor sobre una imagen
     * \param src cv::Mat que contiene la imagen original que se va a filtrar
     * \param oiMatrix cv::Mat que contiene la orientacion de la imagen que se va a filtrar
     * \param freqMatrix cv::Mat que contiene la frecuencia de la imagen que se va a filtrar
     * \param gaborMatrix cv::Mat que va a contener la imagen filtrada
     * \param min
     * \param max
     * \param blockSize cv:: Tamaño de bloque que se va a usar en el proceso de filtrado
     */
    void applyGaborFilterToChunk(cv::Mat& src, cv::Mat& oiMatrix, cv::Mat& freqMatrix, cv::Mat& gaborMatrix, int min, int max, int blockSize);
    /*!
     * \brief applySobelFilterX
     * \param src cv::Mat que contiene la imagen original que se va a filtrar
     * \return cv:Mat que va a contener la imagen filtrada
     */
    cv::Mat applySobelFilterX(cv::Mat& src);
    /*!
     * \brief applySobelFilterY
     * \param src cv::Mat que contiene la imagen original que se va a filtrar
     * \return cv:Mat que va a contener la imagen filtrada
     */
    cv::Mat applySobelFilterY(cv::Mat& src);
};

#endif // FILTER_H
