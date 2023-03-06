#ifndef MODEL_H
#define MODEL_H
#include<QString>
#include<QProcess>
#include<QVariantList>
#include<QJsonArray>
#include<QJsonDocument>
#include<QByteArray>
#include<QApplication>
#include<QJsonObject>

typedef struct tableOne{

  int addr;
  double x;
  double y;
  int cylinder_number;
  int direction;
  QString user_name;
  QString identification_number;
}TableOne;
Q_DECLARE_METATYPE(TableOne)

typedef struct tableTwo{
  int id;
  int addr;
  QString user_name;
  QString identification_number;
  int is_delete;
}TableTwo;

Q_DECLARE_METATYPE(TableTwo)

// 控制命令接口路由值 10000-19999
// RewriteTargetId 重写地址
const int RewriteTargetId = 10000;
// ClearTarget 清除靶标
const int 	ClearTarget = 10001;
// OpenCalibrationTargetById 开启校准
const int OpenCalibrationTargetById = 10002;
// CloseCalibrationTargetById 关闭校准
const int CloseCalibrationTargetById = 10003;
// OpenInfoEntry 打开信息录入
const int OpenInfoEntry = 10004;
// CloseInfoEntry 关闭信息录入
const int CloseInfoEntry = 10005;
// UserGrouping 配置分组
const int UserGrouping = 10006;


// 获取信息接口路由值 20000-29999
// GetTargetInfo 获取
const int    GetTargetInfo = 20000;
// GetTargetState 获取靶标状态
const int    GetTargetState = 20001;
// GetShowInfo 获取展示信息
const int    GetShowInfo = 20002;
// GetVoltage 获取电压
const int    GetVoltage = 20003;





inline QByteArray mapToByteArry(QVariantList varList)
{
  QJsonArray jsonArray = QJsonArray::fromVariantList(varList);
  QJsonDocument jsonDoc(jsonArray);

  QByteArray json = jsonDoc.toJson();


  QString str = json;
  str.replace("\n","");
  str.replace(" ","");
  str.replace("[","");
  str.replace("]","");
  str.append('\n');

  QByteArray sendData = str.toUtf8();
  return sendData;
}

//运行main程序
inline void runMain()
{

  QString  strm = QApplication::applicationDirPath();
  strm += "/main.exe";

  strm.replace("/","\\");

  if (QProcess::startDetached(strm))
    qDebug()  <<"main Running...";
  else
    qDebug()  <<"mian Running Failed";

}

//终止main程序
inline void stopMain()
{
  // 通过进程名字结束进程
  QProcess::startDetached("taskkill -t  -f /IM " + QString("main.exe"));
  QProcess::startDetached("taskkill -t  -f /IM " + QString("main.exe"));
  QProcess::startDetached("taskkill -t  -f /IM " + QString("main.exe"));
}


inline QVariantList toJsonData(QString strm,int code,int addr,bool flag)
{

  QVariantList varList;

  QVariantMap var;
  var.insert("code", code);
  QVariantMap var1;

  var.insert("msg", var1);
  QVariantMap var2;

  //  var2.insert("group_number",-1);

  if(flag == true)
    {
      var2.insert(strm,addr);
    }

  var.insert("data", var2);


  varList << var;
  return varList;
}


inline QJsonObject QstringToJson(QString jsonString)
{
  QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
  if(jsonDocument.isNull())
    {
      qDebug()<< "String NULL"<< jsonString.toLocal8Bit().data();
    }
  QJsonObject jsonObject = jsonDocument.object();
  return jsonObject;
}

inline QString JsonToQstring(QJsonObject jsonObject)
{
  return QString(QJsonDocument(jsonObject).toJson());
}





#endif // MODEL_H
