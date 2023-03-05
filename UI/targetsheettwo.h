#ifndef TARGETSHEETTWO_H
#define TARGETSHEETTWO_H

#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QMetaType>
#include <QTimer>
#include<QTime>
#include <windows.h>
#include<QFont>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>


class TargetSheetTwo : public QLabel
{
  Q_OBJECT

public:
  explicit TargetSheetTwo(QWidget *parent = nullptr);
  ~TargetSheetTwo();

  void create();
  //重载父类绘制方法
private:
  void paintEvent(QPaintEvent *event) override;

  //弹孔更新槽函数
public slots:
  void updateHoles(QList<QPointF>  msg);
private:
  QImage          backgroundImage ;        // 定义靶纸背景对象
  QPixmap         bulletImage;             // 定义弹孔图对象
  QPixmap         lastBulletImage;
  QPointF          bulletCenter;            // 弹孔图片中心坐标

  QTimer m_timer;


  QList<QPointF>   onlyHoleList = {};                // 定义每个靶号对象

};


#endif // TARGETSHEETTWO_H
