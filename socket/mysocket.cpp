#include "mysocket.h"

MySocket::MySocket(QObject *parent)
  : QTcpSocket(parent)
{
    QString Ip = "127.0.0.1";
//  QString Ip = "192.168.43.191";
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
}

//void MySocket::tryConnect()
//{
//  //  abort();
//  //  connectToHost(QHostAddress(Ip),Port);
//  //  if(waitForConnected())
//  //    {
//  //      qDebug() << "connect success";
//  //      return true;
//  //    }else{
//  //      qDebug() << "connect failed";
//  //      return false;
//  //    }
//}

void MySocket::sendData(QString msg)
{
  write(msg.toUtf8().data());
  //  qDebug()<<"send:"<<msg;
}

void MySocket::recvData()
{
  QByteArray recvMsg = readAll();

  QString recvStr = QString::fromUtf8(recvMsg);
  qDebug()<<"recv:"<<recvStr;


  //构建JSON对象
  QJsonObject json = QstringToJson(recvStr);
  //Json转QMap
  QVariantMap map = json.toVariantMap();

  code = map["code"].toInt();
  msg = map["msg"].toString();



  if(code == 2000){
      QMap<QString, QVariant> map1 = map["data"].toMap();
      QMap<QString, QVariant>::iterator it = map1.begin();
      QVector<int> vec(21,1);
      while(it != map1.end())
        {
          vec[it.key().toInt()] = it.value().toInt();
        }
      emit mySignalState(vec);
      //    qDebug()<<code<<vec;

    }else if(code == GetShowInfo){

      QJsonValue jsonValue = map["data"].toJsonValue();

      int num = jsonValue.toArray().size();

      QList<QList<QString>> onlyHolesList;
      QList<QString> onlyList;

      //t1 = new TableOne[num];
      for(int i = 0;i < num;i++)
        {
          //          t1[i].id = jsonValue[i]["id"].toInt();
          //          t1[i].addr = jsonValue[i]["addr"].toInt();
          onlyList.append(jsonValue[i]["addr"].toString());
          //          t1[i].x = jsonValue[i]["x"].toDouble();
          onlyList.append(jsonValue[i]["x"].toString());
          //          t1[i].y = jsonValue[i]["y"].toDouble();
          onlyList.append(jsonValue[i]["y"].toString());
          //          t1[i].cylinder_number = jsonValue[i]["cylinder_number"].toInt();
          onlyList.append(jsonValue[i]["cylinder_number"].toString());
          //          t1[i].direction =  jsonValue[i]["direction"].toInt();
          onlyList.append(jsonValue[i]["direction"].toString());

          onlyList.append(jsonValue[i]["user_name"].toString());

          onlyList.append(jsonValue[i]["identification_number"].toString());

          onlyHolesList.append(onlyList);


        }

      emit mySignalUpdateHoles(onlyHolesList);
      //      qDebug()<<code<<onlyHolesList;
    }else if(code == GetVoltage){
      QMap<QString, QVariant> map1 = map["data"].toMap();
      QMap<QString, QVariant>::iterator it = map1.begin();
      QVector<double> vec(21,1);
      while(it != map1.end())
        {
          vec[it.key().toInt()] = it.value().toInt();
        }
      emit mySignalBattery(vec);
      //      qDebug()<<code<<vec;
    }else if(code == GetTargetInfo){

      QJsonValue jsonValue = map["data"].toJsonValue();

      int num = jsonValue.toArray().size();

      QList<QList<QString>> onlyHolesList;
      QList<QString> onlyList;
      for(int i = 0;i < num;i++)
        {

          onlyList.append(jsonValue[i]["addr"].toString());
          onlyList.append(jsonValue[i]["GroupNumber"].toString());
          onlyList.append(jsonValue[i]["user_name"].toString());
          onlyList.append(jsonValue[i]["cylinder_number"].toString());
          onlyHolesList.append(onlyList);
        }
      emit mySignalGradeData(onlyHolesList);
    }
}

void MySocket::closeSocket()
{
  close();
}


//void MySocket::passGroupNumber(int fenZu, int baHao, QString time)
//{
//  group = fenZu;
//  number = baHao;
//  m_time = time;
//}






