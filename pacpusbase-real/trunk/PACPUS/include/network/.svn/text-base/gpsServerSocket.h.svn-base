//////////////////////////////////////////////////////////////////////////
// Gerald Dherbomez
//////////////////////////////////////////////////////////////////////////
//  [10/17/2005]
//////////////////////////////////////////////////////////////////////////


#include <qserversocket.h>
#include "../../include/kernel/pacpus.h"


class GpsServerSocket : public QServerSocket
{
  Q_OBJECT
public:
  GpsServerSocket(int gpsServerSocketPort = 1000);  
  ~GpsServerSocket(); 

  void customEvent(QCustomEvent* e); /*!< new data received form the processing thread */
  void newConnection(int socket); 

private:
  trame_gga_dbl ggaData;
  trame_gsa gsaData; 
  trame_gst gstData;
  trame_gsv gsvData;
  trame_hdt hdtData;
  trame_rmc rmcData; 
  trame_rot rotData;
  trame_vtg vtgData;
  trame_zda zdaData; 

};