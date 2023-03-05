#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include<QTableWidgetItem>
#include<QHeaderView>

class MyTableWidget : public QTableWidget
{
  Q_OBJECT
public:
  explicit MyTableWidget(QWidget *parent = nullptr);

};

#endif // MYTABLEWIDGET_H
