#include "mygradetablewidget.h"

MyGradeTableWidget::MyGradeTableWidget(QWidget *parent) :
  QWidget(parent,Qt::WindowStaysOnTopHint)
{

  //   setAttribute(Qt::WA_DeleteOnClose,false);

  int nWidth = GetSystemMetrics(SM_CXSCREEN);
  int nHeight = GetSystemMetrics(SM_CYSCREEN);

  resize(nWidth - 300,nHeight - 300);

  move(150,150);

  create();

  QDate m_date = QDate::currentDate();
  currentDate = m_date.toString("yyyy-MM-dd");

  connect(btnCheck,SIGNAL(clicked()),this,SLOT(check_clicked()));
  connect(btnOut,SIGNAL(clicked()),this,SLOT(out_clicked()));
  connect(dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(dateChange(QDate)));

}

MyGradeTableWidget::~MyGradeTableWidget()
{

}

//向tablewidget和excel中写入数据
void MyGradeTableWidget::addData()
{
  QList<int> list;

  int i;
  tableWidget->clear();
  if(fenZu != 0 || (fenZu != 0 && fenZu != 0) )
    {


      for(i = 1;i < 21;i++)
        {
          int flag = 3;
          int sum = 0;
          QList<QList<int>> m_list;
          foreach (list, baHaoAndFenZu) {
              if(list[0] == i)
                {
                  baWei = new QTableWidgetItem(QString::asprintf("%d号",i));
                  tableWidget->setItem(i - 1,0,baWei);
                  xlsx.write(i,2,QString::asprintf("%d号",baHao));
                  fenZuIndex = new QTableWidgetItem(QString::asprintf("%d",fenZu));
                  tableWidget->setItem(i - 1,1,fenZuIndex);
                  xlsx.write(i,3,QString::asprintf("%d",fenZu));
                  name = new QTableWidgetItem(QString::asprintf("火麟飞"));
                  tableWidget->setItem(i - 1,2,name);
                  xlsx.write(i ,4,QString::asprintf("火麟飞"));
                  m_list.append(list);
                }
            }

          foreach (list, m_list) {

              if(flag <  23)
                {
                  sum = sum + list[3];
                  onlyHuanShu = new QTableWidgetItem(QString::asprintf("%d",list[3]));
                  tableWidget->setItem(i -1  ,flag,onlyHuanShu);
                  xlsx.write(i ,flag + 2,QString::asprintf("%d",list[3]));
                  flag++;
                }

            }

          allSum = new QTableWidgetItem(QString::asprintf("%d",sum));
          tableWidget->setItem(i - 1 ,23,allSum);
          xlsx.write(i ,25,QString::asprintf("%d",sum));

        }
    }
  else if(baHao != 0){
      for(i = 1;i < 21;i++)
        {
          QList<QList<int>> m_list;
          QList<QList<int>> s_list;
          foreach (list, baHaoAndFenZu) {
              if(list[0] == baHao)
                {
                  m_list.append(list);
                }
            }
          foreach (list, m_list) {
              if(list[6] == i){
                  baWei = new QTableWidgetItem(QString::asprintf("%d号",baHao));
                  tableWidget->setItem(i - 1,0,baWei);
                  xlsx.write(i,2,QString::asprintf("%d号",baHao));
                  fenZuIndex = new QTableWidgetItem(QString::asprintf("%d",i));
                  tableWidget->setItem(i - 1,1,fenZuIndex);
                  xlsx.write(i,3,QString::asprintf("%d",i));
                  name = new QTableWidgetItem(QString::asprintf("火麟飞"));
                  tableWidget->setItem(i - 1,2,name);
                  xlsx.write(i ,4,QString::asprintf("火麟飞"));
                  s_list.append(list);
                }
            }

          int flag = 3;
          int sum = 0;
          foreach (list, s_list) {

              if(flag <  23)
                {
                  sum = sum + list[3];
                  onlyHuanShu = new QTableWidgetItem(QString::asprintf("%d",list[3]));
                  tableWidget->setItem(i -1  ,flag,onlyHuanShu);
                  xlsx.write(i ,flag + 2,QString::asprintf("%d",list[3]));
                  flag++;
                }

            }

          allSum = new QTableWidgetItem(QString::asprintf("%d",sum));
          tableWidget->setItem(i - 1 ,23,allSum);
          xlsx.write(i ,25,QString::asprintf("%d",sum));

        }
    }
}

void MyGradeTableWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();
}

void MyGradeTableWidget::create()
{
  setWindowTitle("成绩导出");
  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);
  QSpacerItem *v_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding);


  QGroupBox *groupBox = new QGroupBox(this);
  groupBox->setTitle("筛选");

  QLabel *labelGroup = new QLabel("分组:");
  QLabel *labelNum = new QLabel("靶号:");
  QLabel *labelTime = new QLabel("时间:");

  lineEditGroup = new QLineEdit();
  lineEditNum = new QLineEdit();

  dateEdit = new QDateEdit();

  dateEdit->setDate(QDate::currentDate());

  btnCheck = new QPushButton("查找");

  QHBoxLayout *h_layout_1 = new QHBoxLayout;

  h_layout_1->addItem(h_spacer);
  h_layout_1->addWidget(labelGroup);
  h_layout_1->addWidget(lineEditGroup);

  h_layout_1->addWidget(labelNum);
  h_layout_1->addWidget(lineEditNum);
  h_layout_1->addItem(h_spacer);
  h_layout_1->addWidget(labelTime);
  h_layout_1->addWidget(dateEdit);
  h_layout_1->addWidget(btnCheck);
  h_layout_1->addItem(h_spacer);

  groupBox->setLayout(h_layout_1);

  tableWidget = new QTableWidget(this);
  tableWidget->verticalHeader()->setHidden(true);
  tableWidget->setRowCount(20);
  tableWidget->setColumnCount(24);
  tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:19pt '宋体';};");
  QStringList strList;
  strList<<tr("靶号")<<tr("分组")<<tr("姓名");
  xlsx.write(1,1,"靶号");
  xlsx.write(1,2,"分组");
  xlsx.write(1,3,"姓名");
  for(int i = 1;i < 21;i++)
    {
      strList.append(QString::asprintf("%d",i));
    }
  strList<<tr("总环数");
  tableWidget->setHorizontalHeaderLabels(strList);

  QHBoxLayout *h_layout_2 = new QHBoxLayout;

  btnOut = new QPushButton("导出");

  h_layout_2->addItem(h_spacer);
  h_layout_2->addWidget(btnOut);
  h_layout_2->addItem(h_spacer);

  QVBoxLayout *v_layout_1 = new QVBoxLayout;

  v_layout_1->addLayout(h_layout_2);

  QVBoxLayout *v_layout_2 = new QVBoxLayout;

  v_layout_2->addWidget(groupBox);
  v_layout_2->addWidget(tableWidget);
  v_layout_2->addLayout(v_layout_1);

  setStyleSheet("QLabel,QPushButton,QLineEdit,QGroupBox,QDateEdit,QTableWidget{font-size:25px;font-bold;font-family: 微软雅黑;}");
  setLayout(v_layout_2);
}

//导出excel成绩表
void MyGradeTableWidget::out_clicked()
{
  QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间

  QString str = dateTime .toString("yyyy-MM-dd hh：mm：ss");//格式化时间

  QString  strm = QApplication::applicationDirPath();
  strm += "/导出数据";

  QDir path; // 创建一个QDir变量
  if (!path.exists(strm)) {  // 使用QDir成员函数exists()来判断文件夹是否存在
      path.mkdir(strm);  // 使用mkdir来创建文件夹
    }
  strm +=  "/" + str + "的打靶数据导出.xlsx";

  if(xlsx.saveAs(strm))
    QMessageBox::information(this,tr("提示"),tr("导出成功!"),QMessageBox::Ok);
  else
    QMessageBox::information(this,tr("提示"),tr("导出失败!"),QMessageBox::Ok);

}

void MyGradeTableWidget::dateChange(const QDate &date)
{
  QDate m_date = date;
  currentDate = m_date.toString("yyyy-MM-dd");

}

