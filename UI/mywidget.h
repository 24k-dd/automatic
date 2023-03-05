#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QString>
#include<QProgressBar>
#include<QLabel>
#include<QListWidgetItem>
#include<QPointF>
#include <QTimer>
#include <windows.h>
#include<QPushButton>
#include<QMessageBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSpacerItem>

#include "targetsheettwo.h"
#include"mylistwidget.h"
#include"mytablewidget.h"
#include"api/Model.h"


class MyWidget : public QWidget
{
  Q_OBJECT
signals:
  mySignalBtn();
  mySignalFlag();

  mySignal(QList<QPointF> msg);
public:
  explicit MyWidget(QWidget *parent = nullptr);
  ~MyWidget();

  void create();


  void closeEvent(QCloseEvent *event);


public slots:

  void getIndex(int msg);

  void clearBtn();

  //获取数据库表1数据
  void passHolesData(QList<QList<QString>> msg);

  void passBatteryData(QVector<double> msg);

private:

  TargetSheetTwo  *targetSheetTwo = NULL;
  MyTableWidget *myTable = NULL;


  //姓名
    QLabel *labelName = NULL;
  //靶号
  QLabel *labelBaHao = NULL;
  //总环数
  QLabel *labelSum = NULL;
  //电量
  QLabel *labelBattery = NULL;

  //中弹数
  QLabel *zhongDanShu = NULL;

  //清除按钮
  QPushButton *clearButton = NULL;

  int index = 4;

  bool flag = true;


  TableOne *t1 = NULL;
  TableTwo *t2 = NULL;
  int current_cnt1 = 0;
  int current_cnt2 = 0;

};

#endif // MAINWINDOW_H
