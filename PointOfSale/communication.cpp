#include "communication.h"

Communication::Communication(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    baseIP = "192.168.1.103";
    protocol = "http://";

    QFile cafile("/home/pablo/RaspFingerprint/FingerprintPaymentCA.pem");
    cafile.open(QIODevice::ReadOnly);

    QSslCertificate cert(&cafile);
    allowedCAs << cert;

    QSslSocket::setDefaultCaCertificates(allowedCAs);
}

bool Communication::makePayment(MyFingerprint &fingerprint, QString total, QString currency, QString venue)
{
    QString urlString = protocol + baseIP + "/validatePayment/";
    bool status = false;

    QJsonObject json;
    json["finger"] = fingerprint.type;
    json["total"] = total.toFloat();
    json["currency"] = currency;
    json["venue"] = venue;

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


