#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QPixmap>

#include"mainwindow.h"
#include<windows.h>

#include<tlhelp32.h>

#include<comdef.h>


class LoginWidget : public QWidget
{
  Q_OBJECT

public:
  explicit LoginWidget(QWidget *parent = nullptr);
  ~LoginWidget();

   void closeEvent(QCloseEvent *event);

   void create();

signals:

private slots:
//  void on_pushButton_login_clicked();
  void login_clicked();


private:
  QImage loginImage;

  MainWindow *mainWindow = NULL;
  QLineEdit *lineEdit_username = NULL;
  QLineEdit *lineEdit_password = NULL;
  QString username;
  QString password;



  int flag = 1;

};

#endif // LOGINWIDGET_H
