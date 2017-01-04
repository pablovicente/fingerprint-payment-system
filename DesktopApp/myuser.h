#ifndef MYUSER_H
#define MYUSER_H

#include <QtCore>
#include <mycard.h>
#include <mypurchases.h>
#include <Fingerprint/myfingerprint.h>

/*!
 * \brief The Gender enum Enumeracion que indica el genero del usuario
 */
enum Gender
{
    Male, Female, NotSetted
};
/*!
 * \brief The MyUser class Clase del modelo correspondiente al usuario
 */
class MyUser
{
public:
    /*!
     * \brief MyUser Constructor vacio
     */
    MyUser();
    /*!
     * \brief getName Getter del nombre
     * \return
     */
    QString getName() const;
    /*!
     * \brief setName Setter del nombre
     * \param value
     */
    void setName(const QString &value);
    /*!
     * \brief getCountry del pais
     * \return
     */
    QString getCountry() const;
    /*!
     * \brief setCountry Setter del pais
     * \param value
     */
    void setCountry(const QString &value);
    /*!
     * \brief getEmail Getter del email
     * \return
     */
    QString getEmail() const;
    /*!
     * \brief setEmail Setter del email
     * \param value
     */
    void setEmail(const QString &value);
    /*!
     * \brief getStreet  Getter de la calle
     * \return
     */
    QString getStreet() const;
    /*!
     * \brief setStreet Setter de la calle
     * \param value
     */
    void setStreet(const QString &value);
    /*!
     * \brief getCity  Getter de la ciudad
     * \return
     */
    QString getCity() const;
    /*!
     * \brief setCity Setter de la ciudad
     * \param value
     */
    void setCity(const QString &value);
    /*!
     * \brief getPassword  Getter de la contraseña
     * \return
     */
    QString getPassword() const;
    /*!
     * \brief setPassword Setter de la contraseña
     * \param value
     */
    void setPassword(const QString &value);
    /*!
     * \brief getId  Getter del id
     * \return
     */
    QString getId() const;
    /*!
     * \brief setId Setter del id
     * \param value
     */
    void setId(const QString &value);
    /*!
     * \brief getSurname Getter del apellido
     * \return
     */
    QString getSurname() const;
    /*!
     * \brief setSurname Setter del apellido
     * \param value
     */
    void setSurname(const QString &value);
    /*!
     * \brief getPhones Getter de los telefonos
     * \return
     */
    QStringList getPhones() const;
    /*!
     * \brief setPhones Setter de los telefonos
     * \param value
     */
    void setPhones(const QStringList &value);
    /*!
     * \brief getPostcode Getter del codigo postal
     * \return
     */
    QString getPostcode() const;
    /*!
     * \brief setPostcode Setter del codigo postal
     * \param value
     */
    void setPostcode(const QString &value);
    /*!
     * \brief getCards Getter de las tarjetas bancarias
     * \return
     */
    QList<MyCard> getCards() const;
    /*!
     * \brief setCards Setter de las tarjetas bancarias
     * \param value
     */
    void setCards(const QList<MyCard> &value);
    /*!
     * \brief getFingerprints Getter de las huellas dactilares
     * \return
     */
    QList<MyFingerprint> getFingerprints() const;
    /*!
     * \brief setFingerprints Setter de las huellas dactilares
     * \param value
     */
    void setFingerprints(const QList<MyFingerprint> &value);
    /*!
     * \brief getBirthday Getter del cumpleaños
     * \return
     */
    QDate getBirthday() const;
    /*!
     * \brief setBirthday Setter del cumpleaños
     * \param value
     */
    void setBirthday(const QDate &value);      
    /*!
     * \brief getGender Getter del genero
     * \return
     */
    Gender getGender() const;
    /*!
     * \brief setGender Setter del genero
     * \param value
     */
    void setGender(const Gender &value);

    QList<MyPurchases> getPurchases() const;
    void setPurchases(const QList<MyPurchases> &value);

    void clearPhones(void);
    void clearCards(void);
    void clearFingerprints(void);
    void clearPurchases(void);
    void clearUser(void);
    bool getAccountBlocked() const;
    void setAccountBlocked(bool value);

private:
    /*!
     * \brief id Identificador del usuario
     */
    QString id;
    /*!
     * \brief name  Nombre del usuario
     */
    QString name;
    /*!
     * \brief surname Apellidos del usuario
     */
    QString surname;
    /*!
     * \brief email Email del usuario
     */
    QString email;
    /*!
     * \brief password Contraseña del usuario
     */
    QString password;
    /*!
     * \brief street Calle del usuario
     */
    QString street;
    /*!
     * \brief city Ciudad del usuario
     */
    QString city;
    /*!
     * \brief postcode Codigo postal del usuario
     */
    QString postcode;
    /*!
     * \brief country Pais del usuario
     */
    QString country;
    /*!
     * \brief gender Genero del usuario
     */
    Gender gender;
    /*!
     * \brief birthday Fecha de cumpleaños del usuario
     */
    QDate birthday;
    /*!
     * \brief accountBlocked
     */
    bool accountBlocked;
    /*!
     * \brief phones Telefonos del usuaro
     */
    QStringList phones;
    /*!
     * \brief cards Tarjetas bancarias del usuario
     */
    QList<MyCard> cards;
    /*!
     * \brief fingerprints
     */
    QList<MyFingerprint> fingerprints;
    /*!
     * \brief myPurchases
     */
    QList<MyPurchases> purchases;
};

#endif // MYUSER_H
