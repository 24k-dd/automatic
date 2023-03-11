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
  mySignal(QList<QPointF> msg);
  mySignalDoubleIndex(int msg);
mySignalIndex(int msg);

public slots:
  //获取数据库表1数据
  void passHolesData(QJsonArray msg);

  void passBatteryData(QVector<double> msg);

  //显示详细信息
  void listWidgetDoubleClicked(QListWidgetItem *item);

  //添加选中阴影
  void listWidgeSelectionChanged(QListWidgetItem* item);

public:
  double screenWidth;
  double labelXY = 801;
  double currentWidth = 1;
  double scaleBody = 1;

  int targetShu = 20;

  QList<int> list;

  OneWidget *oneWidget[20];

  QListWidgetItem *item[20];


  QTimer m_Timer;

  int s_index = 1;//详细信息界面序号

  int index2 = -1;

  int index3 = -2;


};

#endif // MYLISTWIDGET_H
