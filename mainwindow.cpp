#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);

    setStyleSheet("background-image: url(:/images/bg.png);");
    ui->Price_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Price_Num_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Rank_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Rank_Num_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Market_Cap_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Market_Cap_Num_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Crypto_Name->setAttribute(Qt::WA_TranslucentBackground);

    //Get data from the CoinCap API
    this->networkManager = new CryptoInfo();
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
    price = obdata["priceUsd"].toString();
    rank = obdata["rank"].toString();
    marketCapUsd = obdata["marketCapUsd"].toString();

    ui->Price_Num_Label->setText(price);
    ui->Rank_Num_Label->setText(rank);
    ui->Market_Cap_Num_Label->setText(marketCapUsd);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1){

    if(arg1 == "Bitcoin"){
        ui->Crypto_Name->setText("Bitcoin");
        connect(networkManager, SIGNAL(dataReadyRead(QString)), this, SLOT(processNetworkData(QString)));
        networkManager->makeRequest("https://api.coincap.io/v2/assets/bitcoin");

    }
    else if(arg1 == "Ethereum"){
        ui->Crypto_Name->setText("Ethereum");
        connect(networkManager, SIGNAL(dataReadyRead(QString)), this, SLOT(processNetworkData(QString)));
        networkManager->makeRequest("https://api.coincap.io/v2/assets/ethereum");
    }
}
