#ifndef MINUTIA_H
#define MINUTIA_H

/*!
 * \brief The MinutiaType enum Enumeracion que recoge los posible tipos de minucias
 */

enum MinutiaType
{
    Unknown, End, Bifurcation
};

/*!
 * \brief The Minutia class Clase que va a contener las caracteristicas de la minucias
 */
class Minutia
{
public:
    /*!
     * \brief Minutia Constructor vacio
     */
    Minutia();
    /*!
     * \brief Minutia Contructor con argumentos para crear los objetos tipo minucia
     * \param an Double que indica el angulo de la minucia
     * \param x_pos Entero que indica la posicion de la minucia en el eje x
     * \param y_pos Entero que indica la posicion de la minucia en el eje y
     * \param t Tipo de minucia
     */
    Minutia(double an, int x_pos, int y_pos, MinutiaType t);
    /*!
     * \brief Minutia Contructor con argumentos para crear los objetos tipo minucia
     * \param an Double que indica el angulo de la minucia
     * \param x_pos Entero que indica la posicion de la minucia en el eje x
     * \param y_pos Entero que indica la posicion de la minucia en el eje y
     */
    Minutia(double an, int x_pos, int y_pos);
    /*!
     * \brief angle Double que almacena la orientacion de la minucia
     */
    float angle;
    /*!
     * \brief x Entero que almacena la posicion de la minucia en el eje x
     */
    float x;
    /*!
     * \brief y Entero que almacena la posicion de la minucia en el eje y
     */
    float y;
    /*!
     * \brief type Valor que indica el tipo de minucia
     */
    MinutiaType type;
};

#endif // MINUTIA_H
