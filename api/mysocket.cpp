#include "mysocket.h"

MySocket::MySocket(QObject *parent)
  : QTcpSocket(parent)
{
  for(int i = 0;i < array_size;i++)
    {
      vecState.append(1);
    }
//  Ip = "192.168.4.2";

        Ip = "127.0.0.1";
  //  QString Ip = "192.168.43.52";
  //去掉代理
  setProxy(QNetworkProxy::NoProxy);

  //ip和端口号
  connectToHost(QHostAddress(Ip),Port);

  if(waitForConnected())
    {
      qDebug() << "connect success";
    }else{
      qDebug() << "connect failed";
    }

  m_reconnectTimer = new QTimer;

  m_reconnectTimer->setSingleShot(true);

  m_reconnectTimer->setInterval(10000);

  connect(this,&QTcpSocket::connected,this,&MySocket::onConnected);

  connect(this,&QTcpSocket::disconnected,this,&MySocket::onDisconnected);

  connect(m_reconnectTimer,&QTimer::timeout,this,&MySocket::reconnect);

  connect(this, &QTcpSocket::readyRead,this,&MySocket::readMessage);


  m_Timer.setInterval(holes_time);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      //请求已连接状态的靶标信息
      updateHoles();

    });

}

void MySocket::sendData(QString msg)
{
  //发送信息
  write(msg.toUtf8().data());
}

void MySocket::recvData()
{

  int index = recvAllMsg.indexOf('\n');

  recvAllMsg.remove(index,recvAllMsg.size() - index);

  qDebug()<<"接收数据大小:"<<recvAllMsg.size();

  QString recvStr = QString::fromUtf8(recvAllMsg);

  //  构建JSON对象
  QJsonObject json = QstringToJson(recvStr);
  //  Json转QMap
  QVariantMap map = json.toVariantMap();

  code = map["code"].toInt();


  //  确定靶标连接状态
  if(code == GetTargetState){

      vecState = getStateApi(vecState,map);

      emit mySignalState(vecState);

    }
  else if(code == GetTargetInfo){//获取显示信息

      QMap<QString, QVariant> map3 = map["msg"].toMap();
      int addr = map3["addr"].toInt();

      if(addr == s_index + 1)
        {
          emit mySignalOnlyTarget(getTargetInfoApi(map));
        }

      emit mySignalUpdateHoles(getTargetInfoApi(map),addr);

      //          getTargetInfoApi(map)

    }else if(code == GetVoltage){//获取电量信息

      QVector<double> vecBattery = getvecBatteryApi(map);

      //获取所有靶的电量信息
      emit mySignalBattery(vecBattery);

    }else if(code == GetShowInfo){//获取显示信息 用于查询信息

      emit mySignalGradeData(getShowInfoApi(map));

      //      getShowInfoApi(map)

    }else if(code == BindInfo)
    {
      QMap<QString, QVariant> map2 = map["msg"].toMap();
      QString msg = map2["msg"].toString();

      emit mySignalInfo(msg);
    }
}

void MySocket::closeSocket()
{
  close();
}

//请求已连接靶标信息
void MySocket::updateHoles()
{
  for(int i = 1;i < array_size;i++)
    {
      if(vecState[i] == flag_3 || vecState[i] == flag_5)
        {
          sendHoles(i);
        }
    }

}

//读取一帧数据
void MySocket::readMessage()
{
  while(true)
    {
      QByteArray temp =read(1);
      if (temp.size()>0){
          recvAllMsg.append(temp[0]);
          if(temp[0] == '\n')
            {
              recvData();

              recvAllMsg.clear();
              return ;
            }
        }else{
          break;
        }
    }

}

void MySocket::updateId(int msg)
{
  s_index = msg;
}

void MySocket::onConnected()
{
  qDebug()<<"Connected to server";
  m_reconnectTimer->stop();
}

void MySocket::onDisconnected()
{
  qDebug()<<"Disconnect from server";
  m_reconnectTimer->start();
}

void MySocket::reconnect()
{
  qDebug()<<"Reconnecting...";
  //ip和端口号
  connectToHost(QHostAddress(Ip),Port);
}

void MySocket::openInfo()
{
  QByteArray data = openInfoApi();

  sendData(data);
  qDebug()<<"开始人员录入指令已发送:"<<data;

}

void MySocket::closeInfo()
{
  QByteArray data = closeInfoApi();

  sendData(data);
  qDebug()<<"结束人员录入指令已发送:"<<data;
}

void MySocket::bindInfo(QString name, QString idCard)
{
  for(int i = 1;i < array_size;i++)
    {
      if(vecState[i] == flag_5)
        {
          QByteArray data = bindInfoApi(i,name,idCard);

          sendData(data);
          qDebug()<<"人员信息已发送:"<<data;
          vecState[i] = flag_3;
          break;
        }
    }

}

//分组控制信息
void MySocket::sendGroupNumber(QString indexZuHao)
{
  group_number = indexZuHao.toInt();

  QByteArray data = sendGroupNumberApi(group_number);

  sendData(data);

  qDebug()<<"分组指令已发送:"<<data;

}

//更改编号控制信息
void MySocket::sendYuanXin(int old_addr, int new_addr)
{

  QByteArray data = sendYuanXinApi(old_addr,new_addr);
  sendData(data);

  qDebug()<<"编码设置指令已发送:"<<data;
}

//开始校准控制信息
void MySocket::sendBegin(int flag)
{
  QByteArray data = sendBeginApi(flag);

  sendData(data);

  qDebug()<<"开始校准指令已发送:"<<data;
}

//结束校准控制信息
void MySocket::sendOver(int flag)
{
  QByteArray data = sendOverApi(flag);
  sendData(data);

  qDebug()<<"结束指令已发送:"<<data;
}

//查询数据
void MySocket::sendSearchData(int fenZu, int baHao, QString time)
{
  QByteArray data = sendSearchDataApi(fenZu,baHao,time);
  sendData(data);

  qDebug()<<"查询成绩指令已发送:"<<data;
}

//请求靶号
void MySocket::sendHoles(int msg)
{
  QByteArray data = sendHolesApi(msg,group_number);
  sendData(data);

}

QString MySocket::getMyIpString()
{
  QString ip_address;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses(); // 获取所有ip
  for (int i = 0; i < ipAddressesList.size(); ++i)
    {

      QHostAddress ipAddr = ipAddressesList.at(i);
      if ((ipAddr.protocol() == QAbstractSocket::IPv4Protocol))// 筛选出ipv4
        {

          if (!ipAddr.toString().startsWith("169"))// 过滤掉网卡，路由器等的ip
            {
              ip_address = ipAddr.toString();
              break;
            }
        }
    }
  if (ip_address.isEmpty())
    ip_address = QHostAddress(QHostAddress::LocalHost).toString();
  return ip_address;
}







