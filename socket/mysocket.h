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
#include<QTimer>
#include<QDate>

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

  void updateHoles();



signals:
  mySignalUpdateHoles(QJsonArray jsonArry);

  mySignalOnlyTarget(QJsonArray jsonArry);

  mySignalBattery(QVector<double> msg);

  mySignalBatteryValue(double msg);

  mySignalGradeData(QJsonArray jsonArry);

  mySignalState(QVector<int> msg);



public slots:
  //建立通信

  void groupNumber(QString indexZuHao);


  void sendYuanXin(int old_addr,int new_addr);//编码设置

  void sendBegin(int flag);//下一个

  void sendOver(int flag);//结束

  void searchData(int fenZu,int baHao,QString time);

  void sendHoles(int msg);

  void updateIndex(int msg);



private:
  ip_port ipPort;

  QList<QList<QString>> onlyHolesList;

  //  QString Ip = ipPort.ip;
  //  int Port = ipPort.port;
QTimer m_Timer;
  int code = 1;

  QString msg;
   QVector<int> vecState;


  int group_number = -1;

  int s_index = -1;
double batteryValue = 0;
};

#endif // MYSOCKET_H
