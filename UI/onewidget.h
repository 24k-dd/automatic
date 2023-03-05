#ifndef ONEWIDGET_H
#define ONEWIDGET_H

#include <QWidget>

#include<QVBoxLayout>
#include<QSpacerItem>
#include<QList>
#include<QPointF>


#include"targetsheet.h"

class OneWidget :public QWidget
{
  Q_OBJECT

public:
  explicit OneWidget(double size,int index,QWidget *parent = nullptr);

  //创建布局
  void create(double labelXY);

  //实时更新大小
  void setSize(double width);

private slots:


signals:

  mySignal(double);

  mySignalHoles(QList<QPointF>  msg);
  //获取数据库表1数据

public:
  TargetSheet *targetSheet;

  QLabel *labelSum;
  QLabel *labelState;

//  TableOne *t1 = NULL;
//  TableTwo *t2 = NULL;


  QTimer m_Timer;

  int current_cnt1 = 0;
  int current_cnt2 = 0;

  int c_index = 1;

  double scaleBody = 1;

  double currentWidth = 1;

    int targetShu = 20;

};

#endif // ONEWIDGET_H
