 
#include "kernel/ComponentBase.h" 
#include "kernel/ComponentFactory.h" 
 
#include <QUdpSocket> 
 
 
 
class OmasUdpServer : public QObject, public ComponentBase 
{ 
  Q_OBJECT 
 
public: 
  // Constructor 
  OmasUdpServer(QString name); 
 
  // Destructor 
  ~OmasUdpServer(); 
 
public slots : 
 
  //Slot de lecture des paquets envoyés pour tests 
  void readPendingDatagrams(); 
 
  //Slot d'envoie des paquets 
  void sendDatagrams(QString frame); 
 
protected: 
 
  // The 3 virtual methods relative to the ComponentBase inheritance 
  virtual void startActivity();
  virtual void stopActivity();
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
 
	QUdpSocket* udpSocket_;
  
	QHostAddress omasSender_;
	quint16 omasSenderPort_;
};
