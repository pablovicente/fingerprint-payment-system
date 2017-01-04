#ifndef SCREEN_H
#define SCREEN_H

#include <QtCore>
#include <QDebug>
#include <QThread>
#include <wiringPi.h>           //WiringPi headers
#include <lcd.h>                //LCD headers from WiringPi
#include <stdio.h>              //Needed for the printf function below

//Pin numbers below are the WiringPi pin numbers

#define LCD_RS  29               //Register select pin
#define LCD_E   28               //Enable Pin
#define LCD_D4  25               //Data pin 4
#define LCD_D5  24               //Data pin 5
#define LCD_D6  23               //Data pin 6
#define LCD_D7  22               //Data pin 7

/*!
 * \brief The Screen class Clase que recoge la funcionalidad asociada al manejo de las pantallas
 */
class Screen : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Screen Constructor que recibe el objeto padre como parametro
     * \param parent Padre de la instancia
     */
    explicit Screen(QObject *parent = 0);
    /*!
     * \brief displayText Metodo que muestra el texto indicado en la pantalla
     * \param line  Entero que indica la linea en la que se va a mostrar el mensaje
     * \param message Cadena que se va a mostrar
     */
    void displayText(int line, QString message);
    /*!
     * \brief scrollMessage Metodo que muestra el texto indicado de manera deslizante en la pantalla
     * \param line Entero que indica la linea en la que se va a mostrar el mensaje
     * \param width Tamaño del mensaje
     * \param message Cadena que se va a mostrar
     */
    void scrollMessage (int line, int width, QString message);
    /*!
     * \brief waitForEnter Metodo que muesta el mensaje de pulse una tecla y se queda esperando hasta que sea pulsada
     */
    void waitForEnter(void);
    /*!
     * \brief clearScreen Metodo que elimina los mensajes de la pantalla
     */
    void clearScreen(void);
    /*!
     * \brief doSetup Metodo que establece la configuracion del hilo en el que se van a mostrar los mensajes deslizantes
     * \param thread
     */
    void doSetup(QThread &thread);
    /*!
     * \brief pause Metodo que detiene el mensaje deslizante
     */
    void pause(void);
    /*!
     * \brief resume Metodo que reanuda el mensaje deslizante
     */
    void resume(void);
    /*!
     * \brief sync Mutex que bloquea el hilo
     */
    QMutex sync;
    /*!
     * \brief scrollingString Mensaje deslizante que se va a mostrar en la pantalla
     */
    QString scrollingString;    
private:
    /*!
     * \brief lcdHandler Manejador de la pantalla LCD
     */
    int lcdHandler;
    /*!
     * \brief position Posicion que indica las lineas de la pantalla
     */
    int position[2];
    /*!
     * \brief timer Timer que indica la velocidad a la que se muestra el mensaje deslizante
     */
    unsigned int timer;   //timer                      
    /*!
     * \brief stop Boolean que indica si el mensaje deslizante se encuentra detenido
     */
    bool stop;
public slots:
    /*!
     * \brief doWork Slot creado en un hilo que activa el metodo que muestra el mensaje deslizante
     */
    void doWork();
};

#endif // SCREEN_H

