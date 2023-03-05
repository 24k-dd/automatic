#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include<QString>
#include<QJsonValue>
#include<QJsonObject>
#include<QVariantMap>
#include<QJsonDocument>
#include<QByteArray>
#include<QNetworkProxy>
#include<QHostAddress>
#include<QJsonArray>
#include<QVariant>
#include<QVector>
#include"Model.h"
#include"ip_port.h"


class MySocket : public QTcpSocket
{
  Q_OBJECT

public:
  explicit MySocket(QObject *parent = nullptr);



  //发m送数据
  void sendData(QString msg);

  //接收数据
  void recvData();

  //关闭通信
  void closeSocket();

signals:
  mySignalUpdateHoles(QList<QList<QString>> msg);

  mySignalState(QVector<int> msg);

  mySignalBattery(QVector<double> msg);

public slots:
  //建立通信
  void tryConnect();

private:
  ip_port ipPort;

  //  QString Ip = ipPort.ip;
  //  int Port = ipPort.port;

  int code = 1;

  QString msg;

};

#endif // MYSOCKET_H
