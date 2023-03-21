//#ifndef SQLITETHREAD_H
//#define SQLITETHREAD_H

//#include <QTimer>
//#include <QObject>
//#include <QThread>
//#include <QPoint>
//#include <QDebug>
//#include <QMetaType>
//#include<QtSql>
//#include <QSqlDatabase>
//#include <QSqlError>
//#include <QSqlQuery>
//#include<QMutex>

//#include"sqlitetools.h"
//#include"Model.h"


//class SQLiteThread : public QThread
//{
//  Q_OBJECT

//signals:

//public:
//  explicit SQLiteThread(QString connectName,QObject *parent = nullptr);

//private:
//  void run() override; //QThread的虚函数，线程处理函数,不能直接调用，通过start()间接调用
//public:
//  //更新结构体1数据
//  void updateHoles(TableOne t1[]);
//  //更新结构体2数据
//  void updateState(TableTwo t2[]);

//private:

//  SQLiteTools *sqliteTools = NULL;

//  QMutex mutex;

//  QString dbConnect;

//public:

//  int cnt1 = 0;
//  int cnt2 = 0;

//};

//#endif // SQLITETHREAD_H
