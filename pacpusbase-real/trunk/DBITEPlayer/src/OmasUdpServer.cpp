#include "DbitePlayer/OmasUdpServer.h" 

// Ports PACPUS/OMAS
// 40 000 : PACPUS recoit
// 40 001 : OMAS recoit 


// Construction de la fabrique de composant DbtPlyEngine 
static ComponentFactory<OmasUdpServer>*  factory  =  new ComponentFactory<OmasUdpServer>("OmasUdpServer");  



// constructor 
OmasUdpServer::OmasUdpServer(QString name) : ComponentBase(name) 
{ 
	
} 


// destructor 
OmasUdpServer::~OmasUdpServer() 
{ 

} 




ComponentBase::COMPONENT_CONFIGURATION  OmasUdpServer::configureComponent(XmlComponentConfig config) 
{ 
	omasSender_.setAddress( param.getProperty("omasAddress") );
	omasSenderPort_ = param.getProperty("omasPort").toUInt();

	return ComponentBase::CONFIGURED_OK; 
} 


void OmasUdpServer::startActivity() 
{ 
	//connect(udpSocketReceiver, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams())); 

	if ( !(udpSocket_ = new QUdpSocket() ) )
		qFatal("Failed to init UDP socket!");

	if ( udpSocket_->bind(omasSender_,omasSenderPort_) )
		qDebug("Socket bound to OMAS");
	else
		qWarning("Failed to bind OMAS");

} 


void OmasUdpServer::sendDatagrams(QString frame) 
{ 
	int sent=0;
	if( (sent = udpSocket_->writeDatagram( frame.toLocal8Bit(),omasSender_, omasSenderPort_ )) == -1) 
	//if(udpSocket_->write( frame.toLocal8Bit() ) != -1) 
		qDebug() << "Failed to send the frame: " << frame << endl; 
	else 
		qDebug() << "TO OMAS:" << frame << "size" << sent ;

} 


void OmasUdpServer::readPendingDatagrams()
{
	while (udpSocket_->hasPendingDatagrams())  
	{
		QByteArray datagram; 
		datagram.resize(udpSocket_->pendingDatagramSize()); 
		QHostAddress sender; 
		quint16 senderPort;

		if(udpSocket_->readDatagram(datagram.data(), datagram.size(),  &sender, &senderPort) != -1)
			printf(datagram.data());
		else printf("Erreur lors de la lecture du message\n");
	}
}


void OmasUdpServer::stopActivity()
{
	udpSocket_->close();
	delete udpSocket_;
}
