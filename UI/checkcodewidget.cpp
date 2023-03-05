#include "checkcodewidget.h"


CheckCodeWidget::CheckCodeWidget(QWidget *parent) :
  QWidget(parent,Qt::WindowStaysOnTopHint)
{

  setWindowTitle("校准程序");
  setFixedSize(650,200);
  //窗口关闭时清空资源
  setAttribute(Qt::WA_DeleteOnClose,false);

  QLabel *label = new QLabel("编号:");

  lineEdit = new QLineEdit("1");
  lineEdit->setFixedSize(70,60);

  lineEdit->setReadOnly(true);
  lineEdit->setAlignment(Qt::AlignCenter);

  btn1 = new QPushButton("开始校准");
  btn1->setFixedSize(180,60);

  btn2 = new QPushButton("结束");
  btn2->setFixedSize(180,60);

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);

  QHBoxLayout *layout= new QHBoxLayout();
  layout->addItem(h_spacer);
  layout->addWidget(label);
  layout->addItem(h_spacer);
  layout->addWidget(lineEdit);
  layout->addItem(h_spacer);
  layout->addWidget(btn1);
  layout->addItem(h_spacer);
  layout->addWidget(btn2);
  layout->addItem(h_spacer);
  setLayout(layout);

  connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Slots()));
  connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Slots()));

  setStyleSheet("QLabel,QPushButton,QLineEdit{width: 100px;height: 100px;font-size: 30px;font-bold;font-family: 微软雅黑;}");

}


void CheckCodeWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
}

void CheckCodeWidget::btn1Slots()
{

  btn1->setEnabled(false);
  btn1->setText("正在校准...");
  emit mySignalBegin(flag);
}

void CheckCodeWidget::btn2Slots()
{
  btn1->setEnabled(true);
  btn1->setText("开始校准");
  emit mySignalOver(flag);
}

void CheckCodeWidget::getCurrentIndex(int index)
{
  flag = index + 1;
  lineEdit->setText(QString::asprintf("%d",flag));

}


