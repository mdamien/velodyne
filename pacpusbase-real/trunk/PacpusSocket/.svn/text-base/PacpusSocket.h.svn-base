/*********************************************************************
//  created:    2012/03/01 - 14:06
//  filename:   PacpusSocket.h
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:    Create network socket if needed in Pacpus
//
*********************************************************************/

#include <qudpsocket.h>

#include "Pacpus/kernel/Log.h"
#include "Pacpus/kernel/ComponentBase.h" 
#include "Pacpus/kernel/ComponentFactory.h" 

// Export macro for PacpusSocket DLL for Windows only
#ifdef WIN32
#   ifdef PACPUSSOCKET_EXPORTS
        // make DLL
#       define PACPUSSOCKET_API __declspec(dllexport)
#   else
        // use DLL
#       define PACPUSSOCKET_API __declspec(dllimport)
#   endif
#else
    // On other platforms, simply ignore this 
#   define PACPUSSOCKET_API 
#endif

class QByteArray;

namespace pacpus {

class PACPUSSOCKET_API Client
{
public: 
    /// Constructor
    Client();
    Client(QHostAddress address, quint16 port) {address_ = address; port_ = port;};
    /// Destructor
    ~Client();
    
    QHostAddress address_;
    quint16 port_;
    
    QHostAddress getAddress() {return address_;};    
    quint16 getPort() {return port_;};
};

class PACPUSSOCKET_API PacpusSocket
        : public QObject
        , public ComponentBase 
{ 
  Q_OBJECT

public: 
    /// Constructor
    PacpusSocket(QString name);

    /// Destructor
    ~PacpusSocket();
    PacpusSocket * getSocket() {return this;}

public Q_SLOTS:
    /// Slot de lecture des paquets envoys pour tests
    void readPendingDatagrams();

    /// Slot d'envoie des paquets
    void sendDatagrams(QString frame);
    void sendDatagrams(QByteArray frame);
    
Q_SIGNALS:
    void newDatagram(QByteArray datagram);
    void newQString(QString string);

protected:
    // The 3 virtual methods relative to the ComponentBase inheritance
    virtual void startActivity();
    virtual void stopActivity();
    virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

    QUdpSocket * udpSocket_; //TODO Mode TCP

    quint16 port2bind_;
    quint16 port2send_;
    QHostAddress address2send_;
    QString socketType_;         
      
    QList <Client *> listClients;
};

} // namespace pacpus
