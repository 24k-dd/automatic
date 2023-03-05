////#include "sqlitetools.h"
//#include<bits/stdc++.h>

////带参数的构造函数，进行私有属性的初始化
//SQLiteTools::SQLiteTools(QString dbName, QString connName)
//{
//  //    //使用qRegisterMetaType对自定义类型 QList<QList> 进行注册
//  //    qRegisterMetaType<QList<QList>>("QList<QList>");
//  //    signalMessage = {};

//  dataBaseName = dbName;
//  connectionName = connName;


//}

//SQLiteTools::~SQLiteTools()
//{
//  db.close();
//}

////封装发送信号函数
////void SQLiteTools::emitSqliteSignal()
////{
////    emit mySqliteSignal(signalMessage);
////}

////根据自定义任务重载run()函数
////void SQLiteTools::run()
////{

////  //获取查询结果，如果结果是多行数据，可用while(query.next()){}遍历每一行
////    int rowCounts = getRowCounts();
////    int tableData[rowCounts][6];


////  int i = 0,m = 0,n = 0;
////  QSqlQuery query(db);
////  QString sql = QString(R"(SELECT * FROM bootData8 WHERE Table_Logic='%1';)").arg(0);

////  query.exec(sql);

////      while(query.next())
////      {
////          signalMessage = {};
////          QList<int> list = {};
////           for(int j = 0;j<6;j++)
////             {
////               tableData[i][j] = query.value(j).toInt();
////               list.append(query.value(j).toInt());
////             }
////          i++;
////          signalMessage.append(list);
////          emitSqliteSignal();

////        }


////}


//void SQLiteTools::initDataBase()
//{
//  //qDebug()<<QSqlDatabase::drivers();//打印驱动列表
//  //检测已连接的方式 - 自定义连接名
//  if(QSqlDatabase::contains(connectionName))
//    db = QSqlDatabase::database(connectionName);
//  else
//    db = QSqlDatabase::addDatabase("QSQLITE",connectionName);

//  //设置数据库路径，不存在则创建
//  db.setDatabaseName("./PtQt5_SQLite.db");
//  //db.setUserName("gongjianbo");  //SQLite不需要用户名和密码
//  //db.setPassword("qq654344883");

//  //打开数据库，验证是否成功
//  if(db.open()){
//      qDebug()<<"open success";
//      //关闭数据库
//      //        db.close();
//    }
//}

//bool SQLiteTools::openDateBase()
//{
//  if(!db.open())
//    {
//      qDebug() << "Error: Failed to open database." << db.lastError();
//      return false;
//    }
//  return true;
//}

//void SQLiteTools::closeDataBase()
//{
//  db.close();
//}

//void SQLiteTools::createTable()
//{
//  //如果不存在则创建my_table表,id自增,name唯一
//  const QString sql=R"(
//                    CREATE TABLE IF NOT EXISTS  my_table (
//                    ID   INTEGER   PRIMARY KEY   NOT NULL,
//                    PX   REAL   NOT NULL,
//                    PY   REAL   NOT NULL
//                    );)";
//  //QSqlQuery构造前，需要db已打开并连接
//  //未指定db或者db无效时使用默认连接进行操作
//  QSqlQuery query(db);
//  if(query.exec(sql)){
//      qDebug()<<"init table success";
//    }else{
//      //打印sql语句错误信息
//      qDebug()<<"init table error"<<query.lastError();
//    }
//}

////插入数据
//void SQLiteTools::insertRecord(int id, qreal px, qreal py)
//{
//  //方式一，绑定值，待定变量默认用问号占位,注意字符串也没有引号
//  //query.prepare(R"(INSERT INTO my_table(name,age) VALUES(?,?);)");
//  //query.addBindValue(name);
//  //query.addBindValue(age);
//  //query.exec();

//  QSqlQuery query(db);
//  QString sql = QString(R"(INSERT INTO my_table(ID, PX, PY) VALUES(%1, %2, %3);)")
//      .arg(id).arg(px).arg(py);
//  query.prepare(sql);
//  if(!query.exec())
//    {
//      qDebug() << query.lastError();
//    }
//  else
//    {
//      qDebug() << "inserted OK!";
//    }
//}

////删除数据
//void SQLiteTools::deleteRecord(int id)
//{
//  //方式一，直接执行SQL语句
//  //query.exec(QString(R"(DELETE FROM my_table WHERE name='%1';)")
//  //           .arg(name));
//  //方式二，绑定值，待定变量默认用问号占位
//  /*query.prepare(R"(DELETE FROM my_table WHERE name=?;)");
//    query.addBindValue(name);
//    query.exec();*/

