#include "communication.h"
#include "QMessageBox"

Communication::Communication(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    protocol = "http://";
    baseIP = "192.168.1.103";


    QFile cafile("/Users/Pablo/Desktop/FingerprintPaymentCA.pem");
    cafile.open(QIODevice::ReadOnly);

    QSslCertificate cert(&cafile);
    allowedCAs << cert;

    QSslSocket::setDefaultCaCertificates(allowedCAs);

}

bool Communication::registerUser(MyUser user)
{

    QString urlString = protocol + baseIP + "/register/";
    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();
    json["name"] = user.getName();
    json["surname"] = user.getSurname();
    json["email"] = user.getEmail();
    json["password"] = user.getPassword();
    json["birthday"] = user.getBirthday().toString("yyyy-MM-dd");
    json["street"] = user.getStreet();
    json["city"] = user.getCity();
    json["postcode"] = user.getPostcode();
    json["country"] = user.getCountry();
    json["phone"] = user.getPhones().at(0);
    if(user.getGender() == Male)
        json["gender"] = "Male";
    else
        json["gender"] = "Female";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();        
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();        

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {            
            status = true;
        }
        if(jsonObject["result"].toInt() == SIGN_UP_ERROR)
        {

        }

    }

    reply->deleteLater();

    return status;
}



bool Communication::insertCard(MyUser user, MyCard card)
{    
    QString urlString = protocol + baseIP + "/insert/";
    bool status = false;

    QJsonObject json;
    json["insertField"] = "card";
    json["cardNumber"] = card.getCardNumber();    
    json["idCard"] = "temp";
    json["shortCardNumber"] = card.getShortCardNumber();
    json["cardType"] = card.getCardType();
    json["cvv"] = card.getCvv();
    json["expirationMonth"] = card.getExpirationMonth();
    json["expirationYear"] = card.getExpirationYear();
    json["user"] = user.getId();    
    if(card.getSelected())
        json["selected"] = "True";
    else
        json["selected"] = "False";    


    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();    

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();                

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == USER_NOT_FOUND) //Existe
        {

        }
        if(jsonObject["result"].toInt() == CARD_FORM_ERROR) //Existe
        {

        }
        if(jsonObject["result"].toInt() == PAYPAL_CREDIT_CARD_NOT_SAVED) //Existe
        {
        }



    }

    reply->deleteLater();

    return status;
}



bool Communication::login(MyUser &userData)
{

    QString urlString = protocol + baseIP + "/loginUser/";
    bool status = false;

    QJsonObject json;
    json["idCode"] = userData.getId();
    json["password"] = userData.getPassword();

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QNetworkReply *reply = manager->post(request, postData);


    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();                        

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            QJsonObject user = jsonObject["user"].toObject();            
            userData.setEmail(user["email"].toString());
            userData.setStreet(user["street"].toString());
            userData.setCity(user["city"].toString());
            userData.setCountry(user["country"].toString());            
            userData.setName(user["name"].toString());
            userData.setSurname(user["surname"].toString());
            userData.setPostcode(user["postcode"].toString());
            if(user["postcode"].toString() == "Male")
                userData.setGender(Male);
            else
                userData.setGender(Female);

            status = true;
        }
        if(jsonObject["result"].toInt() == INVALID_LOGIN_DETAILS) //Existe
        {

        }

    }

    reply->deleteLater();


    return status;
}

bool Communication::logout()
{
    QString urlString = protocol + baseIP + "/logoutUser/";
    bool status = false;

    QUrl url(urlString);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QByteArray postData = NULL;
    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        qDebug() << "out " << strReply;

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
    }

    reply->deleteLater();


    return status;
}

bool Communication::searchUser(MyUser userData)
{

    QString urlString = protocol + baseIP + "/search/";
    bool status = false;

    QJsonObject json;
    json["email"] = userData.getEmail();
    json["idCode"] = userData.getId();
    json["searchField"] = "user";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QNetworkReply *reply = manager->post(request, postData);


    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();        

        if(jsonObject["result"].toInt() == SUCCESS) //Existe, No se puede crear
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == USER_NOT_FOUND) //No Existe, Se puede crear
        {         
            status = false;
        }

    }

    reply->deleteLater();


    return status;
}

bool Communication::selectPreferredCard(MyCard card)
{
    bool status = false;

    QString urlString = protocol + baseIP + "/selectPreferredCard/";

    QJsonObject json;

    json["idNewSelectedCard"] = card.getIdCard();

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
        else if(jsonObject["result"].toInt() == CARD_NOT_FOUND) //Existe
        {

        }

    }

    reply->deleteLater();

    return status;
}

