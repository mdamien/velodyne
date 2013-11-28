#include "../../PACPUS/include/DbitePlayer/serverinterface.h"


using namespace std;

serverInterface::serverInterface() {

	socket= (QTcpSocket*)malloc(sizeof(QTcpSocket));
	connect(this, SIGNAL(updaterequest(uint)), this, SLOT(updateRequested(uint)));
}


void serverInterface::updateWhlSpd(whSpeed *fromser) {
	
	whlspd=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateSusp(suspension *fromser) {
	susp=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateVhSp(vhSpeed *fromser) {
	vclspd=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateLDyn(LDynamics *fromser) {
	ldyn=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateRLDyn(rLDynamics *fromser) {
	rldyn=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateGGA(trameGGA *fromser) {
	tramegga=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateGGADBL(trameGGADBL *fromser) {
	trameggadbl=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateGSA(trameGSA *fromser) {
	tramegsa=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateGST(trameGST *fromser) {
	tramegst=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateGSV(trameGSV *fromser) {
	tramegsv=fromser;
	emit updaterequest(fromser->ID);
}
				
void serverInterface::updateHDT(trameHDT *fromser) {
	tramehdt=fromser;
	emit updaterequest(fromser->ID);
}
				
void serverInterface::updateRMC(trameRMC *fromser) {
	tramermc=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateROT(trameROT *fromser) {
	tramerot=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateVTG(trameVTG *fromser) {
	tramevtg=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateZDA(trameZDA *fromser) {
	tramezda=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateGYROKVH(trameGYROKVH *fromser) {
	tramegyrokvh=fromser;
	emit updaterequest(fromser->ID);
}

void serverInterface::updateRequested(uint t) {
	switch(t) {
		case CARMEN_CAN_WHEELSPEED :
		  printf("send wheelspeed\n");
			nbbytes= (uint)socket->write((char *)whlspd, sizeof(whSpeed));
			break;
		case CARMEN_CAN_SUSPENSION :
			nbbytes= (uint)socket->write((char *)susp, sizeof(suspension));
			break;
		case CARMEN_CAN_ODOMETRY :
			nbbytes= (uint)socket->write((char *)vclspd, sizeof(vhSpeed));
			break;
		case CARMEN_CAN_LATDYN :
			nbbytes= (uint)socket->write((char *)ldyn, sizeof(LDynamics));
			break;
		case CARMEN_CAN_RAWLATDYN :
			nbbytes= (uint)socket->write((char *)rldyn, sizeof(rLDynamics));
			break;
		case TRAME_GGA :
			nbbytes= (uint)socket->write((char *)tramegga, sizeof(trameGGA));
			break;
		case TRAME_GGA_DBL :
		  printf("send GGA\n");
			nbbytes= (uint)socket->write((char *)trameggadbl, sizeof(trameGGADBL));
			break;
		case TRAME_GSA :
			nbbytes= (uint)socket->write((char *)tramegsa, sizeof(trameGSA));
			break;
		case TRAME_GST :
			nbbytes= (uint)socket->write((char *)tramegst, sizeof(trameGST));
			break;
		case TRAME_GSV :
			nbbytes= (uint)socket->write((char *)tramegsv, sizeof(trameGSV));
			break;
		case TRAME_HDT :
			nbbytes= (uint)socket->write((char *)tramehdt, sizeof(trameHDT));
			break;
		case TRAME_RMC :
			nbbytes= (uint)socket->write((char *)tramermc, sizeof(trameRMC));
			break;
		case TRAME_ROT :
			nbbytes= (uint)socket->write((char *)tramerot, sizeof(trameROT));
			break;
		case TRAME_VTG :
			nbbytes= (uint)socket->write((char *)tramevtg, sizeof(trameVTG));
			break;
		case TRAME_ZDA :
			nbbytes= (uint)socket->write((char *)tramezda, sizeof(trameZDA));
			break;
		case GYRO_KVH :
			nbbytes= (uint)socket->write((char *)tramegyrokvh, sizeof(trameGYROKVH));
			break;
// 		default: emit sendok(0);
		break;
	}
// 	emit sendok(nbbytes);
	
}
	
