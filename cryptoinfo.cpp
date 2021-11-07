#include "cryptoinfo.h"

CryptoInfo::CryptoInfo(QObject *parent) : QObject(parent){
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &CryptoInfo::readyRead);
}

void CryptoInfo::makeRequest(QString endpointRequest){
    QNetworkRequest request=QNetworkRequest(QUrl(endpointRequest));
	
    //API key goes here. Replace xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx with your API key.
    //request.setRawHeader(QByteArray("Authorization"), QByteArray("Bearer xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"));
    manager->get(request);
}

void CryptoInfo::readyRead(QNetworkReply *reply){
    QString ReplyText;
    ReplyText = reply->readAll();
    emit this->dataReadyRead(ReplyText);
}
