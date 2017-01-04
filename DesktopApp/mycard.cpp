#include "mycard.h"

MyCard::MyCard()
{
}
QString MyCard::getCardNumber() const
{
    return cardNumber;
}

void MyCard::setCardNumber(const QString &value)
{
    cardNumber = value;
}

QString MyCard::getCardType() const
{
    return cardType;
}

void MyCard::setCardType(const QString &value)
{
    cardType = value;
}

QString MyCard::getCvv() const
{
    return cvv;
}

void MyCard::setCvv(const QString &value)
{
    cvv = value;
}

QString MyCard::getShortCardNumber() const
{
    return shortCardNumber;
}

void MyCard::setShortCardNumber(const QString &value)
{
    shortCardNumber = value;
}
bool MyCard::getSelected() const
{
    return selected;
}

void MyCard::setSelected(bool value)
{
    selected = value;
}
QString MyCard::getExpirationYear() const
{
    return expirationYear;
}

void MyCard::setExpirationYear(const QString &value)
{
    expirationYear = value;
}
QString MyCard::getIdCard() const
{
    return idCard;
}

void MyCard::setIdCard(const QString &value)
{
    idCard = value;
}


QString MyCard::getExpirationMonth() const
{
    return expirationMonth;
}

void MyCard::setExpirationMonth(const QString &value)
{
    expirationMonth = value;
}











