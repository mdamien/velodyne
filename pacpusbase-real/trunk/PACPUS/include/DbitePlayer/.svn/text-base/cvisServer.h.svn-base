
#ifndef __serverdata_h__
#define __serverdata_h__


#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QIODevice>
#include <iostream>
#include <QHostAddress>
#include <QString>
#include <QObject>
#include <QMap>

#include "serverinterface.h"

using namespace std;

class cvisServer: public QTcpServer {
	Q_OBJECT
	public:
// 	cvisServer(quint16 portnum);
	cvisServer();
	~cvisServer() {delete this; }

	
	void setWheelSpeed(StructWheelSpeed whlspdext, road_time_t rt);
	void setSuspension(StructSuspension suspext, road_time_t rt);
	void setVehicleSpeed(StructVehicleSpeed vclspdext, road_time_t rt);
	void setLateralDynamics(StructLateralDynamics ldynext, road_time_t rt);
	void setRawLateralDynamics(StructRawLateralDynamics rldynext, road_time_t rt);
	void setgga(trame_gga trameggaext, road_time_t rt);
	void setggadbl(trame_gga_dbl trameggadblext, road_time_t rt);
	void setgsa(trame_gsa tramegsaext);
	void setgst(trame_gst tramegstext, road_time_t rt);
	void setgsv(trame_gsv tramegsvext);
	void sethdt(trame_hdt tramehdtext);
	void setrmc(trame_rmc tramermcext);
	void setrot(trame_rot tramerotext);
	void setvtg(trame_vtg tramevtgext, road_time_t rt);
	void setzda(trame_zda tramezdaext);
	void setgyrokvh(data_gyroKVH trgyrokvhext,road_time_t rt);
	
	signals:
		void attemptconnect();
		void conestab(int);
		void setproperty(QString);
		void propertyset(uint);
		void propertynotset(uint);
		void endsending(uint);
	
	private:
		
		int sockid;
		serverInterface *serint; 
		QMap<int,serverInterface*>  interMap;
		QMap<int,serverInterface*>::iterator iter;

		whSpeed whlspd;
		suspension susp;
		vhSpeed vclspd;
		LDynamics ldyn;
		rLDynamics rldyn;
		trameGGA tramegga;
		trameGGADBL trameggadbl;
		trameGSA tramegsa;
		trameGST tramegst;
		trameGSV tramegsv;
		trameHDT tramehdt;
		trameRMC tramermc;
		trameROT tramerot;
		trameVTG tramevtg;
		trameZDA tramezda;
		trameGYROKVH tramegyrokvh;
		
	protected slots:
		void conavailable();
		void sendOK(uint f);
		
};



#endif