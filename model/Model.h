#ifndef MODEL_H
#define MODEL_H

#include<QString>
#include <QMetaType>

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

//状态电量请求间隔ms
const int state_time = 5000;

//靶标请求间隔
const int holes_time = 1000;

//画布刷新间隔
const int paint_time = 300;

//靶标数目
const int array_size = 21;

//标签缩小比例
const double label_scaleBody = 0.0857;

//靶标大小
const int label_img = 801;

//0 1表示未连接 2表示校准中 3表示已连接 4表示电量过低
const int flag_0 = 0,flag_1 = 1,flag_2 = 2,flag_3 = 3,flag_4 = 4;

typedef struct Target_Info_Table
{
  int addr;
  double x;
  double y;
  int cylinder_number;
  int direction;
  QString user_name;
}targetInfoTable;
Q_DECLARE_METATYPE(Target_Info_Table)

typedef struct Check_Target_Table
{
  int addr;
  int group_number;
  int cylinder_number;
  QString user_name;

}checkInfoTable;
Q_DECLARE_METATYPE(Check_Target_Table)

//发送信息格式
typedef struct Send_Info{
 int code;
 QMap<QString,QString> msg;
 QMap<QString,int> data;
}sendInfo;



#endif // MODEL_H
