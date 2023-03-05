#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent)
{
  runMain();

  myListWidget = new MyListWidget();

  mySocket = new MySocket(this);

  create();

  //双击放大
  connect(myListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listWidgetDoubleClicked(QListWidgetItem*)));

  //单击选中
  connect(myListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listWidgeSelectionChanged(QListWidgetItem*)));

  //更新靶标子弹
  connect(mySocket,SIGNAL(mySignalUpdateHoles(QList<QList<QString> >)),myListWidget,SLOT(passHolesData(QList<QList<QString> >)));

  //更新连接状态
  connect(mySocket,SIGNAL(mySignalState(QVector<int>)),myListWidget,SLOT(passStateData(QVector<int>)));

  //根据连接状态请求相应靶标接口
  connect(mySocket,SIGNAL(mySignalState(QVector<int>)),this,SLOT(passStateData(QVector<int>)));


  connect(mySocket,SIGNAL(mySignalBattery(QVector<double>)),myListWidget,SLOT(passBatteryData(QVector<double>)));

  //进行信号槽关联
  connect(act[0],SIGNAL(clicked()),this,SLOT(clearall_clicked()));
  connect(act[1],SIGNAL(clicked()),this,SLOT(clearonly_clicked()));
  connect(act[2],SIGNAL(clicked()),this,SLOT(codeset_clicked()));
  connect(act[3],SIGNAL(clicked()),this,SLOT(calib_clicked()));
  connect(act[4],SIGNAL(clicked()),this,SLOT(people_clicked()));
  connect(act[5],SIGNAL(clicked()),this,SLOT(grade_clicked()));
  connect(act[6],SIGNAL(clicked()),this,SLOT(close_clicked()));

  m_Timer.setInterval(700);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      updateState();

      updateBattery();

    });


}

MainWindow::create()
{
  setWindowTitle("标靶显示系统");
  setWindowIcon(QIcon(":/Img/app-icon.gif"));
  //最大化
  setWindowState(Qt::WindowMaximized);
  //清除缓存
  setAttribute(Qt::WA_DeleteOnClose,true);

  //隐藏标题框
  setWindowFlags(Qt::FramelessWindowHint);

  //获取电脑宽度
  nWidth = GetSystemMetrics(SM_CXSCREEN);
  nHeight = GetSystemMetrics(SM_CYSCREEN);

  //工具栏
  toolBar = new QToolBar(this);
  toolBar->setFixedHeight(50);

  //设置工具按钮
  act[0] = new QToolButton(this);
  act[0]->setFixedWidth(170);
  act[0]->setText("全部清除");

  //提示语
  act[0]->setToolTip("清空全部靶标的子弹");

  act[1] = new QToolButton(this);
  act[1]->setFixedWidth(170);
  act[1]->setText("单个清除");

  act[1]->setToolTip("清空单个靶的子弹");

  act[2] = new QToolButton(this);
  act[2]->setFixedWidth(170);
  act[2]->setText("地址设置");


  act[3] = new QToolButton(this);
  act[3]->setFixedWidth(170);
  act[3]->setText("校准程序");


  act[4] = new QToolButton(this);
  act[4]->setFixedWidth(170);
  act[4]->setText("人员分组");


  act[5] = new QToolButton(this);
  act[5]->setFixedWidth(170);
  act[5]->setText("成绩导出");

  act[6] = new QToolButton(this);
  act[6]->setFixedWidth(170);
  act[6]->setText("退出程序");



  //按钮美化
  setStyleSheet("QToolButton,QComboBox{width: 100px;height: 100px;font-size: 25px;font-bold;border: 1px solid green;font-family: 微软雅黑;border-radius: 17px;background-color: #00ffff}""QToolButton:pressed{background:white;}\
                QComboBox QAbstractItemView::item{height:50px;}");

                for(int i = 0;i < 7;i++)
  {
    toolBar->addWidget(act[i]);
    toolBar->addSeparator();
    toolBar->addSeparator();
  }

  //布局
  QVBoxLayout *v_layout = new QVBoxLayout();

  v_layout->addWidget(toolBar);

  v_layout->addWidget(myListWidget);

  setLayout(v_layout);
}

