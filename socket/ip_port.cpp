#include "ip_port.h"

ip_port::ip_port()
{

  QString  strm = QApplication::applicationDirPath();
  strm += "/config/config.yml";
  QFile file(strm);

  if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
  qDebug()<<"Can't open the file!";
  QString temp = "";
  while(!file.atEnd())
    {
      QByteArray line = file.readLine();
      QString str(line);
        if(str.indexOf(QRegExp("port")) != -1)
        {
            temp = "";
            for(int j = 0;j < str.length();j++)
              {
                if(str[j] <= '9' && str[j] >= '0')
                  {
                    temp.append(str[j]);
                  }
              }
        }
    }
      port = temp.toInt();

     ip = getMyIpString();

//  port = 32728;

// ip = "192.168.43.110";

    qDebug()<<"本机:"<<ip<<" "<<port;

}

QString ip_port::getMyIpString()
{
    QString ip_address;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses(); // 获取所有ip
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {

        QHostAddress ipAddr = ipAddressesList.at(i);
        if ((ipAddr.protocol() == QAbstractSocket::IPv4Protocol))// 筛选出ipv4
        {

            if (!ipAddr.toString().startsWith("169"))// 过滤掉网卡，路由器等的ip
            {
                ip_address = ipAddr.toString();
                break;
            }
        }
    }
    if (ip_address.isEmpty())
        ip_address = QHostAddress(QHostAddress::LocalHost).toString();
    return ip_address;
}
