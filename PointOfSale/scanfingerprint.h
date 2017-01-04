#ifndef SCANFINGERPRINT_H
#define SCANFINGERPRINT_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/*!
 * \brief The ScanFingerprint class Clase encargada del proceso de lectura
 */
class ScanFingerprint
{
public:
    /*!
     * \brief ScanFingerprint Constructor vacio
     */
    ScanFingerprint();
    /*!
     * \brief scan Método encargado del proceso de lectura
     * \return cv::Mat que contine la imagen leida
     */
    cv::Mat scan(void);
};

#endif // SCANFINGERPRINT_H
