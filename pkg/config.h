#ifndef CONFIG_H
#define CONFIG_H

#include<QProcess>
#include<QVariantList>
#include<QJsonArray>
#include<QJsonDocument>
#include<QByteArray>
#include<QApplication>
#include<QJsonObject>
#include<QVector>
#include<QDataStream>

#include"Model.h"

//转为json格式数据
inline QByteArray structToJson(const Send_Info &sendDataInfo)
{
  QJsonObject jsonObject;
  jsonObject["code"] = sendDataInfo.code;
  QJsonObject jo1;
  for(auto it = sendDataInfo.msg.begin();it != sendDataInfo.msg.end();++it)
    jo1[it.key()] = it.value();
  jsonObject["msg"] = jo1;
  QJsonObject jo2;
  for(auto it = sendDataInfo.data.begin();it != sendDataInfo.data.end();++it)
    jo2[it.key()] = it.value();
  jsonObject["data"] = jo2;

  QJsonDocument jsonDocu(jsonObject);
  QString jsonStr = jsonDocu.toJson();

  jsonStr.replace("\n","");
  jsonStr.replace(" ","");
  jsonStr.append('\n');

  QByteArray sendData = jsonStr.toUtf8();
  return sendData;
}

//字符串转json格式数据
inline QJsonObject QstringToJson(QString jsonString)
{
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
  if(jsonDocument.isNull())
    {
      //      qDebug()<< "String NULL"<< jsonString.toLocal8Bit().data();
    }
  QJsonObject jsonObject = jsonDocument.object();
  return jsonObject;
}

//json格式转字符串
inline QString JsonToQstring(QJsonObject jsonObject)
{
  return QString(QJsonDocument(jsonObject).toJson());
}




#endif // CONFIG_H