void MyGradeTableWidget::check_clicked()
{
  fenZu = lineEditGroup->text().toInt();
  baHao = lineEditNum->text().toInt();
  if(fenZu == 0)
    {
      fenZu = -1;
    }
  if(baHao == 0)
    {
      baHao = -1;
    }

  //  initTableWidget();

  emit mySignalData(fenZu,baHao,currentDate);

}

void MyGradeTableWidget::updateGrade(QJsonArray msg)
{

  int msgSize = msg.size();


  tableWidget->clear();

  QStringList strList;
  int i = 1;
  strList<<tr("靶号")<<tr("分组")<<tr("姓名");
  xlsx.write(1,1,"靶号");
  xlsx.write(1,2,"分组");
  xlsx.write(1,3,"姓名");
  for(i = 1;i < 21;i++)
    {
      strList.append(QString::asprintf("%d",i));
      xlsx.write(1,3+ i,QString::asprintf("%d",i));
    }
  strList<<tr("总环数");
   xlsx.write(1,3 + i,"总环数");
  tableWidget->setHorizontalHeaderLabels(strList);

  if(baHao != -1 && fenZu != -1)
    {
      QList<int> m_list;
      for(int i = 0;i < msgSize;i++)
        {
          QJsonObject jsonObject = msg[i].toObject();
          m_list.append(jsonObject["cylinder_number"].toInt());
        }

      baWei = new QTableWidgetItem(QString::asprintf("%d号",baHao));
      tableWidget->setItem(0,0,baWei);
      xlsx.write(2,1,QString::asprintf("%d号",baHao));
      fenZuIndex = new QTableWidgetItem(QString::asprintf("%d",fenZu));
      tableWidget->setItem(0,1,fenZuIndex);
      xlsx.write(2,2,QString::asprintf("%d",fenZu));
      if(msgSize > 0)
        {
          QJsonObject s_jsonObject = msg[0].toObject();
          name = new QTableWidgetItem(s_jsonObject["user_name"].toString());
          tableWidget->setItem(0,2,name);
          xlsx.write(2 ,3,s_jsonObject["user_name"].toString());
        }
      int sum = 0,i;
      for(i = 0;i < m_list.size() && i < 20;i++)
        {
          sum += m_list[i];
          onlyHuanShu = new QTableWidgetItem(QString::asprintf("%d",m_list[i]));
          tableWidget->setItem(0,i + 3,onlyHuanShu);
          xlsx.write(2 ,i + 4,QString::asprintf("%d",m_list[i]));
        }
      allSum = new QTableWidgetItem(QString::asprintf("%d",sum));
      tableWidget->setItem(0,23,allSum);
      xlsx.write(2 ,24,QString::asprintf("%d",allSum));
    }else if(baHao != -1 && fenZu == -1)
    {


      QVector<int> groupVec;
      QVector<QString> nameVec;

      for(int i = 0;i < msgSize;i++)
        {
          QJsonObject jsonObject = msg[i].toObject();
          groupVec.append(jsonObject["group_number"].toInt());
          nameVec.append(jsonObject["user_name"].toString());
        }

      for(int i=0;i<groupVec.size();i++){
          for(int j=i+1;j<groupVec.size();j++){
              if(groupVec[j]==groupVec[i]){
                  groupVec.remove(j);
                  j--;
                }
            }
        }

      for(int i=0;i<nameVec.size();i++){
          for(int j=i+1;j<nameVec.size();j++){
              if(nameVec[j]==nameVec[i]){
                  nameVec.remove(j);
                  j--;
                }
            }
        }

      for(int i = 0;i < groupVec.size();i++)
        {
          QList<int> m_list;
          for(int s = 0;s < msgSize;s++)
            {

              QJsonObject jsonObject = msg[s].toObject();
              if(groupVec[i] == jsonObject["group_number"].toInt())
                {
                  m_list.append(jsonObject["cylinder_number"].toInt());
                }

            }


          baWei = new QTableWidgetItem(QString::asprintf("%d号",baHao));
          tableWidget->setItem(i,0,baWei);
          xlsx.write(i + 2,1,QString::asprintf("%d号",baHao));


          fenZuIndex = new QTableWidgetItem(QString::asprintf("%d",groupVec[i]));
          tableWidget->setItem(i,1,fenZuIndex);
          xlsx.write(i+2,2,QString::asprintf("%d",groupVec[i]));
          if(nameVec.size() > i)
            {
              name = new QTableWidgetItem(nameVec[i]);
              tableWidget->setItem(i,2,name);
              xlsx.write(i+2 ,3,nameVec[i]);
            }else{
              name = new QTableWidgetItem("root");
              tableWidget->setItem(i,2,name);
              xlsx.write(i+2 ,3,"root");
            }

          int sum = 0;
          for(int j = 0;j < m_list.size() && j < 20;j++)
            {
              sum += m_list[j];
              onlyHuanShu = new QTableWidgetItem(QString::asprintf("%d",m_list[j]));
              tableWidget->setItem(i,j + 3,onlyHuanShu);
              xlsx.write(2 + i ,j+4,QString::asprintf("%d",m_list[j]));
            }
          allSum = new QTableWidgetItem(QString::asprintf("%d",sum));
          tableWidget->setItem(i,23,allSum);
          xlsx.write(2 + i ,24,QString::asprintf("%d",allSum));
        }
    }
  else if(fenZu != -1 && baHao == -1)
    {
      QList<int> m_list;
      QList<QString> list;
      QVector<int> numVec;
      QVector<QString> nameVec;
      for(int i = 0;i < msgSize;i++)
        {
          QJsonObject jsonObject = msg[i].toObject();
          numVec.append(jsonObject["addr"].toInt());
          nameVec.append(jsonObject["user_name"].toString());
        }

      for(int i=0;i<numVec.size();i++){
          for(int j=i+1;j<numVec.size();j++){
              if(numVec[j]==numVec[i]){
                  numVec.remove(j);
                  j--;
                }
            }
        }

      for(int i=0;i<nameVec.size();i++){
          for(int j=i+1;j<nameVec.size();j++){
              if(nameVec[j]==nameVec[i]){
                  nameVec.remove(j);
                  j--;
                }
            }
        }

      for(int i = 0;i < numVec.size();i++)
        {
          QList<int> m_list;
          for(int s = 0;s < msgSize;s++)
            {

              QJsonObject jsonObject = msg[s].toObject();
              if(numVec[i] == jsonObject["addr"].toInt())
                {
                  m_list.append(jsonObject["cylinder_number"].toInt());
                }

            }
          baWei = new QTableWidgetItem(QString::asprintf("%d号",numVec[i]));
          tableWidget->setItem(i,0,baWei);
          xlsx.write(i + 2,1,QString::asprintf("%d号",numVec[i]));


          fenZuIndex = new QTableWidgetItem(QString::asprintf("%d",fenZu));
          tableWidget->setItem(i,1,fenZuIndex);
          xlsx.write(i+2,2,QString::asprintf("%d",fenZu));

          if(nameVec.size() > i)
            {
              name = new QTableWidgetItem(nameVec[i]);
              tableWidget->setItem(i,2,name);
              xlsx.write(i+2 ,3,nameVec[i]);
            }else{
              name = new QTableWidgetItem("root");
              tableWidget->setItem(i,2,name);
              xlsx.write(i+2 ,3,"root");
            }
                int sum = 0;
          for(int j = 0;j < m_list.size() && j < 20;j++)
            {
              sum += m_list[j];
              onlyHuanShu = new QTableWidgetItem(QString::asprintf("%d",m_list[j]));
              tableWidget->setItem(i,j + 3,onlyHuanShu);
              xlsx.write(2 + i ,j+4,QString::asprintf("%d",m_list[j]));
            }
          allSum = new QTableWidgetItem(QString::asprintf("%d",sum));
          tableWidget->setItem(i,23,allSum);
          xlsx.write(2 + i ,24,QString::asprintf("%d",allSum));
        }
    }
}