bool Communication::retrieveCards(MyUser &user)
{

    bool status = false;

    QString urlString = protocol + baseIP + "/search/";

    QList<MyCard> qList;
    QJsonObject json;
    json["idCode"] = user.getId();
    json["searchField"] = "card";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();                

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            QJsonArray array = jsonObject["cards"].toArray();
            foreach (const QJsonValue & v, array)
            {
                MyCard card;
                card.setIdCard(v.toObject().value("idCard").toString());
                card.setShortCardNumber(v.toObject().value("shortCardNumber").toString());
                card.setCardType(v.toObject().value("cardType").toString());
                card.setExpirationMonth(v.toObject().value("expirationMonth").toString());
                card.setExpirationYear(v.toObject().value("expirationYear").toString());
                card.setSelected(v.toObject().value("selected").toBool());

                qList.push_back(card);
            }         
            user.setCards(qList);

            status = true;
        }     

    }

    reply->deleteLater();

    return status;
}

bool Communication::deleteCard(MyUser &user, MyCard card,  MyCard selectedCard)
{
    bool status = false;    

    QString urlString = protocol + baseIP + "/delete/";

    QJsonObject json;    
    json["deleteField"] = "card";
    json["idCode"] = user.getId();
    json["idCard"] = card.getIdCard();
    if(selectedCard.getIdCard() != NULL)
        json["idNewSelectedCard"] = selectedCard.getIdCard();

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }

    }

    reply->deleteLater();

    return status;
}

QHash<int,int> Communication::retrievePurchaes(MyUser &user,QDate initial,QDate final, PurchasesInfo info, int page)
{

    qDebug() << "page" << page;

    QString urlString = protocol + baseIP + "/searchPaginated/page/" + QString::number(page);
    QHash<int,int> pagination;
    QList<MyPurchases> oldPurchases;
    QList<MyPurchases> newPurchases;
    QJsonObject json;

    initial = initial.addDays(-1);
    final = final.addDays(1);

    json["idCode"] = user.getId();
    json["initial"] = initial.toString("yyyy-MM-dd");
    json["final"] = final.toString("yyyy-MM-dd");
    if(info == Detail)
        json["mode"] = "details";
    else
        json["mode"] = "basic";           

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();                        

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            oldPurchases = user.getPurchases();
            user.getPurchases().clear();

            QJsonArray array = jsonObject["purchases"].toArray();
            foreach (const QJsonValue & v, array)
            {
                MyPurchases purchases;
                purchases.setAmount(v.toObject().value("amount").toString());
                QString dateString = v.toObject().value("date").toString();
                QStringRef year(&dateString, 0, 4);
                QStringRef month(&dateString, 5, 2);
                QStringRef day(&dateString, 8, 2);
                QDate date(year.toInt(), month.toInt(), day.toInt());
                purchases.setDate(date);

                purchases.setVenue(v.toObject().value("venue").toString());
                purchases.setCurrency(v.toObject().value("currency").toString());
                newPurchases.push_back(purchases);
            }

            oldPurchases.append(newPurchases);

            user.setPurchases(oldPurchases);
            pagination.insert(NUM_PAGES, jsonObject["numPages"].toInt());
            pagination.insert(PAGE, jsonObject["pageNumber"].toInt());
        }
        if(jsonObject["result"].toInt() == PAYMENT_MODE_ERROR)
        {

        }

    }

    reply->deleteLater();

    return pagination;
}

bool Communication::retrievePhones(MyUser &user)
{    

    bool status = false;
    QString urlString = protocol + baseIP + "/search/";

    QJsonObject json;
    QStringList qList;
    json["idCode"] = user.getId();
    json["searchField"] = "phone";


    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QNetworkReply *reply = manager->post(request, postData);


    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            user.getPhones().clear();
            QJsonArray array = jsonObject["phones"].toArray();
            foreach (const QJsonValue & v, array)
            {              
              qList.push_back(v.toObject().value("phoneNumber").toString());
            }
            user.setPhones(qList);

            status = true;
        }
        if(jsonObject["result"].toInt() == DATA_NOT_FOUND)
        {

        }

    }

    reply->deleteLater();

    return status;
}

bool Communication::updateEmail(MyUser &user, QString newEmail)
{

    QString urlString = protocol + baseIP + "/update/";

    bool status = false;

    QJsonObject json;    
    json["oldEmail"] = user.getEmail();
    json["newEmail"] = newEmail;
    json["updateField"] = "email";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();   

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();        

        if(jsonObject["result"].toInt() == SUCCESS)
        {
            user.setEmail(newEmail);
            status = true;
        }
        if(jsonObject["result"].toInt() == EMAIL_NOT_UPDATED)
        {

        }
    }

    reply->deleteLater();

    return status;
}

