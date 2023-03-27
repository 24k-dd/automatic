#ifndef MYSERVER_H
#define MYSERVER_H

#include "Model.h"

#include"config.h"

#include<QMap>
#include<QVector>
#include<QVariant>
#include<QVariantMap>

inline QByteArray sendGroupNumber(int groupNumber)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = UserGrouping;
  sendDataInfo.data.insert("group_number",groupNumber);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray sendYuanXin(int old_addr, int new_addr)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = RewriteTargetId;
  sendDataInfo.data.insert("old_addr",old_addr);
  sendDataInfo.data.insert("new_addr",new_addr);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray sendBegin(int flag)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = OpenCalibrationTargetById;
  sendDataInfo.data.insert("addr",flag);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray sendOver(int flag)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = CloseCalibrationTargetById;
  sendDataInfo.data.insert("addr",flag);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray sendSearchData(int fenZu, int baHao, QString time)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = GetShowInfo;
  sendDataInfo.msg.insert("date",time);
  sendDataInfo.data.insert("addr",baHao);
  sendDataInfo.data.insert("group_number",fenZu);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray sendHoles(int msg,int group_number)
{
  QDate m_date = QDate::currentDate();
  QString currentDate = m_date.toString("yyyy-MM-dd");

  Send_Info sendDataInfo;
  sendDataInfo.code = GetTargetInfo;
  sendDataInfo.msg.insert("date",currentDate);
  sendDataInfo.data.insert("addr",msg);
  sendDataInfo.data.insert("group_number",group_number);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray requestState()
{
  Send_Info sendDataInfo;
  sendDataInfo.code = GetTargetState;
  QByteArray dataState = structToJson(sendDataInfo);
  return dataState;
}

inline QByteArray requestBattery()
{
  Send_Info sendDataInfo;
  sendDataInfo.code = GetVoltage;
 QByteArray dataBattery  = structToJson(sendDataInfo);
  return dataBattery;
}

inline QByteArray requestClearAll()
{
  Send_Info sendDataInfo;
  sendDataInfo.code = ClearTarget;
  sendDataInfo.data.insert("addr",-1);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray requestClearOnly(int index2)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = ClearTarget;
  sendDataInfo.data.insert("addr",index2);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray openInfo()
{
  Send_Info sendDataInfo;
  sendDataInfo.code = OpenInfoEntry;
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QByteArray closeInfo()
{
  Send_Info sendDataInfo;
  sendDataInfo.code = CloseInfoEntry;
  QByteArray data = structToJson(sendDataInfo);
  return data;
}

inline QList<int> getState(QList<int> vecState,const QVariantMap &map)
{
  for(int i = 0;i < array_size;i++)
    {
      vecState[i] = 1;
    }
  QMap<QString, QVariant> map1 = map["data"].toMap();

  QMap<QString, QVariant>::iterator it = map1.begin();

  while(it != map1.end())
    {

      vecState[it.key().toInt()] = it.value().toInt();
      it++;
    }
  return vecState;
}

inline QVector<Check_Target_Table> getShowInfo(const QVariantMap &map)
{
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
  return checkInfo;
}

inline QVector<double> getvecBattery(const QVariantMap &map)
{
  QMap<QString, QVariant> map1 = map["data"].toMap();
  QMap<QString, QVariant>::iterator it = map1.begin();

  QVector<double> vecBattery(array_size,0);
  while(it != map1.end())
    {
      int addr = it.key().toInt();
      vecBattery[addr] = it.value().toDouble();
      it++;
    }
  return vecBattery;
}

inline QVector<Target_Info_Table> getTargetInfo(const QVariantMap &map)
{
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
  return targetInfo;
}


inline QByteArray bindInfo(int addr,QString name,QString idCard)
{
  Send_Info sendDataInfo;
  sendDataInfo.code = BindInfo;

  sendDataInfo.msg.insert("user_name",name);
  sendDataInfo.msg.insert("identification_number",idCard);
    sendDataInfo.data.insert("addr",addr);
  QByteArray data = structToJson(sendDataInfo);
  return data;
}


#endif // MYSERVER_H
