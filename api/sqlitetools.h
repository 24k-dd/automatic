//#ifndef SQLITECLASS_H
//#define SQLITECLASS_H
//#include <QSql>
//#include <QSqlDatabase>
//#include <QDebug>
//#include <QSqlError>
//#include <QSqlQuery>
//#include<QList>
//#include<QMessageBox>

//#include"api/Model.h"

//class SQLiteTools
//{

//    private:
//        QSqlDatabase    db;                 //定义一个私有的数据库连接对象
//        QString         connectionName;     //定义数据库连接名
//        QString         dataBaseName;       //定义用于建立连接的数据库名或路径
////         QList<QList> signalMessage;
////         QList<int> listRow;
////         QList<QList<int>> listRows;
////        QList<QList<int>> listRows1;
////        QList<int> listRow1;
////         QList<int> listRowBattery;
////         QList<QList<int>> listRowsBattery;
//         QString sql;
//         QList<int> listRowFenZu;
//         QList<QList<int>> listRowsFenZu;

//    public:
//        SQLiteTools(QString dbName, QString connName);
//        ~SQLiteTools();

//        /**
//         * @brief initDataBase 初始化数据库连接
//         * @param
//         */
//        void initDataBase(void);
//        /**
//         * @brief openDateBase 打开数据库
//         * @param
//         */
//        bool openDateBase(void);
//        /**
//         * @brief closeDataBase 关闭数据库
//         * @param
//         */
//        void closeDataBase(void);
//        /**
//         * @brief createTable 创建数据表
//         * @param
//         */
//        void createTable(void);
//        /**
//         * @brief insertRecord 插入记录
//         * @param
//         */
//        void insertRecord(int id, qreal px, qreal py);
//        /**
//         * @brief deleteRecord 删除记录
//         * @param
//         */
//        void deleteRecord(int id);
//        /**
//         * @brief updateRecord 更新记录
//         * @param
//         */
//        void updateRecord(int id, qreal px, qreal py);
//        /**
//         * @brief searchRecord 查询记录
//         * @param
//         */
//        void searchRecord(TableOne t1[]);
//        /**
//         * @brief getRowCounts 获取所有记录数目
//         * @param
//         */
//        void searchBatteryStatue(TableTwo t2[]);

////        void searchFenZu(Table1 t2[]);

//        int getRowCountsTable1();

//        int getRowCountsTable2();
//};

//#endif // SQLITECLASS_H
