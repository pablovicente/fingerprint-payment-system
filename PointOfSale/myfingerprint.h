#ifndef MYFINGERPRINT_H
#define MYFINGERPRINT_H

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "minutia.h"

enum Finger
{
    Pinkie, Ring, Middle, Index, Thumg
};

/*!
 * \brief The MyFingerprint class Clase del modelo que hace referencia las huellas
 */

class MyFingerprint
{
public:
    /*!
     * \brief MyFingerprint Contructor vacio
     */
    MyFingerprint();
    /*!
     * \brief minutiaes Vector que almacena el conjunto de minucias de la huella
     */
    std::vector<Minutia> minutiaes;
    /*!
     * \brief type Hace referencia al dedo elegido
     */
    Finger type;
};

#endif // MYFINGERPRINT_H

