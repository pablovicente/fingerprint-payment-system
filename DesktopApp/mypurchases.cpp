#include "mypurchases.h"

MyPurchases::MyPurchases()
{
}
QString MyPurchases::getCode() const
{
    return code;
}

void MyPurchases::setCode(const QString &value)
{
    code = value;
}

QString MyPurchases::getCurrency() const
{
    return currency;
}

void MyPurchases::setCurrency(const QString &value)
{
    currency = value;
}
QString MyPurchases::getVenue() const
{
    return venue;
}

void MyPurchases::setVenue(const QString &value)
{
    venue = value;
}
QDate MyPurchases::getDate() const
{
    return date;
}

void MyPurchases::setDate(const QDate &value)
{
    date = value;
}
QString MyPurchases::getCard() const
{
    return card;
}

void MyPurchases::setCard(const QString &value)
{
    card = value;
}
QString MyPurchases::getAmount() const
{
    return amount;
}

void MyPurchases::setAmount(const QString &value)
{
    amount = value;
}


