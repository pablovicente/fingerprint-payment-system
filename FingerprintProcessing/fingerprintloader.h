#ifndef FINGERPRINTLOADER_H
#define FINGERPRINTLOADER_H

#include <QWidget>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <libfprint/fprint.h>
#include <QFileDialog>
#include <QMessageBox>
#include "ConstantsFingerprint.h"

/*!
 * \brief The FingerprintLoader class Clase encargada de la carga de las imagenes de las huellas dactilares
 */
class FingerprintLoader : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief FingerprintLoader Constructor
     * \param parent Padre de la clase
     */
    explicit FingerprintLoader(QWidget *parent = 0);
    /*!
     * \brief loadFromFile Metodo que se encarga de cargar la huella dactilar desde un archivo
     * \return  cv::Mat que contiene la imagen leida
     */
    cv::Mat loadFromFile();
    /*!
     * \brief loadFromScanner Metodo que se encarga de cargar la huella dactilar desde el escaner
     * \return cv::Mat que contiene la imagen leida
     */
    cv::Mat loadFromScanner();


};

#endif // FINGERPRINTLOADER_H

