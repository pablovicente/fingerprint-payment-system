#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QJsonDocument>
#include <QJsonObject>

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

#include "myuser.h"
#include "mycard.h"
#include "mypurchases.h"
#include "Fingerprint/myfingerprint.h"
#include "Fingerprint/minutia.h"
#include "Constants.h"

enum PurchasesInfo
{
    Basic, Simple, Detail
};

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
     * \brief registerUser Metodo que realiza el registro del usuario
     * \param user Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool registerUser(MyUser user);
    /*!
     * \brief insertPhone Metodo que realiza la insercion de un telefono del usuario
     * \param user Instacia del usuario
     * \param phone Numero telefonico a guardar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool insertPhone(MyUser &user, QString phone);
    /*!
     * \brief insertCard Metodo que realiza la insercion de una tarjeta bancaria del usuario
     * \param user Instacia del usuario
     * \param card Instacia de la tarjeta bancaria a almacenar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool insertCard(MyUser user, MyCard card);
    /*!
     * \brief login Metodo que realiza el login del usuario
     * \param user Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool login(MyUser &user);
    /*!
     * \brief logout Metodo que cierra la sesion del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool logout();
    /*!
     * \brief searchUser Metodo que comprueba si los datos indicados existen para otro usuario
     * \param user Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool searchUser(MyUser user);
    /*!
     * \brief forgottenPassword Metodo que permite recuperar la contraseña
     * \param user Instancia de usuario a modificar
     * \param fingerprint Instancia de la huella dactilar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool forgottenPassword(MyUser &user, MyFingerprint &fingerprint);
    /*!
     * \brief selectPreferredCard Metodo que selecciona la tarjeta preferida del usuario
     * \param card Instancia de la tarjeta bancaria seleccionada como favorita
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool selectPreferredCard(MyCard card);    
    /*!
     * \brief retrievePurchaes Metodo que devuelve las transacciones de un usuario
     * \param user Instancia de usuario
     * \param initial Fecha inicial
     * \param final Fecha final
     * \param info Nivel de detalle
     * \param page Pagina
     * \return Hash que contiene el numero de paginas y la pagina devuelta
     */
    QHash<int,int> retrievePurchaes(MyUser &user,QDate initial,QDate final, PurchasesInfo info, int page);
    /*!
     * \brief retrieveCards Metodo que recupera las tarjetas bancarias del usuario
     * \param user Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool retrieveCards(MyUser &user);
    /*!
     * \brief retrievePhones Metodo que recupera los telefonos del usuario
     * \param user Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool retrievePhones(MyUser &user);
    /*!
     * \brief updateEmail Metodo que actualiza el email del usuario
     * \param user Instacia del usuario
     * \param newEmail Nuevo email que se va a almacenar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool updateEmail(MyUser &user, QString newEmail);
    /*!
     * \brief updatePhone Metodo que actualiza un telefono del usuario
     * \param user Instacia del usuario
     * \param oldPhone Telefono que se va a eliminar
     * \param newPhone Telefono que se va a guardar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool updatePhone(MyUser &user, QString oldPhone, QString newPhone);
    /*!
     * \brief updateName Metodo que actualiza el nombre del usuario
     * \param user Instacia del usuario
     * \param newName Nuevo nombre del usuario con el que se va actualizar su cuenta
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool updateName(MyUser &user, QString newName);
    /*!
     * \brief updateSurname Metodo que actualiza el apellido del usuario
     * \param user Instacia del usuario
     * \param newSurname Nuevos apellidos del usuario con el que se va actualizar su cuenta
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool updateSurname(MyUser &user, QString newSurname);
    /*!
     * \brief updateAddress Metodo que actualiza la direccion del usuario
     * \param user Instacia del usuario
     * \param newAddress Nuevo direccion del usuario con el que se va actualizar su cuenta
     * \param newPostcode Nuevo codigo postal del usuario con el que se va actualizar su cuenta
     * \param newCity Nueva ciudad del usuario con el que se va actualizar su cuenta
     * \param newCountry Nuevo pais del usuario con el que se va actualizar su cuenta
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool updateAddress(MyUser &user, QString newAddress, QString newPostcode, QString newCity, QString newCountry);
    /*!
     * \brief updatePassword Metodo que actualiza la contraseña del usuario
     * \param user Instacia del usuario
     * \param newPassword
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool updatePassword(MyUser &user, QString newPassword);
    /*!
     * \brief saveFingerprint Metodo que almacena una huella dactilar del usuario
     * \param user Instacia del usuario
     * \param fingerprint Instancia de la huella dactilar que se va a almacenar
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool saveFingerprint(MyUser &user, MyFingerprint &fingerprint);
    /*!
     * \brief validatePayment Metodo que realiza una transaccion del usuario
     * \param fingerprint Instancia de la huella dactilar con la que se va a realiza el pago
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool validatePayment(MyFingerprint &fingerprint);
    /*!
     * \brief deletePhone Metodo que elimina un telefono del usuario
     * \param user Instacia del usuario
     * \param oldPhone Telefono que se va a eliminar de la cuenta del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool deletePhone(MyUser &user, QString oldPhone);
    /*!
     * \brief deleteCard Metodo que elimina una tarjeta bancaria del usuario
     * \param user Instacia del usuario
     * \param card Instancia de la tarjeta bancaria que se va a eliminar de la cuenta del usuario
     * \param selectedCard Instancia de la nueva tarjeta bancaria elegida como favorita
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool deleteCard(MyUser &user, MyCard card,  MyCard selectedCard);
    /*!
     * \brief deleteAccount Metodo que elimina la cuenta del usuario
     * \param user Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool deleteAccount(MyUser &user);
    /*!
     * \brief blockAccount  Metodo que bloquea la cuenta del usuario
     * \param user  Instacia del usuario
     * \return Boolean que indica el estado de exito o fracaso de la peticion
     */
    bool blockAccount(MyUser &user);
    /*!
     * \brief authenticateDevice
     * \param idDevice
     * \param password
     * \return
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


