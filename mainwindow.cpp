#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Set the background image of the GUI and make the labels transparent.
    //setStyleSheet("background-image: url(:/images/bg.png);");
    ui->centralwidget->setStyleSheet("background-image: url(:/images/bg.png);");
    ui->Price_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Price_Num_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Rank_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Rank_Num_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Market_Cap_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Market_Cap_Num_Label->setAttribute(Qt::WA_TranslucentBackground);
    ui->Crypto_Name->setAttribute(Qt::WA_TranslucentBackground);

    //Instantiate the cyypto info object.
    cryptoInfo = new CryptoInfo();
    connect(cryptoInfo, SIGNAL(dataReadyRead(QString)), this, SLOT(processNetworkData(QString)));

    //Populate the combobox with coin info.
    populateComboBox();
}

MainWindow::~MainWindow(){
    delete ui;
}

//Get the network reply (API data). The JSON data is a nested object.
void MainWindow::processNetworkData(QString datax){
    QString replyText = datax;
    qDebug() << replyText;
    QJsonDocument json_doc = QJsonDocument::fromJson(replyText.toUtf8());
    QJsonObject jsonObject = json_doc.object();

    //Get the desired info from the JSON data.
    QJsonObject obdata = jsonObject["data"].toObject();
    price = obdata["priceUsd"].toString();
    rank = obdata["rank"].toString();
    marketCapUsd = obdata["marketCapUsd"].toString();

    //Display the data on GUI labels.
    ui->Price_Num_Label->setText(price);
    ui->Rank_Num_Label->setText(rank);
    ui->Market_Cap_Num_Label->setText(marketCapUsd);
}

//Populate the dropdown box with coin names from a file
void MainWindow::populateComboBox(){
    QFile inputFile(":/data/coinNameList.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()){
            QString line = in.readLine();
            coinNameList << line;
        }
        inputFile.close();
    }
    foreach(QString coinName, coinNameList){
        ui->comboBox->addItem(coinName);
    }
}

//Change the displayed coin named based on user selection
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1){
    QString coinName = arg1;
    if(arg1 == "Select Coin"){
        return;
    }
    else{
        ui->Crypto_Name->setText(arg1);
    }
}

//Pull data from the CoinCap API based on user selection
void MainWindow::on_comboBox_currentIndexChanged(int index){
    if(index == 0){
        return;
    }
    QFile inputFile(":/data/coinId.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()){
            QString line = in.readLine();
            coinIdList << line;
        }
        inputFile.close();
    }
    foreach(QString coinId, coinIdList){
        counter++;
        if(counter == index){
            cryptoInfo->makeRequest("https://api.coincap.io/v2/assets/" + coinId);
            coinFound = true;
        }
        if(coinFound == true){
            counter = 0;
            coinFound = false;
            return;
        }
    }
}
