#include "mypeoplewidget.h"


MyPeopleWidget::MyPeopleWidget(QWidget *parent) :
  QWidget(parent,Qt::WindowStaysOnTopHint)
{

  create();

  m_date = QDate::currentDate();
  currentDate = m_date.toString("yyyy-MM-dd");

  //每隔2s读一次文件
  m_Timer.setInterval(2000);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      //读取信息
      infoEntry();

    });


  connect(btn,SIGNAL(clicked()),this,SLOT(btn_clicked()));
  connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Slots()));

  connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Slots()));

  readText();

}

void MyPeopleWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
  m_Timer.stop();
}

void MyPeopleWidget::readText()
{
  QString  strm = QApplication::applicationDirPath();
  strm += "/config2.txt";

  QFile file(strm);

  if(!file.open(QIODevice::ReadWrite))
    qDebug()<<"Can't open the file!";

  QByteArray line = file.readLine();

  QString str = line;
  str.replace("\n","");

  QString s1,s2;
  for(int i = 0;i < 10;i++)
    {
      s1.append(str[i]);
    }
  for(int i = 11;i < str.size();i++)
    {
      s2.append(str[i]);
    }

  if(s1 == currentDate)
    {
      lineEditTip->setText(s2);

    }
  else
    lineEditTip->setText("0");
  file.close();
}

void MyPeopleWidget::writeText()
{
  m_date = QDate::currentDate();
  currentDate = m_date.toString("yyyy-MM-dd");

  QString  strm = QApplication::applicationDirPath();

  strm += "/config2.txt";
  QDir path; // 创建一个QDir变量
  if (!path.exists(strm)) {  // 使用QDir成员函数exists()来判断文件夹是否存在
      path.mkdir(strm);  // 使用mkdir来创建文件夹
    }

  strm.replace("/","\\");

  QFile file(strm);

  if(!file.open(QIODevice::ReadWrite))
    qDebug()<<"Can't open the file!";

  currentDate += "-"+zuhao;

  file.write(currentDate.toUtf8());
  file.close();
}

void MyPeopleWidget::create()
{
  //  setFixedSize(900,100);
  setWindowTitle("人员检录");


  btn1 = new QPushButton("开始录入");
  btn1->setFixedSize(180,60);
  btn1->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  btn2 = new QPushButton("结束录入");
  btn2->setFixedSize(180,60);
  btn2->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  setAttribute(Qt::WA_DeleteOnClose,false);

  QLabel *tip = new QLabel("上次分组:");
  tip->setFixedSize(150,60);
  tip->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  lineEditTip = new QLineEdit("0");
  lineEditTip->setFixedSize(80,60);
  lineEditTip->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));
  lineEditTip->setReadOnly(true);
  btn = new QPushButton("分组");
  btn->setFixedSize(100,60);

  btn->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  lineEdit = new QLineEdit("1");
  lineEdit->setFixedSize(80,60);
  lineEdit->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);

  QHBoxLayout *layout = new QHBoxLayout();
  layout->addItem(h_spacer);
  layout->addWidget(tip);
  layout->addItem(h_spacer);
  layout->addWidget(lineEditTip);
  layout->addItem(h_spacer);
  layout->addWidget(lineEdit);
  layout->addItem(h_spacer);
  layout->addWidget(btn);
  layout->addItem(h_spacer);
  layout->addWidget(btn1);
  layout->addItem(h_spacer);
  layout->addWidget(btn2);
  layout->addItem(h_spacer);

  setLayout(layout);
}

void MyPeopleWidget::btn_clicked()
{
  zuhao = lineEdit->text();
  vecIdCard.clear();
  emit mySignalZuHao(zuhao);
  writeText();

}

bool MyPeopleWidget::infoEntry()
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
      //      qDebug() << ("打开文件失败");
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

  int vecSize = vecIdCard.size();

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

  if(vecSize != vecIdCard.size())
    {
      emit mySignalInfo(name,idCard);
    }

}

bool MyPeopleWidget::deleteFile(const QString &strPath)
{

  if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
    return false;
  QFileInfo FileInfo(strPath);

  if (FileInfo.isFile())//如果是文件
    QFile::remove(strPath);
  return true;
}

void MyPeopleWidget::btn1Slots()
{

  btn1->setEnabled(false);
  btn1->setText("正在录入...");
  emit openInfo();
}

void MyPeopleWidget::btn2Slots()
{
  btn1->setEnabled(true);
  btn1->setText("开始录入");
  emit closeInfo();
}


