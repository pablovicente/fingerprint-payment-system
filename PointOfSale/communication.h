#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>
#include <QObject>
#include <QByteArray>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDateTime>
#include <QFile>
#include <QUrlQuery>
#include <QEventLoop>
#include <QStringRef>

#include "myfingerprint.h"
#include "minutia.h"
#include "Constants.h"

/*!
 * \brief The Communication class Clase que encapsula la funcionalidad relativa a la comunicación con el servidor
 */

class Communication : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Communication Contructor que recibe como argumento el objeto padre
     * \param parent Objeto que va a ser el padre de la instancia
     */
    explicit Communication(QObject *parent = 0);
    /*!
     * \brief makePayment Metodo que realiza una transaccion del usuario
     * \param fingerprint Instancia de la huella dactilar con la que se va a realiza el pago
     * \param total Precio de la compra
     * \param currency Moneda empleada
     * \param venue Lugar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool makePayment(MyFingerprint &fingerprint, QString total, QString currency, QString venue);
    /*!
     * \brief validatePayment Metodo que realiza una transaccion del usuario
     * \param fingerprint Instancia de la huella dactilar con la que se va a realiza el pago
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool authenticateDevice(QString idDevice, QString password);

private:

   /*!
   * \brief manager Instancia de la clase encargada de manejar las comunicaciones a bajo nivel
   */
  QNetworkAccessManager *manager;
  /*!
   * \brief baseIP Cadena que indica la direccion IP utilizada en la conexion
   */
  QString baseIP;
  /*!
   * \brief protocol Cadena que indica el protocolo de comunicacion utilizado
   */
  QString protocol;
  /*!
   * \brief allowedCAs Lista que almacena los certificados de la autoridad certificadora utilizada en la conexion
   */
  QList<QSslCertificate> allowedCAs;
};

#endif // COMMUNICATION_H
