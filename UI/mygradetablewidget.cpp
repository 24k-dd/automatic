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

  initTableWidget();

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
  tableWidget->setRowCount(20);
  tableWidget->setColumnCount(24);
  tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:19pt '宋体';};");

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

void MyGradeTableWidget::initTableWidget()
{
  QStringList strList;
  strList<<tr("靶号")<<tr("分组")<<tr("姓名");

  for(int i = 1;i < 21;i++)
    {
      strList.append(QString::asprintf("%d",i));
    }
  strList<<tr("总环数");
  tableWidget->setHorizontalHeaderLabels(strList);

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

  emit mySignalData(fenZu,baHao,currentDate);

}
