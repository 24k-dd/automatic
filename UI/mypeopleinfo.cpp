#include "mypeopleinfo.h"


MyPeopleInfo::MyPeopleInfo(QWidget *parent) :
  QWidget(parent,Qt::WindowStaysOnTopHint)
{

  create();

  //每隔2s读一次文件
  m_Timer.setInterval(2000);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      //读取信息
      infoEntry();

    });

  connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Slots()));

  connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Slots()));

}


void MyPeopleInfo::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
}

void MyPeopleInfo::create()
{
  setWindowTitle("人员信息录入");
  setFixedSize(550,200);
  //窗口关闭时清空资源
  setAttribute(Qt::WA_DeleteOnClose,false);



  btn1 = new QPushButton("开始录入");
  btn1->setFixedSize(180,60);

  btn2 = new QPushButton("结束录入");
  btn2->setFixedSize(180,60);

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);

  QHBoxLayout *layout= new QHBoxLayout();

  layout->addItem(h_spacer);
  layout->addWidget(btn1);
  layout->addItem(h_spacer);
  layout->addWidget(btn2);
  layout->addItem(h_spacer);
  setLayout(layout);
  setStyleSheet("QPushButton,QLineEdit{width: 100px;height: 100px;font-size: 30px;font-bold;font-family: 微软雅黑;}");
}

bool MyPeopleInfo::infoEntry()
{

  QString homeDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

  QString strPath = homeDir + "//AppData//Local//Temp//chinaidcard//wz.txt";


  if (QDir().exists(strPath))//是否传入了空的路径||路径是否存在
    {
      if(!deleteFile(strPath))
        qDebug()<<"delete file error!";
    }

  QLibrary mylib("./Termb.dll");

  if(mylib.load())
    {
      qDebug() << "Termb加载成功";

    }else{
      qDebug() << "Termb加载失败";
    }

  typedef int (*CVR_InitComm)(int);
  typedef int (*CVR_Authenticate)(void);
  typedef int (*CVR_Read_Content)(int);
  typedef int(* CVR_CloseComm)(void);
  CVR_InitComm cVR_InitComm = (CVR_InitComm) mylib.resolve("CVR_InitComm");
  CVR_Authenticate cVR_Authenticate = (CVR_Authenticate) mylib.resolve("CVR_Authenticate");
  CVR_Read_Content cVR_Read_Content = (CVR_Read_Content) mylib.resolve("CVR_Read_Content");
  CVR_CloseComm cVR_CloseComm = (CVR_CloseComm) mylib.resolve("CVR_CloseComm");

    cVR_InitComm(1001);
    cVR_Authenticate();
    cVR_Read_Content(4);
    cVR_CloseComm();

  if(!cVR_InitComm){
      //      qWarning() << mylib.errorString();
      qDebug()<<"mylib读取失败";
      return false;
    }



  QFile f(strPath);

  if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      qDebug() << ("打开文件失败");
      return false;
    }
  QTextStream txtInput(&f);
  QVector<QString> vecStr;
  QString lineStr;
  while(!txtInput.atEnd())
    {
      lineStr = txtInput.readLine();
      vecStr.push_back(lineStr);

      qDebug() << (lineStr);
    }

  f.close();

  bool s_flag = true;

  QString name = vecStr[0];
  QString idCard = vecStr[5];

  vecIdCard.push_back(idCard);

  for(int i=0;i<vecIdCard.size();i++){
      for(int j=i+1;j<vecIdCard.size();j++){
          if(vecIdCard[j]==vecIdCard[i]){
              vecIdCard.remove(j);
              j--;
            }
        }
    }


  for(int i = 0;i < vecIdCard.size() - 1;i++)
    {
      if(idCard == vecIdCard[i])
        {
          s_flag = !s_flag;
        }
    }
  if(s_flag)
    {
      emit mySignalInfo(name,idCard);
    }
  qDebug()<<"size"<<vecIdCard.size();
  qDebug()<<vecIdCard;
}

bool MyPeopleInfo::deleteFile(const QString &strPath)
{

  if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
    return false;
  QFileInfo FileInfo(strPath);

  if (FileInfo.isFile())//如果是文件
    QFile::remove(strPath);
  return true;
}

void MyPeopleInfo::btn1Slots()
{

  btn1->setEnabled(false);
  btn1->setText("正在录入...");
  emit openInfo();
}

void MyPeopleInfo::btn2Slots()
{
  btn1->setEnabled(true);
  btn1->setText("开始录入");
  emit closeInfo();
}



