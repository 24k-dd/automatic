#ifndef MYPEOPLEINFO_H
#define MYPEOPLEINFO_H


#include <QWidget>
#include<QFileInfo>
#include<QMessageBox>
#include<QFile>
#include<QLibrary>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QSpacerItem>
#include<QLabel>
#include<QPushButton>
#include<QApplication>
#include<QProcess>
#include<qDebug>
#include <QStandardPaths>
#include<QTimer>
#include<QDir>



#include"windows.h"
#include"shellapi.h"
#include"Winbase.h"

class MyPeopleInfo : public QWidget
{
  Q_OBJECT

public:
  explicit MyPeopleInfo(QWidget *parent = nullptr);

  //关闭窗口时传递信号
  void closeEvent(QCloseEvent *event);

  void create();

  bool infoEntry();

  bool deleteFile(const QString &strPath);

private slots:


  //开始校准
  void btn1Slots();

  //结束
  void btn2Slots();

signals:
  //开始信息录入
  void openInfo(); //自定义信号函数,msg参数可以省略

  //结束信息录入
  void closeInfo();

  void mySignalFlag();

  void mySignalInfo(QString name,QString idCard);

private:

  QPushButton *btn1;

  QPushButton *btn2;

  QVector<QString> vecIdCard;

  QTimer m_Timer;



};



#endif // MYPEOPLEINFO_H
