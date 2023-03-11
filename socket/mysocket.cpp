#include "mysocket.h"

MySocket::MySocket(QObject *parent)
  : QTcpSocket(parent)
{
  for(int i = 0;i < array_size;i++)
    {
      vecState.push_back(0);
    }
        QString Ip = "127.0.0.1";
//    QString Ip = "192.168.43.191";
//  QString Ip = "192.168.43.52";
  int Port = 32728;

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

  connect(this, &QTcpSocket::readyRead,this,&MySocket::recvData);

  m_Timer.setInterval(holes_time);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){
      updateHoles();

    });

}

void MySocket::sendData(QString msg)
{
  write(msg.toUtf8().data());
  //  qDebug()<<"send:"<<msg;
}

void MySocket::recvData()
{
  QByteArray recvMsg = readAll();

  int index = recvMsg.indexOf('\n');
  recvMsg.remove(index,recvMsg.size() - index);
  QString recvStr = QString::fromUtf8(recvMsg);

//  qDebug()<<"recv:"<<recvStr;

  //构建JSON对象
  QJsonObject json = QstringToJson(recvStr);
  //Json转QMap
  QVariantMap map = json.toVariantMap();

  code = map["code"].toInt();
  msg = map["msg"].toString();


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

    }else if(code == GetShowInfo){
            //获取所有靶的信息
            QJsonValue jsonValue = map["data"].toJsonValue();

            QJsonArray jsonArray = jsonValue.toArray();

            emit mySignalUpdateHoles(jsonArray);
            //获取单个靶的信息
            int msgSize = jsonArray.size(),addr = -1;
            if(msgSize > 0)
              {
                QJsonObject s_jsonObject = jsonArray[0].toObject();
                addr = s_jsonObject["addr"].toInt();
              }
            if(s_index == addr)
              emit mySignalOnlyTarget(jsonArray);

    }else if(code == GetVoltage){
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

    }else if(code == GetTargetInfo){

      QJsonValue jsonValue = map["data"].toJsonValue();

      QJsonArray jsonArray = jsonValue.toArray();

      emit mySignalGradeData(jsonArray);

//      QList<QList<QString>> onlyHolesList;
//      QList<QString> onlyList;
//      for(int i = 0;i < num;i++)
//        {

//          onlyList.append(QString::number(jsonValue[i]["addr"].toInt(),10));

//          onlyList.append(QString::number(jsonValue[i]["group_number"].toDouble()));
//          onlyList.append(jsonValue[i]["user_name"].toString());
//          onlyList.append(QString::number(jsonValue[i]["cylinder_number"].toInt(),10));
//          onlyHolesList.append(onlyList);
//        }

//    }
}
}

void MySocket::closeSocket()
{
  close();
}

//请求靶标信息
void MySocket::updateHoles()
{
  for(int i = 1;i < array_size;i++)
    {
      if(vecState[i] != 0)
        {
            sendHoles(vecState[i]);
        }
    }
}

//分组控制信息
void MySocket::groupNumber(QString indexZuHao)
{
  group_number = indexZuHao.toInt();
  QVariantList varList = toJsonData("group_number",UserGrouping,group_number,true);

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"分组指令已发送:"<<data;

}

void MySocket::sendYuanXin(int old_addr, int new_addr)
{
  QVariantList varList;

  QVariantMap var;
  var.insert("code", RewriteTargetId);
  QVariantMap var1;

  var.insert("msg", var1);
  QVariantMap var2;

  var2.insert("old_addr",old_addr);
  var2.insert("new_addr",new_addr);

  var.insert("data", var2);

  varList << var;

  QByteArray data = mapToByteArry(varList);

 sendData(data);

 qDebug()<<"编码设置指令已发送:"<<data;
}

void MySocket::sendBegin(int flag)
{
  QVariantList varList = toJsonData("addr",OpenCalibrationTargetById,flag,true);

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"开始校准指令已发送:"<<data;
}

void MySocket::sendOver(int flag)
{
  QVariantList varList = toJsonData("addr",CloseCalibrationTargetById,flag,true);

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"结束指令已发送:"<<data;
}

void MySocket::searchData(int fenZu, int baHao, QString time)
{
  QVariantList varList;

  QVariantMap var;
  var.insert("code", GetTargetInfo);
  QVariantMap var1;
  var1.insert("date",time);

  var.insert("msg", var1);
  QVariantMap var2;

  var2.insert("addr",baHao);
  var2.insert("group_number",fenZu);

  var.insert("data", var2);

  varList << var;

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"编码设置指令已发送:"<<data;
}

void MySocket::sendHoles(int msg)
{
  QVariantList varList;

  QVariantMap var;
  var.insert("code", GetShowInfo);
  QVariantMap var1;

  QDate m_date = QDate::currentDate();
  QString currentDate = m_date.toString("yyyy-MM-dd");
  var1.insert("date",currentDate);

  var.insert("msg", var1);
  QVariantMap var2;

  var2.insert("addr",msg);
  var2.insert("group_number",group_number);

  var.insert("data", var2);

  varList << var;

  QByteArray data = mapToByteArry(varList);

  sendData(data);
}

void MySocket::updateIndex(int msg)
{
  s_index = msg + 1;
}







