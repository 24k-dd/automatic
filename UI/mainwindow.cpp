#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent)
{
  //运行主程序
  runMain();

  myListWidget = new MyListWidget;

  mySocket = new MySocket();

  //创建布局
  create();


  //双击打开详细界面
  connect(myListWidget,SIGNAL(mySignalDoubleIndex(int)),this,SLOT(doubleClicked(int)));

  //单 双击 更新通信里的id
  connect(myListWidget,SIGNAL(mySignalDoubleIndex(int)),mySocket,SLOT(updateIndex(int)));
  connect(myListWidget, SIGNAL(mySignalIndex(int)), mySocket, SLOT(updateIndex(int)));

  //更新所有靶标
  connect(mySocket,SIGNAL(mySignalUpdateHoles(QJsonArray)),myListWidget,SLOT(passHolesData(QJsonArray)));

  //更新所有靶标电量
  connect(mySocket,SIGNAL(mySignalBattery(QVector<double>)),myListWidget,SLOT(passBatteryData(QVector<double>)));

  //更新所有靶标状态
  connect(mySocket,SIGNAL(mySignalState(QVector<int>)),myListWidget,SLOT(passStateData(QVector<int>)));

  //进行信号槽关联
  connect(act[0],SIGNAL(clicked()),this,SLOT(clearall_clicked()));
  connect(act[1],SIGNAL(clicked()),this,SLOT(clearonly_clicked()));
  connect(act[2],SIGNAL(clicked()),this,SLOT(codeset_clicked()));
  connect(act[3],SIGNAL(clicked()),this,SLOT(calib_clicked()));
  connect(act[4],SIGNAL(clicked()),this,SLOT(people_clicked()));
  connect(act[5],SIGNAL(clicked()),this,SLOT(grade_clicked()));
  connect(act[6],SIGNAL(clicked()),this,SLOT(close_clicked()));

  updateStateAndBattery();

  //每隔5s请求一次
  m_Timer.setInterval(state_time);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      //更新状态和电量
      updateStateAndBattery();

    });
}

void MainWindow::create()
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
  act[2]->setToolTip("对靶标地址进行设置");

  act[3] = new QToolButton(this);
  act[3]->setFixedWidth(170);
  act[3]->setText("校准程序");
  act[3]->setToolTip("对靶标进行校准");

  act[4] = new QToolButton(this);
  act[4]->setFixedWidth(170);
  act[4]->setText("人员分组");
  act[4]->setToolTip("对人员进行分组");

  act[5] = new QToolButton(this);
  act[5]->setFixedWidth(170);
  act[5]->setText("成绩导出");
  act[5]->setToolTip("查询打靶数据或对查询数据进行导出");

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
  index2 = myListWidget->getIndex() + 1;

  if(index2 == -1)
    {
      QMessageBox::information(this,tr("提示"),tr("请选中靶标!"),QMessageBox::Ok);
    }else{

      QVariantList varList = toJsonData("addr",ClearTarget,index2,true);
      QByteArray data = mapToByteArry(varList);

      mySocket->sendData(data);

      qDebug()<<"主界面单个清除指令已发送:"<<index2<<data;
    }
}

//编码设置
void MainWindow::codeset_clicked()
{

  if(m_flag){
      //编码设置
      MyCodeSetWidget *myCodeSetWidget = new MyCodeSetWidget();
      //编码设置发送
      connect(myCodeSetWidget,SIGNAL(mySignalCodeSetting(int,int)),mySocket,SLOT(sendYuanXin(int,int)));
      //传递编码设置索引
      connect(myListWidget,SIGNAL(mySignalIndex(int)),myCodeSetWidget,SLOT(getIndex(int)));
      //控制窗口同时只能打开一个界面
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
      connect(myListWidget,SIGNAL(mySignalIndex(int)),checkCodeWidget,SLOT(getCurrentIndex(int)));
      //开始校准
      connect(checkCodeWidget,SIGNAL(mySignalBegin(int)),mySocket,SLOT(sendBegin(int)));
      //结束
      connect(checkCodeWidget,SIGNAL(mySignalOver(int)),mySocket,SLOT(sendOver(int)));

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
      connect(myPeopleWidget, SIGNAL(mySignalZuHao(QString)), mySocket, SLOT(sendGroupNumber(QString)));

      connect(myPeopleWidget,SIGNAL(mySignalFlag()),this,SLOT(updateFlag()));

      myPeopleWidget->show();
      m_flag = false;
    }
}

//成绩导出
void MainWindow::grade_clicked()
{
  if(m_flag)
    {
      //成绩导出
      MyGradeTableWidget *myGradeTableWidget = new MyGradeTableWidget();

      connect(myGradeTableWidget,SIGNAL(mySignalFlag()),this,SLOT(updateFlag()));

      //查询数据，请求接口
      connect(myGradeTableWidget,SIGNAL(mySignalData(int,int,QString)),mySocket,SLOT(sendSearchData(int,int,QString)));

      //显示查询到的数据
      connect(mySocket,SIGNAL(mySignalGradeData(QJsonArray)),myGradeTableWidget,SLOT(updateGrade(QJsonArray)));

      myGradeTableWidget->show();

      m_flag = false;
    }
}

//请求连接状态和电量
void MainWindow::updateStateAndBattery()
{

  QVariantList varListState = toJsonData("addr",GetTargetState,-1,false);

  QByteArray dataState = mapToByteArry(varListState);

  mySocket->sendData(dataState);

  QVariantList varListBattery = toJsonData("addr",GetVoltage,-1,false);
  QByteArray dataBattery  = mapToByteArry(varListBattery);

  mySocket->sendData(dataBattery );
}


//详细信息界面
void MainWindow::doubleClicked(int msg)
{
  index2 = msg + 1;
  //  详细信息
  if(m_flag)
    {
      MyWidget *myWidget = new MyWidget(index2);
      //单双击传递详细信息界面索引
      connect(myListWidget, SIGNAL(mySignalIndex(int)), myWidget, SLOT(getIndex(int)));
      connect(myListWidget, SIGNAL(mySignalDoubleIndex(int)), myWidget, SLOT(getIndex(int)));

      //详细信息界面清除按钮
      connect(myWidget, SIGNAL(mySignalBtn()), this, SLOT(clearonly_clicked()));

      connect(myWidget, SIGNAL(mySignalFlag()), this, SLOT(updateFlag()));

      //传递单个靶的数据
      connect(mySocket,SIGNAL(mySignalOnlyTarget(QJsonArray)),myWidget,SLOT(passHolesData(QJsonArray)));

      //传递单个靶的电量数据
      connect(mySocket,SIGNAL(mySignalBatteryValue(double)),myWidget,SLOT(passBatteryData(double)));

      myWidget->show();

      m_flag = false;
    }
}

//判断窗口是否打开
void MainWindow::updateFlag()
{
  m_flag = true;
}




