#ifndef MATCHING_H
#define MATCHING_H

#include "minutia.h"
#include <opencv2/opencv.hpp>
#include "ConstantsFingerprint.h"

/*!
 * \brief The Matching class Clase que recoge la funcionalidad encargada de realizar el proceso de matchin
 */
class Matching
{
public:
    /*!
     * \brief Matching Contructor vacio
     */
    Matching();
    /*!
     * \brief match Metodo que va a realizar el calculo del porcentaje de coincidencia entre dos conjutos de minucias
     * \param M1 std::vector que contiene el primer conjunto de minucias a comparar
     * \param M2 std::vector que contiene el segundo conjunto de minucias a comparar
     * \return Float que indica el porcetanje de coincidencia
     */
    float match(std::vector<Minutia> M1, std::vector<Minutia> M2);
};

#endif // MATCHING_H
