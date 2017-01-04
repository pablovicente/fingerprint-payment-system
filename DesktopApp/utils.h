#ifndef UTILS_H
#define UTILS_H

#include <QtCore>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>

using namespace std;
/*!
 * \brief The Utils class Clase que recoge metodos de distintas utilidades
 */
class Utils
{
public:
    /*!
     * \brief Utils Constructor vacio
     */
    Utils();
    /*!
     * \brief validateEmail Metodo que verifica el email recibido como parametro
     * \param email Email a comprobar
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool validateEmail(QString email);
    /*!
     * \brief validateTextField Metodo que verifica que el campo de texto no sea vacio
     * \param text Cadena de texto a comprobar
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool validateTextField(QString text);
    /*!
     * \brief comparePassword Metodo que comprueba que las dos contraseñas sean iguales
     * \param pass1 Contraseña número 1
     * \param pass2 Contraseña número 2
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool comparePassword(QString pass1, QString pass2);
    /*!
     * \brief isOver18 Metodo que valida la edad del usuario
     * \param birthdate Fecha de cumpleaños a comprobar
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool isOver18(QDate birthdate);
    /*!
     * \brief isValidDate Metodo que comprueba que la fecha sea posterior a hoy
     * \param date Fecha a comprobar
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool isValidDate(QDate date);
    /*!
     * \brief hasExpired Metodo que comprueba si una tarjeta bancaria a caducado
     * \param date Fecha a comprobar
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool hasExpired(QDate date);
    /*!
     * \brief verifyID Metodo que comprueba que el identificador tiene el formanto correcto del DNI
     * \param id Numero de identificacion del usuario
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool verifyID(QString id);
    /*!
     * \brief luhn Metodo que verifica que el numero de la tarjeta de credito sea correcto
     * \param id Numero de identificacion del usuario
     * \return Boolean que indica el resultado positivo o negativo de la operacion
     */
    bool luhn(const string& id);
    /*!
     * \brief parseCreditCard Metodo que extrae los numeros de la tarjeta del formato XXXX-XXXX-XXXX-XXXX
     * \param card Cadena con la tarjeta bancaria
     * \return Cadena con el numero de tarjeta parseado
     */
    QString parseCreditCard(QString card);
    /*!
     * \brief extractLastCardDigits Metodo que extrae los ultimos cuatro digitos de la tarjeta bancaria
     * \param card Cadena con la tarjeta bancaria
     * \return Cadena con los cuatro digitos finales de la tarjeta
     */
    QString extractLastCardDigits(QString card);    

private:
    /*!
     * \brief idLetters Secuencia valda de las letras del DNI
     */
    QStringList idLetters;
    /*!
     * \brief getCorrespondingLetter Metodo que calcula la letra que corresponde al numero de id introducido
     * \param id Numero de identificacion del usuario
     * \return Cadena con la letra que corresponde al DNI
     */
    QString getCorrespondingLetter(QString id);
};

#endif // UTILS_H
