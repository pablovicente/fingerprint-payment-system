#ifndef PAYMENTPROCESS_H
#define PAYMENTPROCESS_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QDebug>
#include <QFileInfo>
#include <QProcess>
#include <wiringPi.h>           //WiringPi headers

#include <screen.h>
#include <keypad.h>
#include <myfingerprint.h>
#include <communication.h>
#include <scanfingerprint.h>
#include <processfingerprint.h>

#define LCD_ROWS 2
#define LCD_COLS 16
#define MAX_TRIES 3


/*! \mainpage Terminal de pago
 *
 * Este documento recoge la documentación asocidada al
 * software del terminal de pago.
 *
 */

/*!
 * \brief The PaymentProcess class Clase que gestiona el proceso de pago
 */
class PaymentProcess : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief PaymentProcess Constructor que recibe como parametro el padre
     * \param parent Padre el objeto
     */
    explicit PaymentProcess(QObject *parent = 0);
    /*!
     * \brief init Metodo que inicia el proceso de pago
     */
    void init(void);
signals:

public slots:

};

#endif // PAYMENTPROCESS_H
