#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include<QWidget>
#include<QListWidgetItem>
#include<qDebug>
#include<QTcpSocket>
#include<QComboBox>
#include<QHostAddress>
#include<QMessageBox>
#include<QVBoxLayout>
#include<QPushButton>
#include<QThread>
#include<QDockWidget>
#include<QNetworkProxy>
#include<QProcess>
#include <QListWidget>
#include<QList>
#include<QMouseEvent>
#include<QCloseEvent>
#include<QToolBar>
#include<QAction>
#include<QRect>
#include<QToolButton>
#include<QSpacerItem>


#include"mylistwidget.h"
#include"targetsheet.h"
#include"mywidget.h"
#include"QDialog"
#include"onewidget.h"
#include"winUser.h"
#include<windows.h>
#include<tlhelp32.h>
#include<comdef.h>
#include"socket/mysocket.h"
#include "mycodesetwidget.h"
#include "checkcodewidget.h"
#include "mypeoplewidget.h"
#include "mygradetablewidget.h"


class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  create();

  //请求连接状态
  void updateState();

  //请求电量
  void updateBattery();

signals:
  void mySignal(int msg); //自定义信号函数,msg参数可以省略


private slots:
  void clearall_clicked();

  void clearonly_clicked();

  void codeset_clicked();

  void calib_clicked();

  void people_clicked();

  void grade_clicked();

  void close_clicked();

  void sendYuanXin(int old_addr,int new_addr);//编码设置

  void sendBegin(int flag);//下一个

  void sendOver(int flag);//结束

  void searchData(int fenZu,int baHao,QString time);

  void clearBtn();

  void groupNumber(QString indexZuHao);

  //显示详细信息
  void listWidgetDoubleClicked(QListWidgetItem *item);

  //添加选中阴影
  void listWidgeSelectionChanged(QListWidgetItem* item);

  void passStateData(QVector<int> msg);

private:

  MySocket *mySocket = NULL;

  MyListWidget *myListWidget = NULL;


  int index;//详细信息界面序号

  int index2 = -1;

  int index3 = -2;

public:
    //屏幕宽度
    double nWidth;

    double nHeight;

public:
  QListWidget *listWidget = NULL;
  QToolBar *toolBar = NULL;
  QToolButton *act[6];


public:
  bool m_flag = true;

  QTimer m_Timer;

public slots:
    void updateFlag();

};

#endif // MAINVIEW_H
