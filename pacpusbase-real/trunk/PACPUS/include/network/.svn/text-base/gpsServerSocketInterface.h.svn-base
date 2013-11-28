#include <qsocket.h>


class GpsServerSocketInterface : public QSocket
{
  Q_OBJECT
public:
  GpsServerSocketInterface(int socket);
  
private slots:
  void readClient(); /*!< identify the requested frame and send the data to the client */
  
};
