#ifndef MYGRADETABLEWIDGET_H
#define MYGRADETABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include<QTableWidgetItem>
#include<QGroupBox>
#include<QDebug>
#include<QSpacerItem>
#include<QtXlsx/QtXlsx>
#include<QDateEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QTime>
#include<QMessageBox>
#include<QLineEdit>
#include<QLabel>
#include <windows.h>
#include<QApplication>
#include<QStringList>
#include<QHeaderView>
#include<QDir>


#include <algorithm>

#include "Model.h"

class MyGradeTableWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MyGradeTableWidget(QWidget *parent = nullptr);
  ~MyGradeTableWidget();



  void closeEvent(QCloseEvent *event);

  void create();


public slots:


signals:
  void mySignalFlag();

  void mySignalData(int fenZu,int baHao,QString time);


private slots:
  void check_clicked();

  void updateGrade(const QVector<Check_Target_Table> &data);

  void dateChange(const QDate &date);

  void out_clicked();

private:


  QList<QList<int>>   huanShuList;                // 定义弹孔列表对象
  QList<QList<int>>   baHaoList;                // 定义靶号列表对象
  QList<QList<int>>   baHaoAndFenZu;

  QString currentDate;


  QXlsx::Document xlsx;

  int baHao = -1;
  int fenZu = -1;

  QTableWidgetItem *baWei = NULL;

  QTableWidgetItem *fenZuIndex =NULL;

  QTableWidgetItem *name = NULL;

  QTableWidgetItem *onlyHuanShu = NULL;

  QTableWidgetItem *allSum = NULL;

  QTableWidget *tableWidget = NULL;

  QLineEdit *lineEditGroup = NULL;
  QLineEdit *lineEditNum = NULL;

  QPushButton *btnCheck = NULL;

  QPushButton *btnOut = NULL;

  QDateEdit *dateEdit = NULL;
};


#endif // MYGRADETABLEWIDGET_H
