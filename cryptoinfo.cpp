#include "cryptoinfo.h"

CryptoInfo::CryptoInfo(QObject *parent) : QObject(parent){
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &CryptoInfo::readyRead);
}

void CryptoInfo::makeRequest(QString endpointRequest){
    manager->get(QNetworkRequest(QUrl(endpointRequest)));
}

void CryptoInfo::readyRead(QNetworkReply *reply){
    QString ReplyText;
    ReplyText = reply->readAll();
    emit this->dataReadyRead(ReplyText);
}
