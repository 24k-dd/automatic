#include "widget.h"
#include"mylistwidget.h"
#include "mainwindow.h"
#include"loginwidget.h"
#include"mygradetablewidget.h"
#include"mywidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  LoginWidget w;
//  MyListWidget w;
//  MyWidget w;
//  MainWindow w;
  w.show();
  return a.exec();
}
