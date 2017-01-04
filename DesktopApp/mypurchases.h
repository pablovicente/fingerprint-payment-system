#ifndef MYPURCHASES_H
#define MYPURCHASES_H

#include <QtCore>

/*!
 * \brief The MyPurchases class Clase del modelo correspondiente a las transacciones
 */

class MyPurchases
{
public:

    /*!
     * \brief MyPurchases Contructor vacio
     */
    MyPurchases();
    /*!
     * \brief getCode Getter del codigo de transaccion
     * \return
     */
    QString getCode() const;
    /*!
     * \brief setCode Setter del codigo de transaccion
     * \param value
     */
    void setCode(const QString &value);
    /*!
     * \brief getCurrency Getter de la moneda
     * \return
     */
    QString getCurrency() const;
    /*!
     * \brief setCurrency Setter de la moneda
     * \param value
     */
    void setCurrency(const QString &value);
    /*!
     * \brief getVenue Getter del establecimiento
     * \return
     */
    QString getVenue() const;
    /*!
     * \brief setVenue Setter del establecimiento
     * \param value
     */
    void setVenue(const QString &value);
    /*!
     * \brief getDate Getter de la fecha
     * \return
     */
    QDate getDate() const;
    /*!
     * \brief setDate Setter de la fecha
     * \param value
     */
    void setDate(const QDate &value);
    /*!
     * \brief getCard Getter de la tarjeta
     * \return
     */
    QString getCard() const;
    /*!
     * \brief setCard Setter  de la tarjeta
     * \param value
     */
    void setCard(const QString &value);
    /*!
     * \brief getAmount Getter de la cantidad
     * \return
     */
    QString getAmount() const;
    /*!
     * \brief setAmount Setter de la cantidad
     * \param value
     */
    void setAmount(const QString &value);

private:
    /*!
     * \brief code Codigo de la transaccion
     */
    QString code;
    /*!
     * \brief amount Cantidad de la transaccion
     */
    QString amount;
    /*!
     * \brief currency Moneda de la transaccion
     */
    QString currency;
    /*!
     * \brief venue Establecimiento de la transaccion
     */
    QString venue;
    /*!
     * \brief date Fecha de la transaccion
     */
    QDate date;
    /*!
     * \brief card Tarjeta de la transaccion
     */
    QString card;
};

#endif // MYPURCHASES_H
