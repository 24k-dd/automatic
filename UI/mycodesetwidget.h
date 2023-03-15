#ifndef MYCODESETWIDGET_H
#define MYCODESETWIDGET_H

#include <QWidget>
#include<qDebug>
#include<QLabel>
#include<QSpacerItem>
#include<QHBoxLayout>
#include<QComboBox>
#include<QLineEdit>
#include<QListView>
#include<QPushButton>


class MyCodeSetWidget : public QWidget
{
  Q_OBJECT


public:
  explicit MyCodeSetWidget(QWidget *parent = nullptr);

      void closeEvent(QCloseEvent *event);

      void create();

signals:
      mySignalCodeSetting(int old_addr,int new_addr); //自定义信号函数,msg参数可以省略

      mySignalFlag();
private slots:

  //获取当前id
  void getIndex(int index);

  //发送原新编码
  void btn1Slots();

private:

  int flag = 1;

  QLineEdit *lineEdit;

  QPushButton *btn1;

  QComboBox *comboBox;

  QStringList strList;


public:

};


#endif // MYCODESETWIDGET_H
