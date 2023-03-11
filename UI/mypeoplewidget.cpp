#include "mypeoplewidget.h"


MyPeopleWidget::MyPeopleWidget(QWidget *parent) :
  QWidget(parent,Qt::WindowStaysOnTopHint)
{

  create();
  connect(btn,SIGNAL(clicked()),this,SLOT(btn_clicked()));

  readText();

}

void MyPeopleWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
}

void MyPeopleWidget::readText()
{
  QString  strm = QApplication::applicationDirPath();
  strm += "/config/config2.txt";

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
  strm += "/config";
  QDir path; // 创建一个QDir变量
  if (!path.exists(strm)) {  // 使用QDir成员函数exists()来判断文件夹是否存在
      path.mkdir(strm);  // 使用mkdir来创建文件夹
    }

  strm += "/config2.txt";

  QFile file(strm);

  if(!file.open(QIODevice::ReadWrite))
    qDebug()<<"Can't open the file!";

  currentDate += "-"+zuhao;

  file.write(currentDate.toUtf8());
  file.close();
}

void MyPeopleWidget::create()
{
  setFixedSize(600,100);
  setWindowTitle("人员检录");

  setAttribute(Qt::WA_DeleteOnClose,false);

  QLabel *tip = new QLabel("上次分组:");
  tip->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  lineEditTip = new QLineEdit("0");
  lineEditTip->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));
  lineEditTip->setReadOnly(true);
  btn = new QPushButton("分组");
  btn->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  lineEdit = new QLineEdit("1");
  lineEdit->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  //弹簧
  h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);

  layout = new QHBoxLayout();
  layout->addWidget(tip);
  layout->addItem(h_spacer);
  layout->addWidget(lineEditTip);
  layout->addItem(h_spacer);
  layout->addWidget(lineEdit);
  layout->addItem(h_spacer);
  layout->addWidget(btn);
  setLayout(layout);
}

void MyPeopleWidget::btn_clicked()
{
  zuhao = lineEdit->text();

  emit mySignalZuHao(zuhao);
  writeText();

}


