#ifndef ONEWIDGET_H
#define ONEWIDGET_H

#include <QWidget>

#include<QVBoxLayout>
#include<QSpacerItem>
#include<QList>
#include<QPointF>


#include"targetsheet.h"
#include"Model.h"

class OneWidget :public QWidget
{
  Q_OBJECT

public:
  explicit OneWidget(double size,int index,QWidget *parent = nullptr);

  //创建布局
  void create(double labelXY);

  //实时更新大小
  void setSize(double width);

  void getMySignal();
private slots:


signals:

  mySignal(double);

  mySignalHoles(QList<QPointF>  msg);


private:
  TargetSheet *targetSheet;

  QTimer m_Timer;

  int c_index = 1;

  double scaleBody = 1;

  double currentWidth = 1;

  int targetShu = 20;

public:
  QList<QPointF>   onlyHoleList = {};

  QLabel *labelSum;
  QLabel *labelState;

};

#endif // ONEWIDGET_H
