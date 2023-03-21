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
#include<QNetworkInterface>


#include"Model.h"
#include"api.h"

class MySocket : public QTcpSocket
{
  Q_OBJECT

public:
  explicit MySocket(QObject *parent = nullptr);

  //发m送数据
  void sendData(QString msg);

  //关闭通信
  void closeSocket();

  //更新已连接靶标数据
  void updateHoles();

  //请求已连接靶的数据
  void sendHoles(int msg);

    QString getMyIpString();

signals:

  //传递所有靶的数据
  mySignalUpdateHoles(const QVector<Target_Info_Table> &data);

  //传递单个靶的数据
  mySignalOnlyTarget(const QVector<Target_Info_Table> &data);

  //传递所有靶的电量数据
  mySignalBattery(QVector<double> msg);

  //传递单个靶的电量数据
  mySignalBatteryValue(double msg);

  //传递所有靶的数据 用于成绩查询
  mySignalGradeData(const QVector<Check_Target_Table> &data);

  mySignalState(QVector<int> vec);

public slots:

  //人员分组控制信息
  void sendGroupNumber(QString indexZuHao);

  //地址设置 原新编码控制信息
  void sendYuanXin(int old_addr,int new_addr);

  //校准程序 开始校准控制信息
  void sendBegin(int flag);

  //校准程序 结束控制信息
  void sendOver(int flag);

  //成绩导出 查询成绩控制信息
  void sendSearchData(int fenZu,int baHao,QString time);

  //更新当前双击 单击 靶标的id
  void updateIndex(int msg);

  //接收数据
  void recvData();

  //读取数据
  void readMessage();

private:
int Port = 32728;

  QTimer m_Timer;

  //区分数据
  int code = 1;

  //信息
  QString msg;

  //区分靶标连接状态 0表示未连接 其他表示已连接
  QVector<int> vecState;

  //分组信息 默认为-1
  int group_number = -1;

  //当前id
  int s_index = -1;

  //电量数据
  double batteryValue = 0;

  QByteArray recvAllMsg = "";


};

#endif // MYSOCKET_H
