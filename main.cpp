#include "widget.h"
//#include"mylistwidget.h"
#include "mainwindow.h"
#include"loginwidget.h"
#include"mygradetablewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  LoginWidget w;
  w.show();
  return a.exec();
}
