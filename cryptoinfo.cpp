#include "cryptoinfo.h"

CryptoInfo::CryptoInfo(QObject *parent) : QObject(parent){
    this->qnam = new QNetworkAccessManager(this);
    QObject::connect(this->qnam, SIGNAL(finished(QNetworkReply*)),this, SLOT(readyRead(QNetworkReply*)));
}

void CryptoInfo::makeRequest(QString endpointRequest){
    qnam->get(QNetworkRequest(QUrl(endpointRequest)));
}

void CryptoInfo::readyRead(QNetworkReply *reply){
    QString ReplyText;
    ReplyText = reply->readAll();
    emit this->dataReadyRead(ReplyText);
}
