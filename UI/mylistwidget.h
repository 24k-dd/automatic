#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>
#include<QWheelEvent>

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

  //滚轮放缩事件
  void wheelEvent(QWheelEvent *event);



signals:
  mySignal(QList<QPointF> msg);


public slots:
  //获取数据库表1数据
  void passHolesData(QList<QList<QString>> msg);

  void passStateData(QVector<int> msg);
  void passBatteryData(QVector<double> msg);

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

  //  TableOne *t1 = NULL;
  //  TableTwo *t2 = NULL;

  //  //  int before_cnt1 = 0;
  //  //  int before_cnt2 = 0;
  //  int current_cnt1 = 0;
  //  int current_cnt2 = 0;


};

#endif // MYLISTWIDGET_H
