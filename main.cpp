#include "widget.h"
#include"mylistwidget.h"
#include "mainwindow.h"
#include"loginwidget.h"
#include"mygradetablewidget.h"
#include"mywidget.h"

#include <QApplication>
#include<QDebug>
#include<QFile>
#include<QTextStream>


//void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
// static QMutex mutex;
// mutex.lock();
// QString text;
// switch (type)
// {
// case QtDebugMsg:
//  text = QString("Debug:");
//  break;
// case QtWarningMsg:
//  text = QString("Warning:");
//  break;
// case QtCriticalMsg:
//  text = QString("Critical:");
//  break;
// case QtFatalMsg:
//  text = QString("Fatal:");
// }
// QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
// QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
// QString current_date = QString("(%1)").arg(current_date_time);
// QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(current_date).arg(msg);
// QFile file("log.txt");
// file.open(QIODevice::WriteOnly | QIODevice::Append);
// QTextStream text_stream(&file);
// text_stream << message << "\r\n";
// file.flush();
// file.close();
// mutex.unlock();
//}


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QResource::registerResource("./plane.rcc");
  LoginWidget w;
  //  MyPeopleWidget w;
  //  MyPeopleInfo w;
  w.show();
  // 先注册自己的MsgHandler
  //  qInstallMessageHandler(outputMessage);
  return a.exec();
}
