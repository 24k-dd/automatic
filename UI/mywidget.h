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

#include "targetsheet.h"
#include"mylistwidget.h"
#include"mytablewidget.h"
#include"model/Model.h"


class MyWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MyWidget(int index2,QWidget *parent = nullptr);
  ~MyWidget();

  void create();


  void closeEvent(QCloseEvent *event);

signals:
  mySignalBtn();
  mySignalFlag();

  mySignal(QList<QPointF> msg);
public slots:

  void getIndex(int msg);

  void clearBtn();

  //获取数据库表1数据
  void passHolesData(const QVector<Target_Info_Table> &data);

  void passBatteryData(const QVector<double> &msg);

private:

  TargetSheet *targetSheet = NULL;
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

  int index = 4,s_index = 0;

  QString user_name = "";

  int addr = 0;

};

#endif // MAINWINDOW_H
