#ifndef CHECKCODEWIDGET_H
#define CHECKCODEWIDGET_H

#include <QWidget>

#include<QMessageBox>
#include<QFile>
#include<QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonValue>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QSpacerItem>
#include<QLabel>
#include<QPushButton>
#include<QApplication>
#include<QProcess>
#include"windows.h"
#include"shellapi.h"
#include"Winbase.h"

class CheckCodeWidget : public QWidget
{
  Q_OBJECT

public:
  explicit CheckCodeWidget(QWidget *parent = nullptr);

  //关闭窗口时传递信号
  void closeEvent(QCloseEvent *event);

  void create();

private slots:
  //获取QListWidget的当前id
  void getCurrentIndex(int index);

  //按钮1
  void btn1Slots();
  //按钮2
  void btn2Slots();

signals:
  //
  void mySignalBegin(int flag); //自定义信号函数,msg参数可以省略

  void mySignalOver(int flag);

  void mySignalFlag();

private:

  int flag = 1;

  QLineEdit *lineEdit;

  QPushButton *btn1;

  QPushButton *btn2;


};

#endif // CHECKCODEWIDGET_H
