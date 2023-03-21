#ifndef IP_PORT_H
#define IP_PORT_H

#include <QString>
#include<QFile>
#include<qDebug>
#include<QApplication>
#include<QHostAddress>
#include<QNetworkInterface>
#include<QRegExp>

class ip_port
{

public:
  ip_port();

  QString ip;
  int port;

  QString getMyIpString();

};

#endif // IP_PORT_H
