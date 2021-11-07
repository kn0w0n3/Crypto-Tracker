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

#include "cryptoinfo.h"

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
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    CryptoInfo *cryptoInfo;
    QString price;
    QString rank;
    QString marketCapUsd;
    QString availableSupply;
    QString maxSupply;
    QString currentRequest;
    QStringList coinNameList;
    QStringList coinIdList;
    int counter = 0;
    bool coinFound = false;
    QTimer *refreshClock;
    QTimer *refreshDate;
    QTimer *updateCoinData;
    bool darkmodeEnabled = false;
};
#endif // MAINWINDOW_H
