#include "onewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  OneWidget w;
  w.show();
  return a.exec();
}