//  QSqlQuery query(db);
//  QString sql = QString(R"(DELETE FROM my_table WHERE ID=%1;)").arg(id);
//  query.prepare(sql);
//  if(!query.exec())
//    {
//      qDebug() << query.lastError();
//    }
//  else
//    {
//      qDebug() << "deleted OK!";
//    }
//}

////更新数据
//void SQLiteTools::updateRecord(int id, qreal px, qreal py)
//{
//  //方式一，绑定值，待定变量默认问号，可自定义
//  /*query.prepare(R"(UPDATE my_table SET age=:age WHERE name=:name;)");
//    query.bindValue(":name",name);//通过自定义的别名来替代
//    query.bindValue(":age",age);
//    query.exec();*/

//  QSqlQuery query(db);
//  QString sql = QString(R"(UPDATE my_table SET PX=%2, PY=%3 WHERE ID=%1;)").arg(id).arg(px).arg(py);
//  query.prepare(sql);
//  if(!query.exec())
//    {
//      qDebug() << query.lastError();
//    }
//  else
//    {
//      qDebug() << "updated OK!";
//    }
//}


////查询数据
//void SQLiteTools::searchRecord(TableOne t1[])
//{
//  //获取查询结果，如果结果是多行数据，可用while(query.next()){}遍历每一行
//  QSqlQuery query(db);
//  QString sql = QString(R"(SELECT * FROM bullet_information_table WHERE Table_Logic = '%1';)").arg(0);

//  if(!query.exec(sql))
//    {
//      qDebug() << query.lastError();
//    }

//  int i = 0;
//  while(query.next())
//    {

//      t1[i].id = query.value(0).toInt();
//      t1[i].x = query.value(1).toInt();
//      t1[i].y = query.value(2).toInt();
//      t1[i].CN = query.value(3).toInt();
//      t1[i].direction = query.value(4).toInt();
//      t1[i].Table_Logic = query.value(5).toInt();
//      t1[i].group_no = query.value(6).toInt();

//      i++;
//    }

//}

////电量和状态查询
//void SQLiteTools::searchBatteryStatue(TableTwo t2[])
//{

//  //获取查询结果，如果结果是多行数据，可用while(query.next()){}遍历每一行
//  QSqlQuery query(db);
//  QString sql = QString(R"(SELECT * FROM targetConnection WHERE is_connection = '%1';)").arg(1);
//  if(!query.exec(sql))
//    {
//      qDebug() << query.lastError();

//    }

//  int i = 0;
//  while(query.next())
//    {
//      t2[i].addr = query.value(0).toInt();
//      t2[i].electric = query.value(1).toInt();
//      t2[i].connection = query.value(2).toInt();
//      i++;
//    }
//}

//////分组
////void SQLiteTools::searchFenZu(Table1 t1[])
////{
////  //获取查询结果，如果结果是多行数据，可用while(query.next()){}遍历每一行
////  QSqlQuery query(db);

////  if(baHao == 0 )
////    {
////      sql = QString(R"(SELECT * FROM bullet_information_table WHERE  id="%1";)").arg(baHao);
////      //        QMessageBox::information(this,tr("提示"),tr("请输入靶号!"),QMessageBox::Ok);
////    }else if(fenZu == 0)
////    {
////      sql = QString(R"(SELECT * FROM bullet_information_table WHERE group_no="%1";)").arg(fenZu);
////      //        QMessageBox::information(this,tr("提示"),tr("请输入分组!"),QMessageBox::Ok);
////    }else
////    {
////      sql = QString(R"(SELECT * FROM bullet_information_table WHERE  id="%1" and group_no="%2";)").arg(baHao).arg(fenZu);
////    }
////  query.exec(sql);

////  listRows1 = {};

////  while(query.next())
////    {
////      listRow1 = {};
////      for(int j = 0;j<7;j++)
////        {
////          listRow1.append(query.value(j).toInt());
////        }
////      listRows1.append(listRow1);
////    }

////  return listRows1;
////}




////获取记录行数
//int SQLiteTools::getRowCountsTable1()
//{
//  int counts = 0;
//  QSqlQuery query(db);
//  QString sql = QString(R"(SELECT * FROM bullet_information_table WHERE Table_Logic='%1';)").arg(0);

//  query.prepare(sql);
//  if(!query.exec())
//    {
//      qDebug() << query.lastError();
//    }
//  else
//    {
//      while(query.next())
//        counts++;
//    }
//  return counts;
//}

//int SQLiteTools::getRowCountsTable2()
//{
//  int counts = 0;
//  QSqlQuery query(db);
//  QString sql = QString(R"(SELECT * FROM targetConnection WHERE is_connection ='%1';)").arg(1);
//  query.prepare(sql);
//  if(!query.exec())
//    {
//      qDebug() << query.lastError();
//    }else
//    {
//      while(query.next())
//        counts++;
//    }
//  return counts;
//}



