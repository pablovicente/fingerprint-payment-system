#ifndef ANGLE_H
#define ANGLE_H

#include <opencv2/opencv.hpp>

#include <opencv2/imgproc/imgproc.hpp>

/*!
 * \brief The Angle class Clase encargada del cálculo y transformación de ángulos
 */
class Angle
{
public:
    /*!
     * \brief Angle Constructor vacío
     */
    Angle();
    /*!
     * \brief computeAngleInRadians Método que calcula el angulo en radianes dado a partir de dos valores utilizando la arcotangente
     * \param dX Float en el eje x
     * \param dY Float en el eje y
     * \return Double que contiene el angulo en radianes
     */
    static double computeAngleInRadians(float dY, float dX);
    /*!
     * \brief toRadians Metodo que realiza la transformacion de un angulo de grados a radianes
     * \param deg Angulo en grados
     * \return Double que contiene el angulo en radianes
     */
    static double toRadians(float deg);
    /*!
     * \brief toDegrees Metodo que realiza la transformacion de un angulo de radianes a grados
     * \param rad Angulo en radianes
     * \return Double que contiene el angulo en grados
     */
    static double toDegrees(float rad);
    /*!
     * \brief differencePi
     * \param alpha
     * \param beta
     * \return
     */
    static double differencePi(double angleA, double angleB);
};

#endif // ANGLE_H
