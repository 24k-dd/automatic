#include "targetsheettwo.h"

//构造函数初始化
TargetSheetTwo::TargetSheetTwo(QWidget *parent) : QLabel(parent)
{
  //使用qRegisterMetaType对自定义类型 QList<QPointF> 进行注册，否则无法通过信号传递
  qRegisterMetaType<QList<QPointF>>("QList<QPointF>");

  create();

  m_timer.setInterval(300);

  //开启定时器
  m_timer.start();

  //监听定时器发送的信号
  connect(&m_timer,&QTimer::timeout,[=](){

      update();

    });
}

TargetSheetTwo::~TargetSheetTwo()
{

}

void TargetSheetTwo::create()
{
  //靶纸外观初始化
  this->setGeometry(QRect(0, 0, 801, 801));
  this->setScaledContents(true);
  this->setFixedSize(this->width(), this->height());
  this->setStyleSheet("QLabel{width: 100px;height: 100px;border: 1px solid green;border-radius: 10px;background-color: white}");

  //加载背景
  backgroundImage.load(":/Img/circle-print.gif");
  this->setPixmap(QPixmap::fromImage(backgroundImage));

  //弹孔列表初始化
  onlyHoleList = {};

  //加载弹孔图片，并求取弹孔中心坐标
  bulletImage = QPixmap(":/Img/bulletHole.png").scaled(20,20);
  lastBulletImage = QPixmap(":/Img/blue.png").scaled(20,20);
  bulletCenter = QPointF(bulletImage.size().width()/2.0, bulletImage.size().height()/2.0);
}



//重载父类绘制方法
void TargetSheetTwo::paintEvent(QPaintEvent *event)
{
  //调用父类方法进行窗体绘制
  this->QLabel::paintEvent(event);

  //进行弹孔中心坐标校准，并画出弹孔
  QPainter painter(this);
  int i = 1;
  QPointF pointF;
  foreach(pointF, onlyHoleList)
    {
      //        painter.setPen(QColor(Qt::black));
      painter.setPen(QPen(Qt::red,10));
      painter.setFont(QFont("宋体",10,10));
      //        QFont(字体，大小，线宽)

      painter.drawPixmap(pointF - bulletCenter, bulletImage);
      painter.drawText(pointF - bulletCenter + QPointF(4,-5),QString::asprintf("%d",i));
      if(i == onlyHoleList.length())
        {
          pointF = onlyHoleList[onlyHoleList.length() - 1];
          painter.drawPixmap(pointF - bulletCenter, lastBulletImage);
        }
      i = i + 1;

    }
}

void TargetSheetTwo::updateHoles(QList<QPointF> msg)
{
  onlyHoleList.clear();
  onlyHoleList = msg;
}


