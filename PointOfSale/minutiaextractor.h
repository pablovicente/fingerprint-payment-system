#ifndef MINUTIAEXTRACTOR_H
#define MINUTIAEXTRACTOR_H

#include "math.h"
#include "algorithm"

#include "ConstantsFingerprint.h"
#include "mathoperation.h"
#include "minutia.h"
#include "angle.h"

/*!
 * \brief The MinutiaExtractor class Clase que recoge la funcionalidad encargada de realizar la extraccion de minucias de la imagen
 */

class MinutiaExtractor
{
public:
    /*!
     * \brief MinutiaExtractor Constructor vacio
     */
    MinutiaExtractor();
    /*!
     * \brief extractMinutia Metodo que realiza la extraccion de minucias sobre una huella dactilar
     * \return Vector con las minucias extraidads
     */
    std::vector<Minutia> extractMinutiae(cv::Mat& matrix, cv::Mat& orientationImage, cv::Mat& segment, int blockSize);
    /*!
     * \brief Show  Metodo que muestra las minucias sobre la imagen de la huella dactilar
     * \param features Vector de minucias
     * \param img cv::Mat sobre la que se muestran las minucias
     */
    void overlayMinutiae(std::vector<Minutia> features, cv::Mat & img);
    /*!
     * \brief compareFingerprintMinutiaes Metodo que muestra la compracion entre dos conjuntos de minucias
     * \param features  Vector de minucias
     * \param img   cv::Mat sobre la que se muestran las minucias
     * \param numberImage Imagen que se va a tratar
     */
    void compareFingerprintMinutiae(std::vector<Minutia> features, cv::Mat & img, int numberImage);
    /*!
     * \brief minutiae Vector en el que se van a almacenar minucias
     */
    std::vector<Minutia> minutiae;
private:
    /*!
     * \brief mathOp Objeto de la clase que contine las operaciones matematicas
     */
    MathOperation mathOp;

    std::vector<Minutia> filterBorderMinutiae(std::vector<Minutia> minutiaes, cv::Mat& oiMatrix, cv::Mat& segment, int blockSize);

    std::vector<Minutia> removeFalseMinutiae(std::vector<Minutia> noInTheBorder, cv::Mat& oiMatrix, int blockSize);
};

#endif // MINUTIAEXTRACTOR_H
