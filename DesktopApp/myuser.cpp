#include "myuser.h"

MyUser::MyUser()
{

}


/*
 * Setter and Getter
 */

QString MyUser::getName() const
{
    return name;
}

void MyUser::setName(const QString &value)
{
    name = value;
}
QString MyUser::getCountry() const
{
    return country;
}

void MyUser::setCountry(const QString &value)
{
    country = value;
}
QString MyUser::getEmail() const
{
    return email;
}

void MyUser::setEmail(const QString &value)
{
    email = value;
}

QString MyUser::getCity() const
{
    return city;
}

void MyUser::setCity(const QString &value)
{
    city = value;
}

QString MyUser::getPassword() const
{
    return password;
}

void MyUser::setPassword(const QString &value)
{
    password = value;
}
QString MyUser::getId() const
{
    return id;
}

void MyUser::setId(const QString &value)
{
    id = value;
}
QString MyUser::getSurname() const
{
    return surname;
}

void MyUser::setSurname(const QString &value)
{
    surname = value;
}
QStringList MyUser::getPhones() const
{
    return phones;
}

void MyUser::setPhones(const QStringList &value)
{
    phones = value;
}
QString MyUser::getPostcode() const
{
    return postcode;
}

void MyUser::setPostcode(const QString &value)
{
    postcode = value;
}
QList<MyCard> MyUser::getCards() const
{
    return cards;
}

void MyUser::setCards(const QList<MyCard> &value)
{
    cards = value;
}
QList<MyFingerprint> MyUser::getFingerprints() const
{
    return fingerprints;
}

void MyUser::setFingerprints(const QList<MyFingerprint> &value)
{
    fingerprints = value;
}
QDate MyUser::getBirthday() const
{
    return birthday;
}

void MyUser::setBirthday(const QDate &value)
{
    birthday = value;
}

Gender MyUser::getGender() const
{
    return gender;
}

void MyUser::setGender(const Gender &value)
{
    gender = value;
}
QList<MyPurchases> MyUser::getPurchases() const
{
    return purchases;
}

void MyUser::setPurchases(const QList<MyPurchases> &value)
{
    purchases = value;
}


QString MyUser::getStreet() const
{
    return street;
}

void MyUser::setStreet(const QString &value)
{
    street = value;
}

void MyUser::clearPhones(void)
{
    phones.clear();
}

void MyUser::clearCards(void)
{
    cards.clear();
}

void MyUser::clearFingerprints(void)
{
    fingerprints.clear();
}

void MyUser::clearPurchases(void)
{
    purchases.clear();
}
bool MyUser::getAccountBlocked() const
{
    return accountBlocked;
}

void MyUser::setAccountBlocked(bool value)
{
    accountBlocked = value;
}


void MyUser::clearUser()
{
    setId("");
    setName("");
    setSurname("");
    setEmail("");
    setPassword("");
    setStreet("");
    setStreet("");
    setStreet("");
    setCity("");
    setPostcode("");
    setCountry("");
    setGender(NotSetted);
    clearPhones();
    clearCards();
    clearFingerprints();
    clearPurchases();
}







