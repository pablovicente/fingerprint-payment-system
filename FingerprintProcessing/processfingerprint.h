#ifndef PROCESSFINGERPRINT_H
#define PROCESSFINGERPRINT_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <boost/thread.hpp>

#include <QObject>
#include "ConstantsFingerprint.h"
#include "mathoperation.h"
#include "normalize.h"
#include "segmentation.h"
#include "orientation.h"
#include "frequency.h"
#include "filter.h"
#include "binarization.h"
#include "thinning.h"
#include "minutiaextractor.h"
#include "minutia.h"
#include "angle.h"
#include "matching.h"

enum ImageSource
{
    Scanner, File, NotKnown
};


/*!
 * \brief The ProcessFingerprint class Clase que recoge la funcionalidad encargada de encamsular el procesamiento de la imagen
 */
class ProcessFingerprint : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief ProcessFingerprint Contructor
     * \param parent Indica el padre de la clase para esa instancia
     */
    explicit ProcessFingerprint(QObject *parent = 0);
    /*!
     * \brief process Metodo que realiza el procesamiento de la imagen original calculando todas la imagenes intermedias
     * \param imagesNames Nombre de las imagenes a calcular
     * \param tam Tamaño deseado para las imagenes
     */
    void process(QStringList imagesNames, int tam);
    /*!
     * \brief obtainMinutiaeFromSourceImage Metodo que calcula las minucias de la imagen original
     * \param color cv::Mat que contiene la imagen original
     * \param tam Tamaño deseado para la imagen
     * \param minutiaes Vector en el que se van a almacenar las minucias
     * \param numberImage Orden de la imagen que se va a procesar
     */
    void obtainMinutiaeFromSourceImage(cv::Mat &color, int tam, std::vector<Minutia> &minutiaes, int numberImage, ImageSource source);
    /*!
     * \brief obtainMinutiaeFromSourceImageAsync
     * \param color
     * \param tam
     */
    void obtainMinutiaeFromSourceImageAsync(cv::Mat &color, int tam);
    /*!
     * \brief resize Metodo que recalcula el tamaño de la imagen
     * \param src cv::Mat que contiene la imagen original
     * \param tam  Tamaño deseado para la nueva imagen
     * \return cv::Mat que contiene la imagen con el nuevo tamaño
     */
    cv::Mat resize(cv::Mat &src, int tam);
    /*!
     * \brief toBlackAndWhite Metodo que transforma la imagen a escala de grises
     * \param src cv::Mat que contiene la imagen original
     * \return cv::Mat que contiene la imagen transformada
     */
    cv::Mat toBlackAndWhite(cv::Mat &src);
    /*!
     * \brief match Metodo calcla el porcentaje de coincidencia entre dos images
     * \param leftImage cv::Mat que contiene una de las imagenes
     * \param rightImagen cv::Mat que contiene la segunda imagen
     */
    void match(cv::Mat &leftImage ,cv::Mat &rightImage);
    /*!
     * \brief images Hash que contiene todas la imagenes calculadas durante el procesamiento
     */
    QHash<QString,cv::Mat> images;
    std::vector<Minutia> minutiaeExtracted;
signals:
    /*!
     * \brief finishedProcessFingerprint Señal emitida cuando termina el procesamiento
     */
    void finishedProcessFingerprint(void );
    /*!
     * \brief progressValueProcessFingerprint Señal emitida duarnte el procesamiento
     * \param message Mensaje emitido
     */
    void progressValueProcessFingerprint(QString message);
    /*!
     * \brief finishedFingerprintComparison Señal emitida cuando termina el proceso de compracion
     */
    void finishedFingerprintComparison(void );
    /*!
     * \brief progressValueCompareFingerprints Señal emitida duarnte el proceso de comparacion
     * \param message Mensaje emitido
     */
    void progressValueCompareFingerprints(QString message);
};

#endif // PROCESSFINGERPRINT_H
