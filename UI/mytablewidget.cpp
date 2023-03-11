#pragma execution_character_set("utf-8")
#include "mytablewidget.h"

MyTableWidget::MyTableWidget(QWidget *parent) : QTableWidget(parent)
{
  this->setRowCount(10);
  this->setColumnCount(3);

  //隐藏垂直表头
  QHeaderView *header1 =   this->verticalHeader();
  header1->setHidden(true);

  this->horizontalHeader()->setStyleSheet("QHeaderView::section{font:19pt '宋体';};");
  this->setFixedSize(330,545);
  QStringList strList;
  strList<<tr("弹序")<<tr("环数")<<tr("方向");
  this->setHorizontalHeaderLabels(strList);
  this->setColumnWidth(0,110);
  this->setColumnWidth(1,100);
  this->setColumnWidth(2,100);

  for(int i = 0;i<10;i++)
    {
      this->setRowHeight(i,50);

    }
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->setStyleSheet("QTableWidget{width: 100px;height: 100px;border: 1px solid green;background: white;}""QScrollBar:vertical{max-width: 10px;max-height:10px;}"
                      "QScrollBar:horizontal{max-width: 10px;max-height:10px;}"
                      "QTableWidgetItem{color:black;font-size:25px;font-weight: simsun; font-family: 微软雅黑;font-bold;}");
}





