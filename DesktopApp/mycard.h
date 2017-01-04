#ifndef MYCARD_H
#define MYCARD_H

#include <QtCore>

/*!
 * \brief The MyCard class Clase del modelo correspondiente a las tarjeta bancarias
 */

class MyCard
{
public:
    /*!
     * \brief MyCard Constructor vacio
     */
    MyCard();
    /*!
     * \brief getCardNumber del numero de tarjeta
     * \return
     */
    QString getCardNumber() const;
    /*!
     * \brief setCardNumber Setter del numero de tarjeta
     * \param value
     */
    void setCardNumber(const QString &value);
    /*!
     * \brief getCardType del tipo de tarjeta
     * \return
     */
    QString getCardType() const;
    /*!
     * \brief setCardType Setter del tipo de tarjeta
     * \param value
     */
    void setCardType(const QString &value);    
    /*!
     * \brief getCvv del cvv de la tarjeta
     * \return
     */
    QString getCvv() const;
    /*!
     * \brief setCvv Setter del cvv de la tarjeta
     * \param value
     */
    void setCvv(const QString &value);
    /*!
     * \brief getShortCardNumber de los ultimos digitos de la tarjeta
     * \return
     */
    QString getShortCardNumber() const;
    /*!
     * \brief setShortCardNumber Setter de los ultimos digitos de la tarjeta
     * \param value
     */
    void setShortCardNumber(const QString &value);
    /*!
     * \brief getSelected del estado preferedo de la tarjeta
     * \return
     */
    bool getSelected() const;
    /*!
     * \brief setSelected Setter del estado preferedo de la tarjeta
     * \param value
     */
    void setSelected(bool value);
    /*!
     * \brief getExpirationMonth Getter del mes de expiracion de la tarjeta
     * \return
     */
    QString getExpirationMonth() const;
    /*!
     * \brief setExpirationMonth Setter del mes de expiracion de la tarjeta
     * \param value
     */
    void setExpirationMonth(const QString &value);
    /*!
     * \brief getExpirationYear Getter del año de expiracion de la tarjeta
     * \return
     */
    QString getExpirationYear() const;
    /*!
     * \brief setExpirationYear Setter del año de expiracion de la tarjeta
     * \param value
     */
    void setExpirationYear(const QString &value);
    /*!
     * \brief getIdCard Getter del identificador de la tarjeta
     * \return
     */
    QString getIdCard() const;
    /*!
     * \brief setIdCard Setter del identificador de la tarjeta
     * \param value
     */
    void setIdCard(const QString &value);

private:
    /*!
     * \brief cardNumber Numero de la tarjeta
     */
    QString cardNumber;
    /*!
     * \brief idCard Identificador de la tarjeta
     */
    QString idCard;
    /*!
     * \brief shortCardNumber Ultimos numeros de la tarjeta
     */
    QString shortCardNumber;
    /*!
     * \brief cardType Marca de la tarjeta bancaria
     */
    QString cardType;
    /*!
     * \brief expirationMonth Mes de expiratcion de la tarjeta
     */
    QString expirationMonth;
    /*!
     * \brief expirationYear Year de expiratcion de la tarjeta
     */
    QString expirationYear;
    /*!
     * \brief cvv Codigo cvv de la tarjeta
     */
    QString cvv;
    /*!
     * \brief selected Boolean que indica si la tarjeta es principal
     */
    bool selected;
};

#endif // MYCARD_H
