
#include <QApplication>
#include <QVBoxLayout>
#include "DbitePlayer/SensorTcpServer.h"
#include "kernel/ComponentManager.h"


static ComponentFactory<SensorTcpServer>* factory = new ComponentFactory<SensorTcpServer>("SensorTcpServer");

QString context; //to convert uint to QString
bool* timedOut;
int port;


SensorTcpServer::SensorTcpServer(QString name):ComponentBase(name)  {


	w = new QWidget();
	w->setWindowTitle(componentName);
	w->show();
	w->setFixedSize (500,200);
	label=new QLabel("Server events",w);
	label->move(5,5);
	label->setFixedSize(100,20);
	label->show();
	text= new QTextBrowser(w);
	text->move(5,25);
	text->setFixedSize(490,160);
	text->show();
	cs = new cvisServer();
}

SensorTcpServer::~SensorTcpServer() {
}


ComponentBase::COMPONENT_CONFIGURATION SensorTcpServer::configureComponent(XmlComponentConfig config) {
	
	QApplication::connect(cs,SIGNAL(attemptconnect()), this, SLOT(attemptToCon()));
	QApplication::connect(cs,SIGNAL(conestab(int)),this, SLOT(conEstab(int)));
// 	QApplication::connect(cs,SIGNAL(endsending(uint)),this, SLOT(endSending(uint)));
// 	QApplication::connect(cs,SIGNAL(setproperty(QString)), this, SLOT(setProp(QString)));
// 	QApplication::connect(cs,SIGNAL(propertyset(uint)), this, SLOT(propSet(uint)));
// 	QApplication::connect(cs,SIGNAL(propertynotset(uint)), this, SLOT(propNotSet(uint)));
	port = param.getProperty("port").toInt();
	cs->listen ( QHostAddress::Any, port );
	attemptToCon();
	return ComponentBase::CONFIGURED_OK;

}


void SensorTcpServer::startActivity(){


}

void SensorTcpServer::stopActivity()
{
	w->close();
}

void SensorTcpServer::endSending(uint t){
	if (t==0) text->append("Error!! Unknown Data Frame");
	else {
	context.sprintf("%d",t);
	text->append(context+" Bytes were sent.\n");
	}

}

void SensorTcpServer::conEstab(int t){
	context.sprintf("%d", t);
	text->append("connection established on socket "+ context + "\n");
}

void SensorTcpServer::setProp(QString t){
	text->append("Setting property of "+t+"\n");
}

void SensorTcpServer::propSet(uint t){
	context.sprintf("%d", t);
	text->append("Property of ID "+ context +" is set, update requested \n");
}

void SensorTcpServer::attemptToCon() {
// 	cout << "Attempting to connect\n";
	text->append("Attempting to connect\n");
}

void SensorTcpServer::propNotSet(uint t){
	context.sprintf("%d", t);
	text->append("No Connection Available with client\n");
	text->append("Property of ID "+ context +" is not set\n");
}








	