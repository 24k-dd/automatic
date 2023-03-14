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

  //  双击放大
  connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(listWidgetDoubleClicked(QListWidgetItem*)));

  //单击选中
  connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listWidgeSelectionChanged(QListWidgetItem*)));

}

MyListWidget::~MyListWidget()
{

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
  for(int i = 0; i < array_size - 1;i++){

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

    }
}

int MyListWidget::getIndex()
{
  return index2;
}

//滚轮响应时间
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

  //获取放缩比例
  scaleBody= (double)currentWidth/(double)801;

  //对每个靶标重新进行大小设置
  for(int i = 0;i < array_size - 1;i++)
    {

      oneWidget[i]->setSize(currentWidth);

      item[i]->setSizeHint(QSize((int)(currentWidth*1.051),(int)(currentWidth*1.291)));
      setItemWidget(item[i],oneWidget[i]);
    }
  //重新排列
  create();
}

//传递子弹数据
void MyListWidget::passHolesData(QJsonArray msg)
{
  //总环数 中靶数
  int sum = 0,zhongBa = 0;
  //确定数组大小
  int msgSize = msg.size();
  if(msgSize > 0)
    {
      QJsonObject s_jsonObject = msg[0].toObject();
      s_index = s_jsonObject["addr"].toInt() - 1;
    }
  oneWidget[s_index]->clearHoles();
  for(int i = 0;i < msgSize;i++)
    {
      QJsonObject jsonObject = msg[i].toObject();

      //对数据进行存储
      double x = jsonObject["x"].toDouble();
      double y = jsonObject["y"].toDouble();
      double px = x * scaleBody;
      double py = (801 - y)*scaleBody;

      //中靶数 中环数 -1指脱靶
      if(jsonObject["direction"].toInt() != -1)
        {
          zhongBa++;
          sum += jsonObject["cylinder_number"].toInt();
        }
      oneWidget[s_index]->addHoles(QPointF(px,py));
    }

  //对靶标信息进行设置
  oneWidget[s_index]->labelSum->setText(QString::asprintf("%1号靶 总环数:%2 中靶数:%3" ).arg(s_index + 1).arg(sum).arg(zhongBa));

  //触发信号
  oneWidget[s_index]->getMySignal();

}


void MyListWidget::passStateData(QVector<int> vecState)
{
  for(int i = 1;i < array_size;i++)
    {
      int s_index = i - 1;
      if(vecState[i] == flag_0 || vecState[i] == flag_1)
        {
          oneWidget[s_index]->labelState->setText(QString::asprintf("未连接"));

          if(currentWidth < 300)
            {
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: #cdcdcd}");
            }else{
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: #cdcdcd}");
            }
        }else if(vecState[i] == flag_2)
        {
          oneWidget[s_index]->labelState->setText(QString::asprintf("校准中"));

          if(currentWidth < 300)
            {
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: #89fff2}");
            }else{
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: #89fff2}");
            }
        }else{
          oneWidget[s_index]->labelState->setText(QString::asprintf("已连接"));
          //设置字体大小
          if(currentWidth < 300)
            {
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: #43ff19}");
            }else{
              oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: #43ff19}");
            }
        }
    }
}

 //传递电量数据
void MyListWidget::passBatteryData(QVector<double> msg)
{
  for(int i = 1;i < msg.size();i++)
    {
      int s_index = i - 1;
      if(msg[i] < 12.5 && msg[i] != 0){

                oneWidget[s_index]->labelState->setText(QString::asprintf("电量过低"));
                if(currentWidth < 300)
                  {
                    oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 15px;background-color: red}");
                  }else{
                    oneWidget[s_index]->labelState->setStyleSheet("QLabel{font-size: 23px;background-color: red}");
                  }
        }

    }
}


//详细信息界面
void MyListWidget::listWidgetDoubleClicked(QListWidgetItem *item)
{
  index2 = currentRow();
  emit mySignalDoubleIndex(index2);
}

//添加背景阴影
void MyListWidget::listWidgeSelectionChanged(QListWidgetItem* ite)
{
  //标记
  index3 = index2;

  index2 = currentRow();

  //对当前选中靶标进行深度显示
  item[index2]->setBackgroundColor(QColor("#a8a8a8"));
  if(index3 > -1 && index3 < 21 && index2 != index3)
    {
      //颜色复位
      item[index3]->setBackgroundColor(QColor(Qt::white));
    }
  emit mySignalIndex(index2);
}