MainWindow::~MainWindow()
{


}

//资源释放
void MainWindow::close_clicked()
{
  if(m_flag)
    {
      if(QMessageBox::Ok == QMessageBox::warning(this,tr("警告"),tr("是否退出程序!"),QMessageBox::Ok,QMessageBox::No))
        {
          mySocket->close();
          stopMain();
          this->close();
        }
    }


}

//全部清空
void MainWindow::clearall_clicked()
{

  QVariantList varList = toJsonData("addr",ClearTarget,-1,true);

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"全部清除指令已发送:"<<data;
}

//单个清除
void MainWindow::clearonly_clicked()
{
  QString str1;
  if(index2 == -1)
    {
      QMessageBox::information(this,tr("提示"),tr("请选中靶标!"),QMessageBox::Ok);
    }else{

      QVariantList varList = toJsonData("addr",ClearTarget,index2 + 1,true);
      QByteArray data = mapToByteArry(varList);

      mySocket->sendData(data);

      qDebug()<<"主界面单个清除指令已发送:"<<data;
    }
}

//编码设置
void MainWindow::codeset_clicked()
{

  if(m_flag){
      //编码设置
      MyCodeSetWidget *myCodeSetWidget = new MyCodeSetWidget();

      //编码设置发送
      connect(myCodeSetWidget,SIGNAL(mySignalCodeSetting(int,int)),this,SLOT(sendYuanXin(int,int)));
      //传递编码设置索引
      connect(this,SIGNAL(mySignal(int)),myCodeSetWidget,SLOT(getIndex(int)));
      //判断窗口状态
      connect(myCodeSetWidget,SIGNAL(mySignalFlag()),this,SLOT(updateFlag()));
      myCodeSetWidget->show();

      m_flag = false;
    }

}

//校准程序
void MainWindow::calib_clicked()
{
  if(m_flag)
    {

      CheckCodeWidget *checkCodeWidget = new CheckCodeWidget();

      //传递校准程序索引
      connect(this,SIGNAL(mySignal(int)),checkCodeWidget,SLOT(getCurrentIndex(int)));

      //开始校准索引
      connect(checkCodeWidget,SIGNAL(mySignalBegin(int)),this,SLOT(sendBegin(int)));//下一个
      connect(checkCodeWidget,SIGNAL(mySignalOver(int)),this,SLOT(sendOver(int)));//结束
      connect(checkCodeWidget,SIGNAL(mySignalFlag()),this,SLOT(updateFlag()));
      checkCodeWidget->show();
      m_flag = false;
    }
}

//人员检录
void MainWindow::people_clicked()
{
  if(m_flag)
    {
      //人员分组
      MyPeopleWidget *myPeopleWidget = new MyPeopleWidget();

      //分组编号
      connect(myPeopleWidget, SIGNAL(mySignalZuHao(QString)), this, SLOT(groupNumber(QString)));

      connect(myPeopleWidget,SIGNAL(mySignalFlag()),this,SLOT(updateFlag()));
      myPeopleWidget->show();
      m_flag = false;
    }
}

//成绩导入
void MainWindow::grade_clicked()
{
  if(m_flag)
    {
      //成绩导出
      MyGradeTableWidget *myGradeTableWidget = new MyGradeTableWidget();

      connect(myGradeTableWidget,SIGNAL(mySignalFlag()),this,SLOT(updateFlag()));

      connect(myGradeTableWidget,SIGNAL(mySignalData(int,int,QString)),this,SLOT(searchData(int,int,QString)));
      myGradeTableWidget->show();
      m_flag = false;
    }


}

