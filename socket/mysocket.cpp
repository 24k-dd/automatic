#include "mysocket.h"

MySocket::MySocket(QObject *parent)
  : QTcpSocket(parent)
{
  for(int i = 0;i < array_size;i++)
    {
      vecState.push_back(0);
    }
  //  QString Ip = "192.168.4.2";
  QString Ip = "127.0.0.1";
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

      //请求已连接状态的靶标信息
      updateHoles();

      //      recvData();

    });

}

void MySocket::sendData(QString msg)
{
  //发送信息
  write(msg.toUtf8().data());
}

void MySocket::recvData()
{


  //   QByteArray ba = readAll();
  //      if(ba.size() == 0)
  //          return ;
  //      log_Printf("recv", ba.toHex()); //十六进制打印接收到的数据
  //      recvAllMsg.append(ba);

  //      int length = recvAllMsg.left(20).right(4).toHex().toInt(nullptr, 16); //从接收的数据中解读出数据的长度

  //      if(length > recvAllMsg.size())
  //          return ; //表示未完全接收
  //      else {
  //          ba = recvAllMsg.left(length); //将解读好的数据放入处理缓存中
  //          recvAllMsg = recvAllMsg.right(recvAllMsg.size() - length); //删除已经解读好的数据
  //      }
  QByteArray recvAllMsg = read(1024);
  int msgSize = recvAllMsg.size();

  while(true)
    {
      if(!recvAllMsg.contains('\n'))
        {
          recvAllMsg += read(1024);
        }else
        {
          break;
        }
    }

  int index = recvAllMsg.indexOf('\n');

  recvAllMsg.remove(index,recvAllMsg.size() - index);

  qDebug()<<"接收数据大小:"<<recvAllMsg.size();

  qDebug()<<"recvAllMsg:"<<recvAllMsg;

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

      emit mySignalGradeData(jsonArray);
    }
  recvAllMsg.clear();
  //    }
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

//bool MySocket::readMessage()
//{
//  while(!recvAllMsg.contains('\n'))
//    {
//      recvAllMsg += readAll();
//      if(recvAllMsg.contains('\n'))
//        {
//          int index = recvAllMsg.indexOf('\n');
//          recvAllMsg.remove(index,recvAllMsg.size() - index);
//           qDebug()<<"recvAllMsg:"<<recvAllMsg;
//          return true;
//        }
//    }
//  return false;


//}

//分组控制信息
void MySocket::sendGroupNumber(QString indexZuHao)
{
  group_number = indexZuHao.toInt();
  QVariantList varList = toJsonData("group_number",UserGrouping,group_number,true);

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"分组指令已发送:"<<data;

}

//更改编号控制信息
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

//开始校准控制信息
void MySocket::sendBegin(int flag)
{
  QVariantList varList = toJsonData("addr",OpenCalibrationTargetById,flag,true);

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"开始校准指令已发送:"<<data;
}

//结束校准控制信息
void MySocket::sendOver(int flag)
{
  QVariantList varList = toJsonData("addr",CloseCalibrationTargetById,flag,true);

  QByteArray data = mapToByteArry(varList);

  sendData(data);

  qDebug()<<"结束指令已发送:"<<data;
}

//查询数据
void MySocket::sendSearchData(int fenZu, int baHao, QString time)
{
  QVariantList varList;

  QVariantMap var;
  var.insert("code", GetShowInfo);
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

//请求靶号
void MySocket::sendHoles(int msg)
{
  QVariantList varList;

  QVariantMap var;
  var.insert("code", GetTargetInfo);
  QVariantMap var1;

  QDate m_date = QDate::currentDate();
  QString currentDate = m_date.toString("yyyy-MM-dd");
  var1.insert("date",currentDate);

  var.insert("msg", var1);
  QVariantMap var2;

  var2.insert("addr",msg);
  //  qDebug()<<"addr:"<<msg;
  var2.insert("group_number",group_number);

  var.insert("data", var2);

  varList << var;

  QByteArray data = mapToByteArry(varList);

  sendData(data);
}

//更新当前所选中的靶标
void MySocket::updateIndex(int msg)
{
  s_index = msg + 1;
}







