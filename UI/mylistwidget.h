#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include<QWheelEvent>
#include<QJsonObject>
#include"onewidget.h"


class MyListWidget : public QListWidget
{
  Q_OBJECT

public:
  explicit MyListWidget(QListWidget *parent = nullptr);
  ~MyListWidget();

  //界面布局
  void create();

  //初始化列表
  void initListWidget();

  int getIndex();

  //滚轮放缩事件
  void wheelEvent(QWheelEvent *event);



signals:
  mySignalDoubleIndex(int msg);
  mySignalIndex(int msg);

public slots:
  //传递子弹数据
  void passHolesData(const QVector<Target_Info_Table> &data);

  //传递电量数据
  void passBatteryData(QVector<double> msg);

  void passStateData(QVector<int> vecState);

  //显示详细信息
  void listWidgetDoubleClicked(QListWidgetItem *item);

  //添加选中阴影
  void listWidgeSelectionChanged(QListWidgetItem* item);

private:
  double screenWidth;
  double labelXY = 801;
  double currentWidth = 1;
  double scaleBody = 1;



  OneWidget *oneWidget[20];

  QListWidgetItem *item[20];


  int s_index = 1;//详细信息界面序号

  int index2 = -2;

  int index3 = -3;


};

#endif // MYLISTWIDGET_H
