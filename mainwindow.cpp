#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Get data from the CoinCap API
     this->networkManager = new CryptoInfo();
     connect(networkManager, SIGNAL(dataReadyRead(QString)), this, SLOT(processNetworkData(QString)));
     networkManager->makeRequest("https://api.coincap.io/v2/assets/bitcoin");
}

MainWindow::~MainWindow(){
    delete ui;
}

//JSON is nested object
void MainWindow::processNetworkData(QString datax){
    QString replyText = datax;
    qDebug() << replyText;
    QJsonDocument json_doc = QJsonDocument::fromJson(replyText.toUtf8());

    QJsonObject jsonObject = json_doc.object();
    QJsonObject obdata = jsonObject["data"].toObject();
    QString price =obdata["priceUsd"].toString();
    ui->cryptoPrice->setText(price);
    //qDebug() << price;

    //Find Key
    /*
    foreach(const QString &key, jsonObject.keys()){
        //
        QJsonValue value = jsonObject.value(key);
        if(!value.isObject() ){
            qDebug() << "Key = " << key << ", Value = " << value;
        }
        else{
            qDebug() << "Nested Key = " << key;
            //traversJson(value.toObject());
        }
    }
    */
}

