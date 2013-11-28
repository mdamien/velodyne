// gpsClientSocket.h

#ifndef _GPSCLIENTSOCKET_H_
#define _GPSCLIENTSOCKET_H_

#include <qapplication.h>
#include <qsocket.h>


class gpsClientSocket : public QObject
{
  Q_OBJECT
public:
  gpsClientSocket(); 
  ~gpsClientSocket(); 
  
private slots:
  void connectToServer(QString host, int port);
  void socketConnected();
  void socketConnectionClosed();
  void socketReadyRead();  
  void socketError(int); 
  
private: 
  QSocket *socket; 
};


#endif // _GPSCLIENTSOCKET_H_