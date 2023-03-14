#include "mycodesetwidget.h"

MyCodeSetWidget::MyCodeSetWidget(QWidget *parent) :
  QWidget(parent,Qt::WindowStaysOnTopHint)
{

  //创建布局
  create();

  connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Slots()));
}

void MyCodeSetWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalFlag();

}

void MyCodeSetWidget::create()
{
  setWindowTitle("地址设置");
  setFixedSize(700,200);

  setAttribute(Qt::WA_DeleteOnClose,false);

  QLabel *label_old = new QLabel("原编码:");

  QLabel *label_new = new QLabel("新编码:");

  lineEdit = new QLineEdit("1");
  lineEdit->setFixedSize(70,60);

  lineEdit->setReadOnly(true);
  lineEdit->setAlignment(Qt::AlignCenter);

  comboBox  = new QComboBox();
  comboBox->setFixedSize(110,60);

  QListView* listView1 = new QListView();
  comboBox->setView(listView1);
  //按钮美化
  comboBox->setStyleSheet("QComboBox QAbstractItemView::item{height:30px;}");
  comboBox->setFont(QFont(QString::asprintf("Cambria Math"), 18, QFont::Black));

  for(int i = 1;i <= 20;i++ )
    {
      strList.append(QString::asprintf("%d",i));
    }
  comboBox->addItems(strList);

  btn1 = new QPushButton("发送");
  btn1->setFixedSize(180,60);

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum);

  QHBoxLayout *layout = new QHBoxLayout();

  layout->addItem(h_spacer);
  layout->addWidget(label_old);
  layout->addItem(h_spacer);
  layout->addWidget(lineEdit);
  layout->addItem(h_spacer);
  layout->addWidget(label_new);
  layout->addItem(h_spacer);
  layout->addWidget(comboBox);
  layout->addItem(h_spacer);
  layout->addWidget(btn1);
  layout->addItem(h_spacer);
  setLayout(layout);

  setStyleSheet("QLabel,QPushButton,QLineEdit{width: 100px;height: 100px;font-size: 30px;font-bold;font-family: 微软雅黑;}");
}


//发送原新编码
void MyCodeSetWidget::btn1Slots()
{

  int yuan = flag;
  int xin = comboBox->currentIndex() + 1;

  emit mySignalCodeSetting(yuan,xin);

}

//得到当前靶位
void MyCodeSetWidget::getIndex(int index)
{
  flag = index + 1;
  lineEdit->setText(QString::asprintf("%d",flag));

}



