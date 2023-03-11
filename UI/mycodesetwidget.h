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

signals:
      mySignalCodeSetting(int old_addr,int new_addr); //自定义信号函数,msg参数可以省略

      void mySignalFlag();
public:
  explicit MyCodeSetWidget(QWidget *parent = nullptr);

      void closeEvent(QCloseEvent *event);

      void create();


private slots:

  void getIndex(int index);

  void btn1Slots();

private:

  int flag = 1;

  QLabel *label_old;
  QLabel *label_new;

  QLineEdit *lineEdit;

  QPushButton *btn1;

  QSpacerItem *h_spacer;

  QComboBox *comboBox;

  QHBoxLayout *layout;

  QStringList strList;


public:

  void setPushButton_send_yuanxin(bool flag);

};


#endif // MYCODESETWIDGET_H
