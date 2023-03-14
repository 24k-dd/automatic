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
#include<QVector>

using namespace std;

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

//状态电量请求间隔
const int state_time = 5000;

//靶标请求间隔
const int holes_time = 1000;

//靶标数目
const int array_size = 21;

//标签缩小比例
const double label_scaleBody = 0.0857;

//靶标大小
const int label_img = 801;

//0 1表示未连接 2表示校准中 3表示已连接
const int flag_0 = 0,flag_1 = 1,flag_2 = 2,flag_3 = 3;



//map转字节数组
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

//转为json格式数据
inline QVariantList toJsonData(QString strm,int code,int addr,bool flag)
{

  QVariantList varList;
  QVariantMap var;
  var.insert("code", code);
  QVariantMap var1;
  var.insert("msg", var1);
  QVariantMap var2;

  if(flag == true)
    {
      var2.insert(strm,addr);
    }
  var.insert("data", var2);
  varList << var;
  return varList;
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

#endif // MODEL_H
