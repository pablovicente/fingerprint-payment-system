#ifndef KEYPAD_H
#define KEYPAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QDebug>
#include <wiringPi.h>           //WiringPi headers
#include <stdio.h>              //Needed for the printf function below

/*!
 * \brief The Keypad class Clase que encapsula la funcionalidad del manejo del teclado
 */
class Keypad : public QObject
{          
    Q_OBJECT
public:
    /*!
     * \brief Keypad Constructor que recibe el objeto padre como parametro
     * \param parent Padre de la instancia
     */
    explicit Keypad(QObject *parent = 0);
    /*!
     * \brief getKey Metodo que recupera la tecla que se pulse a continuacion
     * \return Valor de la tecla pulsada
     */
    char getKey(void);
    /*!
     * \brief reset Metodo que resetea los voltajes del teclado
     */
    void reset(void);       
    char current = 'G', previous = 'O';
private:
    /*!
     * \brief MATRIX Matriz que almacena los valores que van a tener asociadas las teclas
     */
    char MATRIX[4][4];
    /*!
     * \brief ROW Vector que indica los pines GPIO a los que se conectan las filas
     */
    int ROW[4];
    /*!
     * \brief COL Vector que indica los pines GPIO a los que se conectan las columnas
     */
    int COL[4];
};

#endif // KEYPAD_H
