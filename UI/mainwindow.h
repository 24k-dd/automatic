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

  void create();

  //请求连接状态和电量
  void updateStateAndBattery();

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

  void doubleClicked(int msg);

  //只允许同时打开一个界面
  void updateFlag();

private:

  MySocket *mySocket = NULL;

  MyListWidget *myListWidget = NULL;

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


  QVector<int> vecState;

  int group_number = -1;

public:
  bool m_flag = true;

  QTimer m_Timer;

public slots:


};

#endif // MAINVIEW_H