//发送原新编码
void MainWindow::sendYuanXin(int old_addr,int new_addr)
{

  QVariantList varList;

  QVariantMap var;
  var.insert("code", RewriteTargetId);
  QVariantMap var1;

  var.insert("msg", var1);
  QVariantMap var2;

  var2.insert("old_addr",old_addr);
  var2.insert("new_addr",new_addr);

  var.insert("data", var2);

  varList << var;

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"编码设置指令已发送:"<<data;
}

//发送指定校准靶号
void MainWindow::sendBegin(int flag)
{


  QVariantList varList = toJsonData("addr",OpenCalibrationTargetById,flag,true);

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"开始校准指令已发送:"<<data;
}

//发送end
void MainWindow::sendOver(int flag)
{

  QVariantList varList = toJsonData("addr",CloseCalibrationTargetById,flag,true);

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"结束指令已发送:"<<data;
}

void MainWindow::searchData(int fenZu, int baHao, QString time)
{
  QVariantList varList;

  QVariantMap var;
  var.insert("code", GetShowInfo);
  QVariantMap var1;
  var1.insert("create_at",time);

  var.insert("msg", var1);
  QVariantMap var2;

  var2.insert("addr",baHao);
  var2.insert("group_number",fenZu);

  var.insert("data", var2);

  varList << var;

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"编码设置指令已发送:"<<data;
}



void MainWindow::updateState()
{

  QVariantList varList = toJsonData("addr",GetTargetState,1,false);

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);
}

//请求电量
void MainWindow::updateBattery()
{


  QVariantList varList = toJsonData("addr",GetVoltage,1,false);
  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);
}



//单个清除
void MainWindow::clearBtn()
{


  QVariantList varList = toJsonData("addr",ClearTarget,index2 + 1,true);

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"详细信息界面单个清除已发送:"<<data;
}


void MainWindow::groupNumber(QString indexZuHao)
{

  QVariantList varList = toJsonData("group_number",UserGrouping,indexZuHao.toInt(),true);

  QByteArray data = mapToByteArry(varList);

  mySocket->sendData(data);

  qDebug()<<"分组指令已发送:"<<data;
}


//详细信息界面
void MainWindow::listWidgetDoubleClicked(QListWidgetItem *item)
{
  //详细信息
  if(m_flag)
    {
      MyWidget *myWidget = new MyWidget();

      //传递详细信息界面索引
      connect(this, SIGNAL(mySignal(int)), myWidget, SLOT(getIndex(int)));

      //详细信息界面清除按钮
      connect(myWidget, SIGNAL(mySignalBtn()), this, SLOT(clearBtn()));

      connect(myWidget, SIGNAL(mySignalFlag()), this, SLOT(updateFlag()));

      connect(mySocket,SIGNAL(mySignalUpdateHoles(QList<QList<QString> >)),myWidget,SLOT(passHolesData(QList<QList<QString>>)));

      connect(mySocket,SIGNAL(mySignalBattery(QVector<double>)),myWidget,SLOT(passBatteryData(QVector<double>)));
      index = myListWidget->currentRow();
      emit mySignal(index);
      myWidget->show();
      m_flag = false;
    }

}

//添加背景阴影
void MainWindow::listWidgeSelectionChanged(QListWidgetItem* ite)
{
  //标记
  index3 = index2;

  index2 = myListWidget->currentRow();
  myListWidget->item[index2]->setBackgroundColor(QColor("#a8a8a8"));
  if(index3 > -1 && index3 < 21 && index2 != index3)
    {
      myListWidget->item[index3]->setBackgroundColor(QColor(Qt::white));
    }
  emit mySignal(index2);
}

void MainWindow::passStateData(QVector<int> msg)
{
  for(int i = 1;i < msg.size();i++)
    {
      if(msg[i] != 1)
        {
          QVariantList varList = toJsonData("addr",GetShowInfo,msg[i],true);

          QByteArray data = mapToByteArry(varList);

          mySocket->sendData(data);
        }

    }
}


//判断窗口是否打开
void MainWindow::updateFlag()
{
  m_flag = true;
}




