#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QStringList>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>


#include "cryptoinfo.h"
#include "staticbackground.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void populateComboBox();
    ~MainWindow();

public slots:
    void processNetworkData(QString);
    void displayTime();
    void displayDate();
    void updateCoinInfo();

private slots:

    void checkMediaState();
    void on_themeButton_clicked();
    void on_homeButton_clicked();
    void on_coinComboBox_currentIndexChanged(int index);
    void on_coinComboBox_currentTextChanged(const QString &arg1);
    void on_themeComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    CryptoInfo *cryptoInfo;
    QString price;
    QString rank;
    QString marketCapUsd;
    QString availableSupply;
    QString maxSupply;
    QString currentRequest;
    QStringList coinNameList;
    QStringList coinIdList;

    QTimer *refreshClock;
    QTimer *refreshDate;
    QTimer *updateCoinData;
    QTimer *loopMedia;

    StaticBackground *staticBackground;
    QGraphicsVideoItem *animatedBackground;
    QMediaPlayer *player;
    bool themeButtonClicked = false;
    bool homebuttonClicked = false;
    bool coinSelected = false;
    bool staticBackgroundActive = false;
    bool animatedBackgroungActive = false;
    bool coinFound = false;
    int counter = 0;
    int videoLoopTime = 0;




};
#endif // MAINWINDOW_H
