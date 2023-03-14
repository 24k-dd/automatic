#include "onewidget.h"

OneWidget::OneWidget(double size,int index,QWidget *parent) :
  QWidget(parent)
{

  create(size);

  c_index = index;

  //改变大小
  connect(this,SIGNAL(mySignal(double)),targetSheet,SLOT(updateSize(double)));

  //更新靶标数据
  connect(this,SIGNAL(mySignalHoles(QList<QPointF>)),targetSheet,SLOT(updateHoles(QList<QPointF>)));
}

void OneWidget::create(double labelXY)
{
  //目标靶
  targetSheet = new TargetSheet(this);
  targetSheet->setFixedSize(labelXY,labelXY);
  //垂直弹簧
  QSpacerItem *v_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding);

  //垂直布局
  QVBoxLayout *v_layout = new QVBoxLayout(this);

  //标签1-> 号靶    总环数 中靶数
  labelSum = new QLabel(this);
  labelSum->setFixedSize(labelXY,labelXY * 0.0857);
  labelSum->setText(QString::asprintf("1号靶    总环数:0  中靶数:0"));
  labelSum->setAlignment(Qt::AlignCenter);

  //标签2-> 连接状态
  labelState = new QLabel(this);
  labelState->setFixedSize(labelXY,labelXY * 0.0857);
  labelState->setText(QString::asprintf("未连接"));
  labelState->setAlignment(Qt::AlignCenter);

  setStyleSheet("QLabel{width: 100px;height: 100px;border: 1px solid green;font-family: 微软雅黑;border-radius: 10px;font-size: 23px;background-color: #cdcdcd}");

  //布局方式
  v_layout->addWidget(targetSheet);
  v_layout->addItem(v_spacer);
  v_layout->addWidget(labelSum);
  v_layout->addItem(v_spacer);
  v_layout->addWidget(labelState);

  //整体布局
  setLayout(v_layout);
}

void OneWidget::setSize(double width)
{
  currentWidth = width;
  targetSheet->setFixedSize(width,width);
  labelSum->setFixedSize(width,width * label_scaleBody);
  labelState->setFixedSize(width,width*label_scaleBody);
  scaleBody= (double)width/(double)label_img;

  emit mySignal(scaleBody);
}

void OneWidget::getMySignal()
{
  emit mySignalHoles(onlyHoleList);
}

void OneWidget::addHoles(QPointF point)
{
  onlyHoleList.append(point);
}

void OneWidget::clearHoles()
{
  onlyHoleList.clear();
}

