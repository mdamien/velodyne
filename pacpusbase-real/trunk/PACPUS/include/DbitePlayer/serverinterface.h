#ifndef __serverinterface_h__
#define __serverinterface_h__


#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QIODevice>
#include <iostream>
#include <QMap>

#include "structure/SensorTcpServerStructure.h"


using namespace std;


class serverInterface : public QObject{

Q_OBJECT
		
	public:
	serverInterface() ;
	~serverInterface() { delete this;}
	QTcpSocket* socket;
	void updateWhlSpd(whSpeed *fromser);
	void updateSusp(suspension *fromser);
	void updateVhSp(vhSpeed *fromser);
	void updateLDyn(LDynamics *fromser);
	void updateRLDyn(rLDynamics *fromser);
	void updateGGA(trameGGA *fromser);
	void updateGGADBL(trameGGADBL *fromser);
	void updateGSA(trameGSA *fromser);
	void updateGST(trameGST *fromser);
	void updateGSV(trameGSV *fromser);
	void updateHDT(trameHDT *fromser);
	void updateRMC(trameRMC *fromser);
	void updateROT(trameROT *fromser);
	void updateVTG(trameVTG *fromser);
	void updateZDA(trameZDA *fromser);
	void updateGYROKVH(trameGYROKVH *fromser);

	signals:
		void sendok(uint);
		void updaterequest(uint);

	protected slots:
		void updateRequested(uint t);

	private:
		uint nbbytes;
		
		whSpeed *whlspd;
		suspension *susp;
		vhSpeed *vclspd;
		LDynamics *ldyn;
		rLDynamics *rldyn;
		trameGGA *tramegga;
		trameGGADBL *trameggadbl;
		trameGSA *tramegsa;
		trameGST *tramegst;
		trameGSV *tramegsv;
		trameHDT *tramehdt;
		trameRMC *tramermc;
		trameROT *tramerot;
		trameVTG *tramevtg;
		trameZDA *tramezda;
		trameGYROKVH *tramegyrokvh;
};
 
#endif