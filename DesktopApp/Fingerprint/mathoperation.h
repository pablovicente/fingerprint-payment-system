#ifndef MATHOPERATION_H
#define MATHOPERATION_H

#include <opencv2/opencv.hpp>
#include <math.h>
#include "ConstantsFingerprint.h"

/*!
 * \brief The MathOperation class Clase en la que se recogen las funciones matematicas necesitadas por el modulo
 */
class MathOperation
{
public:
    /*!
     * \brief MathOperation Constructor vacio
     */
    MathOperation();
    /*!
     * \brief MathOperation Contructor que recibe como argumento el numero de elementos del vector de elementos de la clase
     * \param elements Numero de elementos que va a tener el vector utilizado para realizar los calculos
     */
    MathOperation(int elements);
    /*!
     * \brief MathOperation Contructor que recibe como argumento el numero de elementos del vector de elementos de la clase y la matrix de la image que se va a almacenar en el vector
     * \param elements Numero de elementos que va a tener el vector utilizado para realizar los calculos
     * \param mat cv::Mat que contiene los valores de la imagen tratados
     */
    MathOperation(int elements, cv::Mat& mat);
    ~MathOperation();
    /*!
     * \brief max Entero que almacena el numero de elementos
     */
    int max;
    /*!
     * \brief values Vector que almacena los valores de la matriz sobre la que se van a realizar los calculos
     */
    std::vector<double> values;   
    /*!
     * \brief mean Double que almacena el valor de la media para calculos internos
     */
    double mean;
    /*!
     * \brief CalculateMean Metodo que calcula la media del vector de valores de la clase
     * \return
     */
    double CalculateMean();
    /*!
     * \brief CalculateVariane Metodo que calcula la varianza del vector de valores de la clase
     * \return
     */
    double CalculateVariane();       
    /*!
     * \brief GetStandardDeviation Metodo que calcula la desviación tipica del vector de valores de la clase
     * \return
     */
    double GetStandardDeviation();
    /*!
     * \brief ceil0 Metodo que realiza el redondeo al alza y cambiando el signo
     * \param value Valor sobre el que se realiza el calculo
     * \return Valor calculado
     */
    double ceil0( const double& value );
    /*!
     * \brief roundhalfup Metodo que realiza el redondeo al alza sumandole 0.5
     * \param value Valor sobre el que se realiza el calculo
     * \return Valor calculado
     */
    double roundhalfup( const double& value );
    /*!
     * \brief roundhalfup0 Metodo que realiza el redondeo al alza sumandole 0.5 y cambiando el signo
     * \param value Valor sobre el que se realiza el calculo
     * \return Valor calculado
     */
    double roundhalfup0( const double& value );
    /*!
     * \brief roundhalfeven Metodo que realiza el redondeo del banquero
     * \param value Valor sobre el que se realiza el calculo
     * \return Valor calculado
     */
    double roundhalfeven(const double& value);
};

#endif // MATHOPERATION_H
