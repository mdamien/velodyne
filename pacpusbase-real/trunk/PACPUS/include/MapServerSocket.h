/*********************************************************************
// created:    2006/05/05 - 16:48
// filename:   MapServerSocket.h
//
// author:     Gerald Dherbomez
// 
// version:    $Id: MapServerSocket.h 261 2007-06-22 10:42:03Z gdherbom $
//
// purpose:    Class that will manage the connection of other 
//             applications. Protocol TCP/IP
//
// !!!!!!!!!!!!!!!! TODO !!!!!!!!!!!!!!!!!!
// supress the socket from the socket map when connection is closed
//
*********************************************************************/



#ifndef _MAPSERVERSOCKET_H_
#define _MAPSERVERSOCKET_H_


#include <qserversocket.h>
#include "MapServerSocketInterface.h"


typedef QMap<int,MapServerSocketInterface*> SocketMap; 


class MapServerSocket : public QServerSocket
{
  Q_OBJECT
public:
  MapServerSocket(int port, QObject *parent=0, const char *name=0);
  ~MapServerSocket();
  void newConnection(int socket); 
  
  MapServerSocketInterface* getInterface(int socketId); 
  void removeSocketInterface(int socketId); 
  
private:
  SocketMap socketMap_; 
};



#endif
