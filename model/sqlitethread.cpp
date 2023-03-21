//#include "sqlitethread.h"
//#include<bits/stdc++.h>
////构造函数初始化
//SQLiteThread::SQLiteThread(QString connectName,QObject *parent):QThread(parent)
//{
//  //使用qRegisterMetaType对自定义类型 QList<QList> 进行注册
//  qRegisterMetaType<QList<QList<int>>>("QList<QList>");
//  //  signalMessage = {};
//  dbConnect = connectName;

//  //    m_timer.setInterval(800);

//  //    //开启定时器
//  //    m_timer.start();

//  //    //监听定时器发送的信号
//  //    connect(&m_timer,&QTimer::timeout,[=](){

//  //        update();

//  //      });

//}

////封装发送信号函数
////void SQLiteThread::emitSignal()
////{

////}

//////根据自定义任务重载run()函数
//void SQLiteThread::run()
//{

//  sqliteTools = new SQLiteTools(":/PtQt5_SQLite.db",dbConnect);

//  sqliteTools->initDataBase();

//  //获取数据量
//  cnt1 = sqliteTools->getRowCountsTable1();
//  cnt2 = sqliteTools->getRowCountsTable2();

//}

//void SQLiteThread::updateHoles(TableOne t1[])
//{
//  cnt1 = sqliteTools->getRowCountsTable1();
//  //查询表一数据
//  sqliteTools->searchRecord(t1);
//}

//void SQLiteThread::updateState(TableTwo t2[])
//{
//  cnt2 = sqliteTools->getRowCountsTable2();
//  //查询表二数据
//  sqliteTools->searchBatteryStatue(t2);
//}





