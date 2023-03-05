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

MyWidget::MyWidget(QWidget *parent) : QWidget(parent,Qt::WindowStaysOnTopHint)
{
  \


  //在主界面中创建两个对象
  targetSheetTwo = new TargetSheetTwo(this);



  myTable = new MyTableWidget(this);
  create();

  connect(clearButton,SIGNAL(clicked()),this,SLOT(clearBtn()));

  connect(this,SIGNAL(mySignal(QList<QPointF>)),targetSheetTwo,SLOT(updateHoles(QList<QPointF>)));


}



MyWidget::~MyWidget()
{

  delete targetSheetTwo;
  delete myTable;
  delete labelSum;
  delete labelBaHao;
  delete labelName;
  delete clearButton;
  delete labelBattery;
  delete zhongDanShu;
}

void MyWidget::create()
{
  //主界面外观设置
  this->resize(1215,840);
  this->setWindowTitle("靶标显示系统");
  this->setWindowIcon(QIcon(":/Img/app-icon.gif"));
  this->setFixedSize(this->width(),this->height());

  QWidget *widget = new QWidget();
  QLabel *label_name = new QLabel("姓名:");

  QWidget *label_baHao = new QLabel("靶位号:");

  QWidget *label_allHuanShu = new QLabel("总环数:");



  labelName = new QLabel("火麟飞");

  labelBaHao = new QLabel("1号靶");

  labelSum = new QLabel("0");


  widget->setStyleSheet("width: 100px;height: 100px;background: white;");

  //中靶数
  QLabel *zhongDan = new QLabel("中靶数: ");

  zhongDanShu = new QLabel("0");


  //电压值
  labelBattery = new QLabel("0 V");

  QLabel *batteryLabel = new QLabel("靶位电压:");




  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);
  QSpacerItem *v_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding);

  QHBoxLayout *h_layout_name = new QHBoxLayout();
  QHBoxLayout *h_layout_baHao = new QHBoxLayout();

  QHBoxLayout *h_zhongDan = new QHBoxLayout();
  QHBoxLayout *h_allSum = new QHBoxLayout();

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
  QHBoxLayout *h_zhongdan_allsum = new QHBoxLayout();
  h_zhongdan_allsum->addLayout(h_zhongDan);
  h_zhongdan_allsum->addItem(h_spacer);
  h_zhongdan_allsum->addLayout(h_allSum);

  //电压标签水平布局
  QHBoxLayout *h_layout_battery_value = new QHBoxLayout();
  h_layout_battery_value->addWidget(batteryLabel);
  h_layout_battery_value->addWidget(labelBattery);

  //电压布局
  QHBoxLayout *h_battery = new QHBoxLayout();
  //  h_battery->addItem(h_spacer);
  h_battery->addLayout(h_layout_battery_value);
  h_battery->addItem(h_spacer);

  //清除按钮布局
  QHBoxLayout *h_layout_clear_btn = new QHBoxLayout();
  clearButton = new QPushButton("清除记录");
 clearButton->setStyleSheet("QPushButton{width: 100px;height: 100px;border: 1px solid green;font-family: 微软雅黑;border-radius: 14px;font-size: 25px;background-color: #00ff7f;}""QPushButton:pressed{background:white;}");
  clearButton->setFixedSize(110,50);
  h_layout_clear_btn->addItem(h_spacer);
  h_layout_clear_btn->addWidget(clearButton);
  h_layout_clear_btn->addItem(h_spacer);

  //右侧总布局
  QVBoxLayout *v_layout = new QVBoxLayout();
  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_name);
  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_baHao);
  v_layout->addItem(v_spacer);
  v_layout->addWidget(myTable);
  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_zhongdan_allsum);
  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_battery);
  v_layout->addItem(v_spacer);
  v_layout->addLayout(h_layout_clear_btn);
  v_layout->addItem(v_spacer);
  //右侧布局设置
  widget->setLayout(v_layout);
  //详细信息界面
  QHBoxLayout *h_layout = new QHBoxLayout(this);
  h_layout->addWidget(targetSheetTwo);
  h_layout->addItem(h_spacer);
  h_layout->addWidget(widget);

  setStyleSheet(
        "QLabel,QPushButton{color:black;font-size:25px;font-weight: simsun; font-family: 微软雅黑;font-bold;}");
}

void MyWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
}

//更新子弹列表
void MyWidget::passHolesData(QList<QList<QString>> msg)
{
  int sum = 0,zhongBa = 0;
  int num = msg.size();
    QList<QPointF>   onlyHoleList = {};

  myTable->clearContents();
  for(int i = 0;i < num;i++)
    {
      if(index == msg[i][0])
        {
          onlyHoleList.append(QPointF(msg[i][1].toDouble(),801 - msg[i][2].toDouble()));

          sum += msg[i][3].toInt();
          QTableWidgetItem *danXu = new QTableWidgetItem(QString::asprintf("%d",i + 1));

          danXu->setTextAlignment(Qt::AlignCenter);

          QTableWidgetItem *huanShu = new QTableWidgetItem();

          huanShu->setTextAlignment(Qt::AlignCenter);

          QTableWidgetItem *direction = new QTableWidgetItem();

          direction->setTextAlignment(Qt::AlignCenter);

          if(msg[i][4] == -1)
            {
              danXu->setForeground(QColor(Qt::red));
              huanShu->setText(QString::asprintf("脱靶"));
              huanShu->setForeground(QColor(Qt::red));
              direction->setText(QString::asprintf(""));
            }else{
              huanShu->setText(msg[i][3]);
              direction->setText(msg[i][4]);
              zhongBa++;
            }
          myTable->setItem(i,0,danXu);
          myTable->setItem(i,1,huanShu);
          myTable->setItem(i,2,direction);
        }
    }
  setStyleSheet("QTableWidgetItem{color:black;font-size:25px;font-weight: simsun; font-family: 微软雅黑;font-bold;}");

  zhongDanShu->setText(QString::asprintf("%d",zhongBa));

  labelSum->setText(QString::asprintf("%d",sum));

  emit mySignal(onlyHoleList);

}

void MyWidget::passBatteryData(QVector<double> msg)
{
  double electric = msg[index] / 10 * 1.0;
  if(msg[index] == 1)
    {
        labelBattery->setText(QString::asprintf("0"));
    }else{
        labelBattery->setText(QString::asprintf("%.1f V").arg(electric));
    }
}

//更新电量
//void MyWidget::passStateData()
//{
//  double batteryValue = 0;
//  //获取数据库表二行高
//  current_cnt2  = sqliteThread1->cnt2;
//  //开辟内存空间
//  t2 = new TableTwo[current_cnt2];
//  //初始化结构体2数据
//  sqliteThread1->updateState(t2);
//  for(int i = 0;i < current_cnt2;i++)
//    {
//      if(t2[i].addr == index)
//        {
//          batteryValue = t2[i].electric * 1.0 / 10;
//          break;
//        }
//    }

//  labelBattery->setText(QString::asprintf("%.1f V",batteryValue));

//  if(batteryValue < 12.5)
//    {
//      batteryV->setStyleSheet("background-color: red;");
//    }else{
//      batteryV->setStyleSheet("background-color: white;");
//    }
//  delete [] t2;
//}

//获取当前点击的item
void MyWidget::getIndex(int msg)
{
  index = msg + 1;

  labelBaHao->setText(QString::asprintf("%d",index));
}

void MyWidget::clearBtn()
{
  emit mySignalBtn();
}



