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

class MyPeopleWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MyPeopleWidget(QWidget *parent = nullptr);

      void closeEvent(QCloseEvent *event);
         void readText();
                  void writeText();

                  void create();
signals:
    void mySignalZuHao(QString msg); //自定义信号函数,msg参数可以省略

          void mySignalFlag();


private slots:
  void btn_clicked();

private:
  QPushButton *btn;
  QLineEdit *lineEdit;
    QLineEdit *lineEditTip;
  QHBoxLayout *layout;
  QSpacerItem *h_spacer;
  QString zuhao;

  QFile file;

  QDate m_date;
  QString currentDate;

  int flag = 1;


};


#endif // MYPEOPLEWIDGET_H
