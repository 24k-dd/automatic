#ifndef TARGETSHEET_H
#define TARGETSHEET_H

#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QMetaType>
#include <QTimer>
#include<QTime>
#include <windows.h>
#include<QThread>
#include<thread>

#include"Model.h"

class TargetSheet : public QLabel
{
  Q_OBJECT

public:
  explicit TargetSheet(QWidget *parent = nullptr);

  void create();
  //重载父类绘制方法
private:
  void paintEvent(QPaintEvent *event) override;

  //弹孔更新槽函数
public slots:
  void updateHoles(QList<QPointF>  msg);
  void updateSize(double size);

private:
  QImage          backgroundImage ;        // 定义靶纸背景对象
  QPixmap         bulletImage;             // 定义弹孔图对象
  QPointF          bulletCenter;            // 弹孔图片中心坐标

  QTimer m_timer;

  QList<QPointF>   onlyHoleList = {};                // 定义每个靶对象

};

#endif // TARGETSHEET_H
