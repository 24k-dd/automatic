#include "mywidget.h"
#include<bits/stdc++.h>
#include<QLabel>
#include<QTableWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QWidget>
#include<QSpacerItem>
#include<QSizePolicy>
#include<QDebug>

#include<QGroupBox>

MyWidget::MyWidget(int index2,QWidget *parent) : QWidget(parent,Qt::WindowStaysOnTopHint)
{
  \
  index = index2;

  //在主界面中创建两个对象
  targetSheet = new TargetSheet(hole_size1,this);

  myTable = new MyTableWidget;

  create();

  connect(clearButton,SIGNAL(clicked()),this,SLOT(clearBtn()));

  connect(this,SIGNAL(mySignal(QList<QPointF>)),targetSheet,SLOT(updateHoles(QList<QPointF>)));
}

MyWidget::~MyWidget()
{

}

void MyWidget::create()
{
  //主界面外观设置
  this->resize(1200,840);
  this->setWindowTitle("靶标显示系统");
  this->setWindowIcon(QIcon(":/source/app-icon.gif"));
  this->setFixedSize(this->width(),this->height());

  QWidget *widget = new QWidget(this);


  QLabel *label_name = new QLabel("姓名:");
  label_name->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));

  QWidget *label_baHao = new QLabel("靶位号:");
  label_baHao->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));
  QWidget *label_allHuanShu = new QLabel("总环数:");
  label_allHuanShu->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));

  labelName = new QLabel();
  labelName->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));
  labelBaHao = new QLabel(QString::asprintf("%d",index));
  labelBaHao->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));
  labelSum = new QLabel("0");
  labelSum->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));

  //  widget->setStyleSheet("width: 100px;height: 100px;background: white;");

  //中靶数
  QLabel *zhongDan = new QLabel("中靶数: ");
  zhongDan->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));
  zhongDanShu = new QLabel("0");
  zhongDanShu->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));

  //电压值
  labelBattery = new QLabel("0 V");
  labelBattery->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));
  QLabel *batteryLabel = new QLabel("靶位电压:");
  batteryLabel->setFont(QFont(QString::asprintf("Cambria Math"), 14, QFont::Black));

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Minimum);
  QSpacerItem *v_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Minimum);

  QHBoxLayout *h_layout_name = new QHBoxLayout;
  QHBoxLayout *h_layout_baHao = new QHBoxLayout;

  QHBoxLayout *h_zhongDan = new QHBoxLayout();
  QHBoxLayout *h_allSum = new QHBoxLayout;

  //名字布局
  h_layout_name->addWidget(label_name);
  h_layout_name->addWidget(labelName);

  //靶号布局
  h_layout_baHao->addWidget(label_baHao);
  h_layout_baHao->addWidget(labelBaHao);

  h_zhongDan->addWidget(zhongDan);
  h_zhongDan->addWidget(zhongDanShu);

  h_allSum->addWidget(label_allHuanShu);
  h_allSum->addWidget(labelSum);

  //中弹水平布局
  QHBoxLayout *h_zhongdan_allsum = new QHBoxLayout;
  h_zhongdan_allsum->addLayout(h_zhongDan);
  h_zhongdan_allsum->addItem(h_spacer);
  h_zhongdan_allsum->addLayout(h_allSum);

  //电压标签水平布局
  QHBoxLayout *h_layout_battery_value = new QHBoxLayout;
  h_layout_battery_value->addWidget(batteryLabel);
  h_layout_battery_value->addWidget(labelBattery);
  h_layout_battery_value->addItem(h_spacer);

  //清除按钮布局
  QHBoxLayout *h_layout_clear_btn = new QHBoxLayout;
  clearButton = new QPushButton("清除记录");
  clearButton->setStyleSheet("QPushButton{width: 100px;height: 100px;border: 1px solid green;font-family: 微软雅黑;border-radius: 14px;font-size: 25px;background-color: #00ff7f;}""QPushButton:pressed{background:white;}");
  clearButton->setFixedSize(110,50);
  h_layout_clear_btn->addItem(h_spacer);
  h_layout_clear_btn->addWidget(clearButton);
  h_layout_clear_btn->addItem(h_spacer);

  //右侧总布局
  QVBoxLayout *v_layout = new QVBoxLayout(this);
  //  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_name);
  //  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_baHao);
  //  v_layout->addItem(v_spacer);
  v_layout->addWidget(myTable);
  //  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_zhongdan_allsum);
  //  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_battery_value);
  //  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_clear_btn);
  //  v_layout->addItem(v_spacer);
  //右侧布局设置
  widget->setLayout(v_layout);
  //详细信息界面
  QHBoxLayout *h_layout = new QHBoxLayout;
  h_layout->addWidget(targetSheet);
  h_layout->addItem(h_spacer);
  h_layout->addWidget(widget);

  setLayout(h_layout);

  setStyleSheet(
        "QLabel,QPushButton{color:black;font-size:25px;font-weight: simsun; font-family: 微软雅黑;font-bold;}");
}

void MyWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
}

//更新子弹列表
void MyWidget::passHolesData(const QVector<Target_Info_Table> &data)
{
  int sum = 0,zhongBa = 0;
  int msgSize = data.size();
  QList<QPointF>   onlyHoleList = {};

  myTable->clearContents();
  for(int i = 0;i < msgSize;i++)
    {

      s_index = data[i].addr;

      user_name = data[i].user_name;
      labelName->setText(user_name);

      onlyHoleList.append(QPointF(data[i].x,801 - data[i].y));

      sum += data[i].cylinder_number;
      QTableWidgetItem *danXu = new QTableWidgetItem(QString::asprintf("%d",i + 1));
      danXu->setTextAlignment(Qt::AlignCenter);
      danXu->setFont(QFont(QString::asprintf("Cambria Math"), 16, QFont::Black));

      QTableWidgetItem *huanShu = new QTableWidgetItem();
      huanShu->setTextAlignment(Qt::AlignCenter);
      huanShu->setFont(QFont(QString::asprintf("Cambria Math"), 16, QFont::Black));

      QTableWidgetItem *direction = new QTableWidgetItem();
      direction->setTextAlignment(Qt::AlignCenter);
      direction->setFont(QFont(QString::asprintf("Cambria Math"), 16, QFont::Black));

      if(data[i].direction == -1)
        {
          danXu->setForeground(QColor(Qt::red));
          huanShu->setText(QString::asprintf("脱靶"));
          huanShu->setForeground(QColor(Qt::red));
          direction->setText(QString::asprintf(""));
        }else{
          huanShu->setText(QString::asprintf("%d",data[i].cylinder_number));
          direction->setText(QString::asprintf("%d",data[i].direction));
          zhongBa++;
        }
      myTable->setItem(i,0,danXu);
      myTable->setItem(i,1,huanShu);
      myTable->setItem(i,2,direction);
    }

  zhongDanShu->setText(QString::asprintf("%d",zhongBa));

  labelSum->setText(QString::asprintf("%d",sum));

  emit mySignal(onlyHoleList);


}

void MyWidget::passBatteryData(double msg)
{

  labelBattery->setText(QString::asprintf("%.1f V",msg));
}

//获取当前点击的item
void MyWidget::getIndex(int msg)
{
  index = msg + 1;
  QList<QPointF>   onlyHoleList = {};

  //清空表格
  if(index != s_index)
    {
      myTable->clear();
      labelName->setText("");
      zhongDanShu->setText("");
      labelSum->setText("");
      labelBattery->setText("");
      emit mySignal(onlyHoleList);
    }
  QStringList strList;
  strList<<tr("弹序")<<tr("环数")<<tr("方向");
  myTable->setHorizontalHeaderLabels(strList);


  //更新当前靶号
  labelBaHao->setText(QString::asprintf("%d",index));
}

void MyWidget::clearBtn()
{
  emit mySignalBtn();

  QList<QPointF>   onlyHoleList = {};

  myTable->clear();
  labelName->setText("");
  zhongDanShu->setText("");
  labelSum->setText("");
  labelBattery->setText("");
  emit mySignal(onlyHoleList);

  QStringList strList;
  strList<<tr("弹序")<<tr("环数")<<tr("方向");
  myTable->setHorizontalHeaderLabels(strList);
}



