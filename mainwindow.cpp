#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);

    //Initially hide the labels
    ui->rankLabel->hide();
    ui->priceLabel->hide();  
    ui->marketCapLabel->hide();
    ui->availableSupplyLabel->hide();
    ui->maxSupplyLabel->hide();

    //Make the labels transparent.
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
    ui->rectBackgroundLabel->setAttribute(Qt::WA_TranslucentBackground);

    //Make the main window a fixed size
    this->setFixedSize(QSize(800, 450));

    //Make text color white for labels
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
    ui->themeComboBox->hide();

    //Create the graphics scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,450);

    //Set the scene on the graphics view
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Make the initial backround static
    staticBackground = new StaticBackground(QPixmap(":images/cube_bg"));
    staticBackground->setPos(0,0);
    scene->addItem(staticBackground);
    staticBackgroundActive = true;

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

    //Timer to refresh the coin data every 1 second
    updateCoinData = new QTimer();
    connect(updateCoinData, SIGNAL(timeout()), this, SLOT(updateCoinInfo()));
    updateCoinData->start(1000);

    //Timer to loop media. Currently a bug exists that is not fixed.
    loopMedia = new QTimer();
    connect(loopMedia, SIGNAL(timeout()), this, SLOT(checkMediaState()));
}

MainWindow::~MainWindow(){
    delete ui;
}

//Get the network reply (API data). The JSON data is a nested object.
void MainWindow::processNetworkData(QString datax){
    QString replyText = datax;
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

    //Show labels after coin is selected
    ui->priceLabel->show();
    ui->rankLabel->show();
    ui->marketCapLabel->show();
    ui->availableSupplyLabel->show();
    ui->maxSupplyLabel->show();
}

//Function to display the time
void MainWindow::displayTime(){
    QTime cTime = QTime::currentTime();
    ui->timeLabel->setText(cTime.toString("hh:mm:ss"));
}

//Function to display the date
void MainWindow::displayDate(){
    QDate cDate = QDate::currentDate();
    ui->dateLabel->setText(cDate.toString("MM/dd/yyyy"));
}

//Update the coin info. This will be called by the timer every 1 second.
void MainWindow::updateCoinInfo(){
    if(ui->coinComboBox->currentText() == "Select Coin"){
        return;
    }
    cryptoInfo->makeRequest(currentRequest);
}

//Populate the dropdown box with coin names from a file
void MainWindow::populateComboBox(){
    QFile inputFile(":/data/coinNameList.txt");
    if(inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while (!in.atEnd()){
            QString line = in.readLine();
            coinNameList << line;
        }
        inputFile.close();
    }
    foreach(QString coinName, coinNameList){
        ui->coinComboBox->addItem(coinName);
    }
}

//Function to loop the media. A bug currently exist in Qt that causes gaps in video.
void MainWindow::checkMediaState(){
    if(player->position() > 9800 ){
        player->setPosition(0);
        player->play();
    }
}

//Show the theme selection combo box
void MainWindow::on_themeButton_clicked(){
    if(themeButtonClicked == true){
        return;
    }
    if(themeButtonClicked == false){
        themeButtonClicked = true;
        homebuttonClicked = false;
        ui->coinComboBox->hide();
        ui->themeComboBox->show();
    }
}

//Show the coin selection combo box
void MainWindow::on_homeButton_clicked(){
    if(homebuttonClicked == true){
        return;
    }
    if(homebuttonClicked == false && themeButtonClicked == true){
        themeButtonClicked = false;
        homebuttonClicked = true;
        ui->themeComboBox->hide();
        ui->coinComboBox-> show();
    }
}

//Pull data from the CoinCap API based on user selection
void MainWindow::on_coinComboBox_currentIndexChanged(int index){
    if(index == 0){
        return;
    }
    coinSelected = true;
    QFile inputFile(":/data/coinId.txt");
    if(inputFile.open(QIODevice::ReadOnly)){
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

//Change the displayed coin named based on user selection
void MainWindow::on_coinComboBox_currentTextChanged(const QString &arg1){
    if(arg1 == "Select Coin"){
        return;
    }
    else{
        ui->Crypto_Name->setText(arg1);
        QPixmap coinLogo(":/images/" + arg1 + ".png");
        ui->coinLogoLabel->setPixmap(coinLogo);
    }
}

//Function to change the background
void MainWindow::on_themeComboBox_currentTextChanged(const QString &arg1){
    if(arg1 == "Static 1" && animatedBackgroungActive == true){
        player->stop();
        ui->graphicsView->scene()->removeItem(animatedBackground);
        loopMedia->stop();
        delete animatedBackground;
        staticBackgroundActive = false;

        staticBackground = new StaticBackground(QPixmap(":images/cube_bg"));
        staticBackground->setPos(0,0);
        scene->addItem(staticBackground);
        staticBackgroundActive = true;
    }
    if(arg1 == "Animated 1" && staticBackgroundActive == true){
        scene->removeItem(staticBackground);
        delete staticBackground;
        staticBackgroundActive = false;

        animatedBackground = new QGraphicsVideoItem();
        QSize size(800,450);
        animatedBackground->setSize(size);

        ui->graphicsView->scene()->addItem(animatedBackground);
        player = new QMediaPlayer(this);
        player->setVideoOutput(animatedBackground);
        player->setMedia(QUrl("qrc:/images/blue.mp4"));
        player->play();
        loopMedia->start(1);
        animatedBackgroungActive = true;
    }
}
