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
#include <QDataStream>

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


private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    CryptoInfo *cryptoInfo;
    QString price;
    QString rank;
    QString marketCapUsd;

    QStringList coinNameList;
    QStringList coinIdList;
    int counter = 0;
    bool coinFound = false;
};
#endif // MAINWINDOW_H
