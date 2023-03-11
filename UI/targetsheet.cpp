#include "targetsheet.h"

//构造函数初始化
TargetSheet::TargetSheet(QWidget *parent) : QLabel(parent)
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

void TargetSheet::create()
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
  //    holeList = {};
  onlyHoleList = {};

  //加载弹孔图片，并求取弹孔中心坐标
  bulletImage = QPixmap(":/Img/bulletHole.png").scaled(12,12);
  bulletCenter = QPointF(bulletImage.size().width()/2.0, bulletImage.size().height()/2.0);
}

//重载父类绘制方法
void TargetSheet::paintEvent(QPaintEvent *event)
{
  //    this->clear();
  //调用父类方法进行窗体绘制
  this->QLabel::paintEvent(event);

  //进行弹孔中心坐标校准，并画出弹孔
  QPainter painter(this);

  QPointF pointF;
  foreach(pointF, onlyHoleList)
    {
      painter.drawPixmap(pointF - bulletCenter, bulletImage);
    }

}

void TargetSheet::updateHoles(QList<QPointF> msg)
{
  onlyHoleList.clear();
  onlyHoleList = msg;
}

void TargetSheet::updateSize(double size)
{
  //加载弹孔图片，并求取弹孔中心坐标
  bulletImage = QPixmap(":/Img/bulletHole.png").scaled(24 * size,24 * size);
  bulletCenter = QPointF(bulletImage.size().width()/2.0, bulletImage.size().height()/2.0);
}
