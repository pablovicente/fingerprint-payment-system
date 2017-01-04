#include "utils.h"



Utils::Utils()
{
    idLetters << "T" << "R" << "W" << "A" << "G" << "M" << "Y" << "F" << "P" << "D" << "X" << "B" << "N" << "J" << "Z" << "S" << "Q" << "V" << "H" << "L" << "C" << "K" << "E";
}

bool Utils::validateEmail(QString email)
{
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    return mailREX.exactMatch(email);

}

bool Utils::validateTextField(QString text)
{
    QString trimmed = text.trimmed();

    if(trimmed.isEmpty()){
        return false;
    }else{
        return true;
    }
}

bool Utils::comparePassword(QString pass1, QString pass2)
{        
    if(pass1.compare(pass2,Qt::CaseSensitive) == 0) {
        return true;
    }
    return false;
}


bool Utils::isOver18(QDate birthdate)
{

    float days = (float)birthdate.daysTo(QDate::currentDate());
    float years = days / 365;

    if(years >= 18) {
        return true;
    }

    return false;
}

bool Utils::isValidDate(QDate date)
{
    float days = (float)date.daysTo(QDate::currentDate());

    qDebug() << days;

    if(days > 0)
    {        
        return false;
    }    

    return true;
}

bool Utils::hasExpired(QDate date)
{
    QDate today = QDate::currentDate();

    if(today.year() > date.year())
    {
        return false;
    }
    else
    {
        if(today.month() > date.month())
        {
            return false;
        }
    }

    return true;

}

QString Utils::parseCreditCard(QString card)
{
    QString parsedCard;
    QStringList cardParts = card.split( "-" );

    for(int i=0; i<cardParts.size(); i++)
        parsedCard = parsedCard + cardParts.at(i);

    return parsedCard;
}

QString Utils::extractLastCardDigits(QString card)
{    
    return card.right(4);
}


QString Utils::getCorrespondingLetter(QString id)
{
    QStringRef number(&id, 0, 8);
    int index = number.toInt() % 23;

    return idLetters.at(index);
}

bool Utils::verifyID(QString id)
{
    if(id.length() != 9)
        return false;
    else
        return (getCorrespondingLetter(id) == id.at(8));
}


bool Utils::luhn(const string& id)
{
    static const int m[10]  = {0,2,4,6,8,1,3,5,7,9}; // mapping for rule 3
    bool is_odd_dgt = false;
    auto lambda = [&](int a, char c) {return a + ((is_odd_dgt = !is_odd_dgt) ? c-'0' : m[c-'0']);};
    int s = std::accumulate(id.rbegin(), id.rend(), 0, lambda);
    return 0 == s%10;
}

