#include "mylistwidget.h"

MyListWidget::MyListWidget(QListWidget *parent)
  : QListWidget(parent)
{
  create();

  //获取电脑宽度
  screenWidth = GetSystemMetrics(SM_CXSCREEN);

  //比例系数
  labelXY = screenWidth/5.5;

  currentWidth = labelXY;

  scaleBody= (double)labelXY/(double)801;

  initListWidget();



}

MyListWidget::~MyListWidget()
{

  delete [] oneWidget;
  delete [] item;

}

void MyListWidget::create()
{
  setWrapping(true);
  setViewMode(QListView::IconMode);
  setFlow(QListWidget::LeftToRight);
  setResizeMode(QListView::Adjust);
  //最大化
  setWindowState(Qt::WindowMaximized);
}

void MyListWidget::initListWidget()
{
  for(int i = 0; i < targetShu;i++){

      //创建一个靶标对象
      oneWidget[i] = new OneWidget(labelXY,i);

      item[i] = new QListWidgetItem();

      //设置item大小
      item[i]->setSizeHint(QSize((int)(labelXY*1.051),(int)(labelXY*1.281)));

      //向QListWidget里添加item
      addItem(item[i]);

      //将刚添加的item设置为widget
      setItemWidget(item[i],oneWidget[i]);

      oneWidget[i]->labelSum->setText(QString::asprintf("%1号靶 总环数:%2 中靶数:%3" ).arg(i + 1).arg(0).arg(0));

      connect(this,SIGNAL(mySignal(QList<QPointF>)),oneWidget[i]->targetSheet,SLOT(updateHoles(QList<QPointF>)));
    }


}

void MyListWidget::wheelEvent(QWheelEvent *event)
{
  QPoint numDegrees;                                     // 定义指针类型参数numDegrees用于获取滚轮转角
  numDegrees = event->angleDelta();                      // 获取滚轮转角
  double step = 0;                                          // 设置中间参数step用于将获取的数值转换成整数型
  if (!numDegrees.isNull())                              // 判断滚轮是否转动
    {
      step = numDegrees.y();                             // 将滚轮转动数值传给中间参数step
    }
  event->accept();                                       // 获取事件

  currentWidth += step/20;                                  // 对当前图像的高累加

  //固定最大最小
  if(currentWidth < 240)
    {
      currentWidth = currentWidth - step/20;
    }else if(currentWidth > 810)
    {
      currentWidth = currentWidth - step/20;
    }
  scaleBody= (double)currentWidth/(double)801;
  for(int i = 0;i < targetShu;i++)
    {

      oneWidget[i]->setSize(currentWidth);

      item[i]->setSizeHint(QSize((int)(currentWidth*1.051),(int)(currentWidth*1.291)));
      setItemWidget(item[i],oneWidget[i]);
    }
  //重新排列
  create();
}

//传递子弹数据
void MyListWidget::passHolesData(QList<QList<QString>> msg)
{

  QList<QPointF>   onlyHoleList = {};

  //总环数，中靶数
  int sum = 0,zhongBa = 0,s_index = 0;

  int num = msg.size();

  //遍历表一全部数据
  for(int k = 0;k < num;k++)
    {

      //对数据进行存储
      double x = msg[k][1].toDouble();
      double y = msg[k][2].toDouble();
      double px = (double)(x)*scaleBody;
      double py = (double)(801 - y)*scaleBody;

      onlyHoleList.append(QPointF(px,py));

      //中靶数 中环数 -1指脱靶
      if(msg[k][4].toInt() != -1)
        {
          zhongBa++;
          sum += msg[k][3].toInt();
        }

      s_index = msg[k][0].toInt() - 1;
    }
  oneWidget[s_index]->labelSum->setText(QString::asprintf("%1号靶 总环数:%2 中靶数:%3" ).arg(s_index + 1).arg(sum).arg(zhongBa));

  //设置字体大小
  if(currentWidth < 300)
    {
      oneWidget[s_index]->labelSum->setStyleSheet("QLabel{font-size: 15px;background-color: #cdcdcd}");

    }else{
      oneWidget[s_index]->labelSum->setStyleSheet("QLabel{font-size: 23px;background-color: #cdcdcd}");
    }

  emit mySignal(onlyHoleList);

}


//传递靶标状态
void MyListWidget::passStateData(QVector<int> msg)
{

  for(int i = 1;i < msg.size();i++)
    {
      int s_index = i - 1;
      if(msg[i] == 1)
        {
          oneWidget[s_index]->labelState->setText(QString::asprintf("未连接"));

        }else{
          oneWidget[s_index]->labelState->setText(QString::asprintf("已连接"));
        }
    }
}

void MyListWidget::passBatteryData(QVector<double> msg)
{

  for(int i = 1;i < msg.size();i++)
    {
      int s_index = i - 1;
      double electric = msg[i] / 10 * 1.0;
      if(electric >= 12.5)
        {
          //设置字体大小
          if(currentWidth < 300)
            {
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: #43ff19}");
            }else{
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: #43ff19}");
            }


        }else if(electric < 12.5 && msg[i] != 1){
          if(currentWidth < 300)
            {
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: red}");
            }else{
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: red}");
            }
        }else{

          //设置字体大小
          if(currentWidth < 300)
            {
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: #cdcdcd}");
            }else{
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: #cdcdcd}");
            }

        }
    }
}




