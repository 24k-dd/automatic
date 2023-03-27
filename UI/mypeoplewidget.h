#ifndef MYPEOPLEWIDGET_H
#define MYPEOPLEWIDGET_H

#include <QWidget>
#include<qDebug>
#include<QPushButton>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QLabel>
#include<QFile>
#include<QApplication>
#include<QDate>
#include<QByteArray>
#include<QDir>
#include<QTimer>
#include<QStandardPaths>
#include<QLibrary>

class MyPeopleWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MyPeopleWidget(QWidget *parent = nullptr);

  void closeEvent(QCloseEvent *event);
  void readText();
  void writeText();

  void create();

  bool infoEntry();

  bool deleteFile(const QString &strPath);
signals:
  void mySignalZuHao(QString msg); //自定义信号函数,msg参数可以省略

  void mySignalFlag();

  //开始信息录入
  void openInfo(); //自定义信号函数,msg参数可以省略

  //结束信息录入
  void closeInfo();

  void mySignalInfo(QString name,QString idCard);

private slots:
  void btn_clicked();

  //开始校准
  void btn1Slots();

  //结束
  void btn2Slots();


private:

  QPushButton *btn1;

  QPushButton *btn2;

  QVector<QString> vecIdCard;

  QTimer m_Timer;
  QPushButton *btn;
  QLineEdit *lineEdit;
  QLineEdit *lineEditTip;

  QString zuhao;

  QFile file;

  QDate m_date;
  QString currentDate;
};


#endif // MYPEOPLEWIDGET_H