bool Communication::insertPhone(MyUser &user, QString phone)
{
    QString urlString = protocol + baseIP + "/insert/";

    bool status = false;

    QJsonObject json;
    json["insertField"] = "phone";
    json["idCode"] = user.getId();
    json["phone"] = phone;    

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS)
        {
            QStringList tmpPhones = user.getPhones();
            tmpPhones.append(phone);
            user.setPhones(tmpPhones);
            status = true;
        }
        else if(jsonObject["result"].toInt() == PHONE_ALREADY_EXIST) //Ya tenias ese telefono
        {
            status = false;
        }
        else if(jsonObject["result"].toInt() == PHONE_NOT_UPDATED) //Ya tenias ese telefono
        {
            status = false;
        }
    }

    reply->deleteLater();

    return status;
}

bool Communication::updatePhone(MyUser &user, QString oldPhone, QString newPhone)
{
    QString urlString = protocol + baseIP + "/update/";

    bool status = false;

    QJsonObject json;   
    json["idCode"] = user.getId();
    json["oldPhone"] = oldPhone;
    json["newPhone"] = newPhone;
    json["updateField"] = "phone";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Telefono cambiado
        {
            QStringList tmpPhones = user.getPhones();
            tmpPhones.replaceInStrings(oldPhone,newPhone);
            user.setPhones(tmpPhones);
            status = true;
        }
        else if(jsonObject["result"].toInt() == PHONE_ALREADY_EXIST) //Ya tenias ese telefono
        {
            status = false;
        }
    }

    reply->deleteLater();

    return status;
}


bool Communication::updateName(MyUser &user, QString newName)
{
    QString urlString = protocol + baseIP + "/update/";

    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();
    json["oldName"] = user.getName();
    json["newName"] = newName;
    json["updateField"] = "name";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Nombre cambiado
        {
            user.setName(newName);
            status = true;
        }
        if(jsonObject["result"].toInt() == NAME_NOT_UPDATED) //Nombre cambiado
        {

        }

    }

    reply->deleteLater();

    return status;
}



bool Communication::updateSurname(MyUser &user, QString newSurname)
{
    QString urlString = protocol + baseIP + "/update/";

    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();
    json["oldSurname"] = user.getName();
    json["newSurname"] = newSurname;
    json["updateField"] = "surname";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Apellidos cambiado
        {
            user.setSurname(newSurname);
            status = true;
        }
        if(jsonObject["result"].toInt() == SURNAME_NOT_UPDATED) //Nombre cambiado
        {

        }

    }

    reply->deleteLater();

    return status;
}

bool Communication::updateAddress(MyUser &user, QString newStreet, QString newPostcode, QString newCity, QString newCountry)
{
    QString urlString = protocol + baseIP + "/update/";

    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();   
    json["newStreet"] = newStreet;
    json["newPostcode"] = newPostcode;
    json["newCity"] = newCity;
    json["newCountry"] = newCountry;
    json["updateField"] = "address";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Direccion cambiada
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == ADDRESS_NOT_UPDATED) //Nombre cambiado
        {

        }

    }

    reply->deleteLater();

    return status;

}

bool Communication::updatePassword(MyUser &user, QString newPassword)
{
    QString urlString = protocol + baseIP + "/update/";

    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();
    json["newPassword"] = newPassword;
    json["updateField"] = "password";

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Apellidos cambiado
        {
            user.setPassword(newPassword);
            status = true;
        }
        if(jsonObject["result"].toInt() == PASSWORD_NOT_UPDATED) //Nombre cambiado
        {

        }

    }

    reply->deleteLater();

    return status;
}


bool Communication::deletePhone(MyUser & user, QString oldPhone)
{
    QString urlString = protocol + baseIP + "/delete/";

    bool status = false;

    QJsonObject json;
    json["deleteField"] = "phone";
    json["idCode"] = user.getId();
    json["oldPhone"] = oldPhone;

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS) //Telefono Eliminado cambiado
        {

            status = true;
        }
        if(jsonObject["result"].toInt() == DATA_NOT_FOUND) //Telefono Eliminado cambiado
        {

        }


    }

    reply->deleteLater();

    return status;
}



bool Communication::deleteAccount(MyUser &user)
{
    QString urlString = protocol + baseIP + "/delete/";

    bool status = false;

    QJsonObject json;
    json["deleteField"] = "user";
    json["idCode"] = user.getId();

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        qDebug() << "Sus datos se han eliminado";

        if(jsonObject["result"].toInt() == SUCCESS) //Cuenta Eliminado
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == USER_NOT_FOUND) //Cuenta Eliminado
        {

        }


    }

    reply->deleteLater();

    return status;
}

bool Communication::blockAccount(MyUser &user)
{
    QString urlString = protocol + baseIP + "/blockAccount/";

    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();    

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {
        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        if(jsonObject["result"].toInt() == SUCCESS)
        {
            status = true;
        }

    }

    reply->deleteLater();

    return status;
}


