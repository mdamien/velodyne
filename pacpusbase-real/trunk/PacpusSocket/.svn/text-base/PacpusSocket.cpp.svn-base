/*********************************************************************
//  created:    2012/03/01 - 14:06
//  filename:   PacpusSocket.cpp
//
//  author:     Pierre Hudelaine
//              Copyright Heudiasyc UMR UTC/CNRS 7253
// 
//  version:    $Id: $
//
//  purpose:    Create network socket if needed in Pacpus
//
*********************************************************************/

#include "PacpusSocket.h" 

#include <qbuffer.h>
#include <qbytearray.h>


using namespace pacpus;


DECLARE_STATIC_LOGGER("pacpus.base.PacpusSocket");


//////////////////////////////////////////////////////////////////////////
// Construct the factory
//////////////////////////////////////////////////////////////////////////
static ComponentFactory <PacpusSocket> sFactory("PacpusSocket");  


//////////////////////////////////////////////////////////////////////////
// C
//////////////////////////////////////////////////////////////////////////
PacpusSocket::PacpusSocket(QString name)
    : ComponentBase(name) 
{
} 


//////////////////////////////////////////////////////////////////////////
// Destructor
//////////////////////////////////////////////////////////////////////////
PacpusSocket::~PacpusSocket() 
{
}


//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to pass the XML parameters to the 
// component 
//////////////////////////////////////////////////////////////////////////
ComponentBase::COMPONENT_CONFIGURATION  PacpusSocket::configureComponent(XmlComponentConfig config) 
{ 

	socketType_ = param.getProperty("typeSocket");
	
	if (socketType_ == "client" || socketType_ == "Client")
	{
	    address2send_.setAddress(param.getProperty("address"));
	    port2send_ = param.getProperty("port").toUInt();
	    socketType_ = "client";		
	}
	else if (socketType_ == "server" || socketType_ == "Server")
	{
	    port2bind_ = param.getProperty("port").toUInt();
	    socketType_ = "server";
	}
	else
	{
	    qDebug("typeSocket incorrect, become client");
	    address2send_.setAddress(param.getProperty("address"));
	    port2send_ = param.getProperty("port").toUInt();
	    socketType_ = "client";
	}
	
	return ComponentBase::CONFIGURED_OK; 
} 


//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to start the component
//////////////////////////////////////////////////////////////////////////
void PacpusSocket::startActivity() 
{ 
	if (!(udpSocket_ = new QUdpSocket()))
		qFatal("Failed to init UDP socket!");
  
 	if (socketType_ == "server")
	{
	    if (udpSocket_->bind(QHostAddress::Any, port2bind_, QUdpSocket::DontShareAddress))
		qDebug() << "Socket bound for server on port " << port2bind_;
	    else
		qWarning() << "Failed to bind socket on port " << port2bind_;
	}
	else if (socketType_ == "client")
	{
	  if (udpSocket_->bind(QHostAddress::Any, port2send_ + 1, QUdpSocket::DontShareAddress))
		qDebug() << "Socket bound for client on port " << port2send_ + 1;
	    else
		qWarning() << "Failed to bind socket" << port2send_ + 1;
	}
	    
	connect(udpSocket_, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}


void PacpusSocket::sendDatagrams(QString frame) 
{ 
	int sent=0;
	
	if (socketType_ == "client")
	{
	    if ((sent = udpSocket_->writeDatagram(frame.toLocal8Bit(), address2send_, port2send_)) == -1) 
		qDebug() << "Failed to send the frame: " << address2send_ << port2send_ << frame << endl; 
	    else 
		qDebug() << "TO NETWORK:" << address2send_ << port2send_ << frame << "size" << sent;
	}
	else if (socketType_ == "server")
	{
	    for (int i = 0; i < listClients.size(); i++)
	    {
		if ((sent = udpSocket_->writeDatagram(frame.toLocal8Bit(), listClients[i]->getAddress(), listClients[i]->getPort())) == -1) 
		    qDebug() << "Failed to send the frame: " << listClients[i]->getAddress() << listClients[i]->getPort() << frame << endl; 
		else 
		    qDebug() << "TO NETWORK:" << listClients[i]->getAddress() << listClients[i]->getPort() << frame << "size" << sent;  	
	    }
	}
} 


void PacpusSocket::sendDatagrams(QByteArray frame) 
{ 
	int sent=0;
	
	if (socketType_ == "client")
	{
	    if ((sent = udpSocket_->writeDatagram(frame, address2send_, port2send_)) == -1) 
		qDebug() << "Failed to send the frame: " << address2send_ << port2send_ << frame << endl; 
	    else 
		qDebug() << "TO NETWORK:" << address2send_ << port2send_ << frame << "size" << sent;
	}
	else if (socketType_ == "server")
	{
	    for (int i = 0; i < listClients.size(); i++)
	    {
		if ((sent = udpSocket_->writeDatagram(frame, listClients[i]->getAddress(), listClients[i]->getPort())) == -1) 
		    qDebug() << "Failed to send the frame: " << listClients[i]->getAddress() << listClients[i]->getPort() << frame << endl; 
		else 
		    qDebug() << "TO NETWORK:" << listClients[i]->getAddress() << listClients[i]->getPort() << frame << "size" << sent;  	
	    }
	}
} 


void PacpusSocket::readPendingDatagrams()
{
	while (udpSocket_->hasPendingDatagrams())  
	{
		QByteArray datagram; 
		datagram.resize(udpSocket_->pendingDatagramSize()); 
		QHostAddress sender; 
		quint16 senderPort;
    
		if(udpSocket_->readDatagram(datagram.data(), datagram.size(),  &sender, &senderPort) != -1)
		{
		    qDebug() << "RCV : " << datagram << " by " << sender << "on port " << senderPort << " size:" << datagram.size();
		    
 		    if (socketType_ == "server")
		    {
				bool flag = false;
		
				for (int i = 0; i < listClients.size(); i++) 
				{ 
					if (listClients[i]->getAddress() == sender && listClients[i]->getPort() == senderPort)
					flag = true;
				}
			
				if (flag == false)
					listClients << new Client(sender, senderPort);
			}
		    
		    int i = 0;
		    while (datagram.data()[ i ] != 'f')
				i++;
			    	    
		    if (datagram.data()[ i + 2 ] == 'b')
		    {
				emit newDatagram(datagram);
		    }  
			else if (datagram.size() == 4) {
				// Manette Dualshock 3 pour le wifibot
				emit newDatagram(datagram);
			} else {
				QString string(datagram.data());
				emit newQString(string);
            }
		}
		else
		{
		    printf("Error when reading network frame\n");
		}
	}
}


//////////////////////////////////////////////////////////////////////////
// Called by the ComponentManager to stop the component
//////////////////////////////////////////////////////////////////////////
void PacpusSocket::stopActivity()
{
	udpSocket_->close();
	delete udpSocket_;
}
