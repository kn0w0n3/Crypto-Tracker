#ifndef CRYPTOINFO_H
#define CRYPTOINFO_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class CryptoInfo : public QObject
{
    Q_OBJECT
public:
    CryptoInfo(QObject *parent = nullptr);
    void makeRequest(QString);

signals:
    void dataReadyRead(QString);

public slots:
    void readyRead(QNetworkReply *);

private:
    QNetworkAccessManager *qnam;
};

#endif // CRYPTOINFO_H
