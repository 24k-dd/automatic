#ifndef API_H
#define API_H

#include "myserver.h"

#include<QByteArray>

inline QByteArray sendGroupNumberApi(int groupNumber)
{
  return sendGroupNumber(groupNumber);
}

inline QByteArray sendYuanXinApi(int old_addr, int new_addr)
{
  return sendYuanXin(old_addr,new_addr);
}

inline QByteArray sendBeginApi(int flag)
{
  return sendBegin(flag);
}

inline QByteArray sendOverApi(int flag)
{
  return sendOver(flag);
}

inline QByteArray sendSearchDataApi(int fenZu, int baHao, QString time)
{
  return sendSearchData(fenZu,baHao,time);
}

inline QByteArray sendHolesApi(int msg,int group_number)
{
  return sendHoles(msg,group_number);
}

inline QByteArray requestStateApi()
{
  return requestState();
}

inline QByteArray requestBatteryApi()
{
  return requestBattery();
}

inline QByteArray requestClearAllApi()
{
  return requestClearAll();
}

inline QByteArray requestClearOnlyApi(int index2)
{
  return requestClearOnly(index2);
}

inline QList<int> getStateApi(QList<int> vecState,const QVariantMap &map)
{
  return getState(vecState,map);
}


inline QVector<Check_Target_Table> getShowInfoApi(const QVariantMap &map)
{
  return getShowInfo(map);
}


inline QVector<Target_Info_Table> getTargetInfoApi(const QVariantMap &map)
{
  return getTargetInfo(map);
}

inline QVector<double> getvecBatteryApi(const QVariantMap &map)
{
  return getvecBattery(map);
}

inline QByteArray openInfoApi()
{
  return openInfo();
}

inline QByteArray closeInfoApi()
{
  return closeInfo();
}

inline QByteArray bindInfoApi(int addr,QString name,QString idCard)
{
  return bindInfo(addr,name,idCard);
}

#endif // API_H

