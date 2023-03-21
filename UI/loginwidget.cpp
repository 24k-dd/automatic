#include "loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
  QWidget(parent)
{
  create();
}

LoginWidget::~LoginWidget()
{


}

//当输入密码不对关闭应用程序时，系统会将main程序关闭
void LoginWidget::closeEvent(QCloseEvent *event)
{
  if(flag == 1)
    {
      // 通过进程名字结束进程
      QProcess::startDetached("taskkill -t  -f /IM " + QString("main.exe"));
      QProcess::startDetached("taskkill -t  -f /IM " + QString("main.exe"));
    }
}

void LoginWidget::create()
{
  this->setWindowTitle("用户登录");
  setAttribute(Qt::WA_DeleteOnClose,false);

  this->setWindowIcon(QIcon(":/source/user.jpg"));
  this->setFixedSize(this->width(),this->height());
  this->setStyleSheet("background-color: white;");

  //加载图片
  loginImage.load(":/source/Login.jpg");
  QLabel *label_logo = new QLabel(this);
  label_logo->setFixedSize(160,160);

  label_logo->setPixmap(QPixmap::fromImage(loginImage));

  QLabel *label_register = new QLabel("注册账号");
  label_register->setStyleSheet("font-family: 微软雅黑;");
  label_register->setAlignment(Qt::AlignRight);

  lineEdit_username = new QLineEdit(this);
  lineEdit_username->setPlaceholderText("username");
  lineEdit_username->setAlignment(Qt::AlignCenter);

  lineEdit_password = new QLineEdit(this);
  lineEdit_password->setPlaceholderText("password");
  lineEdit_password->setAlignment(Qt::AlignCenter);

  lineEdit_username->setFixedSize(280,35);
  lineEdit_username->setStyleSheet("QLineEdit{width: 100px;height: 100px;font-family: 微软雅黑;font-size: 18px;border: 1px solid green;border-radius: 15px;}");
  lineEdit_password->setFixedSize(280,35);
  lineEdit_password->setStyleSheet("QLineEdit{width: 100px;height: 100px;font-family: 微软雅黑;font-size: 18px;border: 1px solid green;border-radius: 15px;}");

  QPushButton *pushButton_login = new QPushButton("登录");
  pushButton_login->setFixedSize(280,35);
  pushButton_login->setStyleSheet("QPushButton{width: 100px;height: 100px;border: 1px solid green;font-family: 微软雅黑;border-radius: 15px;font-size: 18px;background-color: #00ffff}""QPushButton:pressed{background:white;}");



  //输入密码
  lineEdit_username->setText("admin");
  lineEdit_password->setText("123456");

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);
  QSpacerItem *v_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding);

  QHBoxLayout *h_layout_1 = new QHBoxLayout;
  h_layout_1->addItem(h_spacer);
  h_layout_1->addWidget(label_logo);
  h_layout_1->addItem(h_spacer);

  QVBoxLayout *v_layout_1 = new QVBoxLayout;
  v_layout_1->addItem(v_spacer);
  v_layout_1->addWidget(lineEdit_username);
  v_layout_1->addItem(v_spacer);
  v_layout_1->addWidget(lineEdit_password);
  v_layout_1->addItem(v_spacer);
  v_layout_1->addWidget(pushButton_login);
  v_layout_1->addItem(v_spacer);

  QHBoxLayout *h_layout_2 = new QHBoxLayout;
  h_layout_2->addItem(h_spacer);
  h_layout_2->addLayout(v_layout_1);
  h_layout_2->addItem(h_spacer);

  QVBoxLayout *v_layout_2 = new QVBoxLayout;

  v_layout_2->addLayout(h_layout_1);
  v_layout_2->addLayout(h_layout_2);
  v_layout_2->addWidget(label_register);

  setLayout(v_layout_2);

  connect(pushButton_login,SIGNAL(clicked()),this,SLOT(login_clicked()));
}

void LoginWidget::login_clicked()
{
  //获取密码
  username = lineEdit_username->text();
  password = lineEdit_password->text();

  if(username == "admin" && password == "123456")
    {
      //主界面
      mainWindow = new MainWindow();
      //标志位
      flag = 0;
      mainWindow->show();

      this->close();
    }
  else{
      QMessageBox::information(this,tr("提示"),tr("用户名或密码有误!"),QMessageBox::Ok);
    }
}