bool Communication::saveFingerprint(MyUser &user, MyFingerprint &fingerprint)
{
    QString urlString = protocol + baseIP + "/insert/";
    bool status = false;

    QJsonObject json;
    json["insertField"] = "fingerprint";
    json["idCode"] = user.getId();
    json["finger"] = fingerprint.fingerType;
    json["hand"] = fingerprint.handType;

    QJsonArray array;    
    qDebug() << "MIN " << fingerprint.minutiaes.size();
    foreach(Minutia m, fingerprint.minutiaes)
    {
        QJsonObject jsonMinutiae;
        jsonMinutiae["xCoord"] = m.x;
        jsonMinutiae["yCoord"] = m.y;
        jsonMinutiae["angle"] = m.angle;
        jsonMinutiae["minutiaType"] = m.type;

        array.append(jsonMinutiae);
    }
    json["Minutiaes"] = array;

    QJsonDocument doc;
    doc.setObject(json);    

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();                

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == FINGERPRINT_ERROR) //Existe
        {

        }
        if(jsonObject["result"].toInt() == MINUTIAE_ERROR) //Existe
        {

        }
        if(jsonObject["result"].toInt() == USER_NOT_FOUND) //Existe
        {
        }


    }

    reply->deleteLater();

    return status;

}

bool Communication::validatePayment(MyFingerprint &fingerprint)
{
    QString urlString = protocol + baseIP + "/validatePayment/";
    bool status = false;

    QJsonObject json;    

    json["finger"] = fingerprint.fingerType;
    json["total"] = 1;



    QFile file("/Users/Pablo/Desktop/minucias2.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("\t");
        Minutia m;
        m.x = fields[0].toFloat();
        m.y = fields[1].toFloat();
        if(fields[2].toInt() == 1)
            m.type = End;
        else
           m.type = Bifurcation;

        m.angle = fields[3].toFloat();
        fingerprint.minutiaes.push_back(m);
    }

    file.close();



    QJsonArray array;

    foreach(Minutia m, fingerprint.minutiaes)
    {
        QJsonObject jsonMinutiae;
        jsonMinutiae["xCoord"] = m.x;
        jsonMinutiae["yCoord"] = m.y;
        jsonMinutiae["angle"] = m.angle;
        jsonMinutiae["minutiaType"] = m.type;

        array.append(jsonMinutiae);
    }
    json["Minutiaes"] = array;

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();        

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == CARD_NOT_FOUND) //Existe
        {

        }
        if(jsonObject["result"].toInt() == USER_NOT_FOUND) //Existe
        {

        }
        if(jsonObject["result"].toInt() == PAYPAL_SAVE_CARD_PAYMENT_ERROR) //Existe
        {
        }
        if(jsonObject["result"].toInt() == FINGER_NOT_MATCH) //Existe
        {
        }
        if(jsonObject["result"].toInt() == ACCOUNT_BLOCKED) //Existe
        {
        }

    }

    reply->deleteLater();

    return status;
}



bool Communication::forgottenPassword(MyUser &user,MyFingerprint &fingerprint)
{
    QString urlString = protocol + baseIP + "/forgottenPassword/";
    bool status = false;

    QJsonObject json;
    json["idCode"] = user.getId();
    json["newPassword"] = user.getPassword();

    QJsonArray array;

    foreach(Minutia m, fingerprint.minutiaes)
    {
        QJsonObject jsonMinutiae;
        jsonMinutiae["xCoord"] = m.x;
        jsonMinutiae["yCoord"] = m.y;
        jsonMinutiae["angle"] = m.angle;
        jsonMinutiae["minutiaType"] = m.type;

        array.append(jsonMinutiae);
    }
    json["Minutiaes"] = array;

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        qDebug() << "VERIFICANDO:   " << strReply;

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
        if(jsonObject["result"].toInt() == FINGER_NOT_MATCH) //Existe
        {

        }

    }

    reply->deleteLater();

    return status;
}

bool Communication::authenticateDevice(QString idDevice, QString password)
{
    QString urlString = protocol + baseIP + "/deviceAuthentication/";
    bool status = false;

    QJsonObject json;
    json["idDevice"] = idDevice;
    json["password"] = password;

    QJsonDocument doc;
    doc.setObject(json);

    QByteArray postData;
    postData = doc.toJson();

    QUrl url(urlString);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();


    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->error();
        qDebug() << reply->errorString();
    }
    else
    {

        QString strReply = (QString)reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();

        qDebug() << "VERIFICANDO:   " << strReply;

        if(jsonObject["result"].toInt() == SUCCESS) //Existe
        {
            status = true;
        }
    }

    reply->deleteLater();

    return status;
}

