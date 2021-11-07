#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Set the background image of the GUI and make the labels transparent.
    ui->centralwidget->setStyleSheet("background-image: url(:/images/bg.png);");
    ui->priceLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->priceNumLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->rankLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->rankNumLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->marketCapLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->marketCapNumLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->availableSupplyLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->avialableSupplyNumLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxSupplyLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxSupplyNumLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->coinLogoLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->Crypto_Name->setAttribute(Qt::WA_TranslucentBackground);
    ui->timeLabel->setAttribute(Qt::WA_TranslucentBackground);
    ui->dateLabel->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(640, 310));

    //Instantiate the cyypto info object.
    cryptoInfo = new CryptoInfo();
    connect(cryptoInfo, SIGNAL(dataReadyRead(QString)), this, SLOT(processNetworkData(QString)));

    //Populate the combobox with coin info.
    populateComboBox();

    //Timer to update the clock every 1 second
    refreshClock = new QTimer();
    connect(refreshClock, SIGNAL(timeout()), this, SLOT(displayTime()));
    refreshClock->start(1000);

    //Timer to refresh the date every 1 second
    refreshDate = new QTimer();
    connect(refreshDate, SIGNAL(timeout()), this, SLOT(displayDate()));
    refreshDate->start(1000);

    //Timer to refresh the date every 1 second
    updateCoinData = new QTimer();
    connect(updateCoinData, SIGNAL(timeout()), this, SLOT(updateCoinInfo()));
    updateCoinData->start(1000);
}

MainWindow::~MainWindow(){
    delete ui;
}

//Get the network reply (API data). The JSON data is a nested object.
void MainWindow::processNetworkData(QString datax){
    QString replyText = datax;
    //qDebug() << replyText;
    QJsonDocument json_doc = QJsonDocument::fromJson(replyText.toUtf8());
    QJsonObject jsonObject = json_doc.object();

    //Get the desired info from the JSON data.
    QJsonObject obdata = jsonObject["data"].toObject();
    price = obdata["priceUsd"].toString();
    rank = obdata["rank"].toString();
    marketCapUsd = obdata["marketCapUsd"].toString();
    availableSupply = obdata["supply"].toString();
    maxSupply = obdata["maxSupply"].toString();

    //Display the data on GUI labels.
    ui->priceNumLabel->setText(price);
    ui->rankNumLabel->setText(rank);
    ui->marketCapNumLabel->setText(marketCapUsd);
    ui->avialableSupplyNumLabel->setText(availableSupply);
    ui->maxSupplyNumLabel->setText(maxSupply);
}

void MainWindow::displayTime(){
    QTime cTime = QTime::currentTime();
    ui->timeLabel->setText(cTime.toString("hh:mm:ss"));
}

void MainWindow::displayDate(){
    QDate cDate = QDate::currentDate();
    ui->dateLabel->setText(cDate.toString("MM/dd/yyyy"));
}

//Update the coin info. This will be called by the timer evers 1 second.
void MainWindow::updateCoinInfo(){
    if(ui->comboBox->currentText() == "Select Coin"){
        return;
    }
    cryptoInfo->makeRequest(currentRequest);
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
    //QString coinName = arg1;
    if(arg1 == "Select Coin"){
        return;
    }
    else{
        ui->Crypto_Name->setText(arg1);
        QPixmap coinLogo(":/images/" + arg1 + ".png");
        ui->coinLogoLabel->setPixmap(coinLogo);
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
            currentRequest = "https://api.coincap.io/v2/assets/" + coinId;
            coinFound = true;
        }
        if(coinFound == true){
            counter = 0;
            coinFound = false;
            return;
        }
    }
}

//Button for dark mode
void MainWindow::on_pushButton_clicked(){
    if(darkmodeEnabled == false){
        darkmodeEnabled = true;
        ui->centralwidget->setStyleSheet("background-image: url(:/images/bg2.png);");
        ui->rankLabel->setStyleSheet("color:white;");
        ui->rankNumLabel->setStyleSheet("color:white;");
        ui->priceLabel->setStyleSheet("color:white;");
        ui->priceNumLabel->setStyleSheet("color:white;");
        ui->marketCapLabel->setStyleSheet("color:white;");
        ui->marketCapNumLabel->setStyleSheet("color:white;");
        ui->availableSupplyLabel->setStyleSheet("color:white;");
        ui->avialableSupplyNumLabel->setStyleSheet("color:white;");
        ui->maxSupplyLabel->setStyleSheet("color:white;");
        ui->maxSupplyNumLabel->setStyleSheet("color:white;");
        ui->Crypto_Name->setStyleSheet("color:white;");
        ui->timeLabel->setStyleSheet("color:white;");
        ui->dateLabel->setStyleSheet("color:white;");
        ui->pushButton->setIcon(QIcon(":/images/lightbulb_b.png"));
        ui->comboBox->setStyleSheet("color:rgb(255, 255, 255);");
        ui->comboBox->setFocus();
    }
    else if(darkmodeEnabled == true){
        darkmodeEnabled = false;
        ui->centralwidget->setStyleSheet("background-image: url(:/images/bg.png);");
        ui->rankLabel->setStyleSheet("color:black;");
        ui->rankNumLabel->setStyleSheet("color:black;");
        ui->priceLabel->setStyleSheet("color:black;");
        ui->priceNumLabel->setStyleSheet("color:black;");
        ui->marketCapLabel->setStyleSheet("color:black;");
        ui->marketCapNumLabel->setStyleSheet("color:black;");
        ui->availableSupplyLabel->setStyleSheet("color:black;");
        ui->avialableSupplyNumLabel->setStyleSheet("color:black;");
        ui->maxSupplyLabel->setStyleSheet("color:black;");
        ui->maxSupplyNumLabel->setStyleSheet("color:black;");
        ui->Crypto_Name->setStyleSheet("color:black;");
        ui->timeLabel->setStyleSheet("color:black;");
        ui->dateLabel->setStyleSheet("color:black;");
        ui->pushButton->setIcon(QIcon(":/images/lightbulbw2.png"));
        ui->comboBox->setStyleSheet("color:black;");
        ui->comboBox->setFocus();
    }
}
