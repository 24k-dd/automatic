#include "mysocket.h"

MySocket::MySocket(QObject *parent)
  : QTcpSocket(parent)
{
  for(int i = 0;i < array_size;i++)
    {
      vecState.push_back(0);
    }
  //    QString Ip = "192.168.4.2";

  QString Ip = "127.0.0.1";
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

  msg = map["msg"].toString();

  //  确定靶标连接状态
  if(code == GetTargetState){
      for(int i = 0;i < array_size;i++)
        {
          vecState[i] = 0;
        }
      QMap<QString, QVariant> map1 = map["data"].toMap();

      QMap<QString, QVariant>::iterator it = map1.begin();

      while(it != map1.end())
        {

          vecState[it.key().toInt()] = it.value().toInt();
          it++;
        }
      emit mySignalState(vecState);

    }else if(code == GetTargetInfo){//获取显示信息
      //获取所有靶的信息
      QJsonValue jsonValue = map["data"].toJsonValue();

      QJsonArray jsonArray = jsonValue.toArray();

      int cnt = jsonArray.size();

      QVector<Target_Info_Table> targetInfo;
      Target_Info_Table target_Info_Table;
      for(int i = 0;i < cnt;i++)
        {
          QJsonObject jsonObject = jsonArray[i].toObject();
          target_Info_Table.addr = jsonObject["addr"].toInt();
          target_Info_Table.x = jsonObject["x"].toDouble();
          target_Info_Table.y = jsonObject["y"].toDouble();
          target_Info_Table.cylinder_number = jsonObject["cylinder_number"].toInt();
          target_Info_Table.direction = jsonObject["direction"].toInt();
          target_Info_Table.user_name = jsonObject["user_name"].toString();
          targetInfo.push_back(target_Info_Table);
        }
      emit mySignalUpdateHoles(targetInfo);

      //获取单个靶的信息
      if(s_index == target_Info_Table.addr)
        {
          emit mySignalOnlyTarget(targetInfo);
        }

    }else if(code == GetVoltage){//获取电量信息
      QMap<QString, QVariant> map1 = map["data"].toMap();
      QMap<QString, QVariant>::iterator it = map1.begin();

      QVector<double> vecBattery(array_size,0);
      while(it != map1.end())
        {
          int addr = it.key().toInt();
          vecBattery[addr] = it.value().toDouble();
          //获取单个靶的电量信息
          if(addr == s_index)
            {
              batteryValue = it.value().toDouble();

              emit mySignalBatteryValue(batteryValue);
            }
          it++;
        }
      //获取所有靶的电量信息
      emit mySignalBattery(vecBattery);

    }else if(code == GetShowInfo){//获取显示信息 用于查询信息

      QJsonValue jsonValue = map["data"].toJsonValue();

      QJsonArray jsonArray = jsonValue.toArray();
      int cnt = jsonArray.size();

      QVector<Check_Target_Table> checkInfo;
      Check_Target_Table check_Info_Table;
      for(int i = 0;i < cnt;i++)
        {
          QJsonObject jsonObject = jsonArray[i].toObject();
          check_Info_Table.addr = jsonObject["addr"].toInt();
          check_Info_Table.cylinder_number = jsonObject["cylinder_number"].toInt();
          check_Info_Table.group_number = jsonObject["group_number"].toInt();
          check_Info_Table.user_name = jsonObject["user_name"].toString();
          checkInfo.push_back(check_Info_Table);
        }
      emit mySignalGradeData(checkInfo);
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
      if(vecState[i] == flag_3)
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
      QByteArray temp = read(1);

      recvAllMsg.append(temp);

      if(temp.contains('\n'))
        {
          recvData();
          recvAllMsg.clear();
          return ;
        }
    }

}

//分组控制信息
void MySocket::sendGroupNumber(QString indexZuHao)
{
  group_number = indexZuHao.toInt();

  Send_Info sendDataInfo;
  sendDataInfo.code = UserGrouping;
  sendDataInfo.data.insert("group_number",group_number);

  QByteArray data = structToJson(sendDataInfo);

  sendData(data);

  qDebug()<<"分组指令已发送:"<<data;

}

//更改编号控制信息
void MySocket::sendYuanXin(int old_addr, int new_addr)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = RewriteTargetId;
  sendDataInfo.data.insert("old_addr",old_addr);
  sendDataInfo.data.insert("new_addr",new_addr);

  QByteArray data = structToJson(sendDataInfo);

  sendData(data);

  qDebug()<<"编码设置指令已发送:"<<data;
}

//开始校准控制信息
void MySocket::sendBegin(int flag)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = OpenCalibrationTargetById;
  sendDataInfo.data.insert("addr",flag);

  QByteArray data = structToJson(sendDataInfo);

  sendData(data);

  qDebug()<<"开始校准指令已发送:"<<data;
}

//结束校准控制信息
void MySocket::sendOver(int flag)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = CloseCalibrationTargetById;
  sendDataInfo.data.insert("addr",flag);

  QByteArray data = structToJson(sendDataInfo);

  sendData(data);

  qDebug()<<"结束指令已发送:"<<data;
}

//查询数据
void MySocket::sendSearchData(int fenZu, int baHao, QString time)
{

  Send_Info sendDataInfo;
  sendDataInfo.code = GetShowInfo;
  sendDataInfo.msg.insert("date",time);
  sendDataInfo.data.insert("addr",baHao);
  sendDataInfo.data.insert("group_number",fenZu);

  QByteArray data = structToJson(sendDataInfo);

  sendData(data);

  qDebug()<<"查询成绩指令已发送:"<<data;
}

//请求靶号
void MySocket::sendHoles(int msg)
{
  QDate m_date = QDate::currentDate();
  QString currentDate = m_date.toString("yyyy-MM-dd");

  Send_Info sendDataInfo;
  sendDataInfo.code = GetTargetInfo;
  sendDataInfo.msg.insert("date",currentDate);
  sendDataInfo.data.insert("addr",msg);
  sendDataInfo.data.insert("group_number",group_number);

  QByteArray data = structToJson(sendDataInfo);

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

//更新当前所选中的靶标
void MySocket::updateIndex(int msg)
{
  s_index = msg + 1;
}








