

#include "../../PACPUS/include/DbitePlayer/cvisServer.h"


// cvisServer::cvisServer( quint16 portnum) {
cvisServer::cvisServer() {
// 	listen (QHostAddress::Any, portnum );
	serint=new serverInterface();
	connect( this, SIGNAL(newConnection()), this, SLOT(conavailable()));

  // init magic word
  whlspd.mw = cvisMagicWord;
		susp.mw = cvisMagicWord;
		vclspd.mw = cvisMagicWord;
		ldyn.mw = cvisMagicWord;
		rldyn.mw = cvisMagicWord;
		tramegga.mw = cvisMagicWord;
		trameggadbl.mw = cvisMagicWord;
		tramegsa.mw = cvisMagicWord;
		tramegst.mw = cvisMagicWord;
		tramegsv.mw = cvisMagicWord;
		tramehdt.mw = cvisMagicWord;
		tramermc.mw = cvisMagicWord;
		tramerot.mw = cvisMagicWord;
		tramevtg.mw = cvisMagicWord;
		tramezda.mw = cvisMagicWord;
		tramegyrokvh.mw = cvisMagicWord;
		
}

void cvisServer::conavailable() {

	serint->socket = nextPendingConnection();
	sockid=serint->socket->socketDescriptor();
	interMap.insert(sockid,serint);
	connect(interMap[sockid],SIGNAL(sendok(uint)),this, SLOT(sendOK(uint)));
	emit conestab(sockid);
}

void cvisServer::sendOK(uint f) {
	emit endsending(f);
}


void cvisServer::setWheelSpeed(StructWheelSpeed whlspdext, road_time_t rt){
	emit setproperty("WheelSpeed");
  printf("V");
	whlspd.ID=CARMEN_CAN_WHEELSPEED;
	whlspd.rtime=rt;
	whlspd.speed=whlspdext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(CARMEN_CAN_WHEELSPEED);
		interMap[sockid]->updateWhlSpd(&whlspd);
	}
	else emit propertynotset(CARMEN_CAN_WHEELSPEED);
		
	
}
void cvisServer::setSuspension(StructSuspension suspext, road_time_t rt){
	emit setproperty("Suspension");
	susp.ID=CARMEN_CAN_SUSPENSION;
	susp.rtime=rt;
	susp.susp= suspext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		interMap[sockid]->updateSusp(&susp);
		emit propertyset(CARMEN_CAN_SUSPENSION);
	}
	else emit propertynotset(CARMEN_CAN_SUSPENSION);
}
void cvisServer::setVehicleSpeed(StructVehicleSpeed vclspdext, road_time_t rt){
	emit setproperty("VehicleSpeed");
  printf("O");
	vclspd.ID=CARMEN_CAN_ODOMETRY;
	vclspd.rtime=rt;
	vclspd.speed=vclspdext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		//emit propertyset(CARMEN_CAN_ODOMETRY);
		interMap[sockid]->updateVhSp(&vclspd);
	}
// 	else emit propertynotset(CARMEN_CAN_ODOMETRY);

}
void cvisServer::setLateralDynamics(StructLateralDynamics ldynext, road_time_t rt){
// 	emit setproperty("LateralDynamics");
  printf("w");
	ldyn.ID=CARMEN_CAN_LATDYN;
	ldyn.rtime=rt;
	ldyn.dynamics= ldynext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
// 		emit propertyset(CARMEN_CAN_LATDYN);
		interMap[sockid]->updateLDyn(&ldyn);
	}
// 	else emit propertynotset(CARMEN_CAN_LATDYN);
}
void cvisServer::setRawLateralDynamics(StructRawLateralDynamics rldynext, road_time_t rt){
	emit setproperty("RawLateralDynamics");
	rldyn.ID=CARMEN_CAN_RAWLATDYN;
	rldyn.rtime=rt;
	rldyn.dynamics= rldynext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(CARMEN_CAN_RAWLATDYN);
		interMap[sockid]->updateRLDyn(&rldyn);
	}
	else emit propertynotset(CARMEN_CAN_RAWLATDYN);
}
void cvisServer::setgga(trame_gga trameggaext, road_time_t rt){
	emit setproperty("GGA");
	tramegga.ID=TRAME_GGA;
	tramegga.rtime=rt;
	tramegga.trgga= trameggaext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_GGA);
		interMap[sockid]->updateGGA(&tramegga);
	}
	else emit propertynotset(TRAME_GGA);
}

void cvisServer::setggadbl(trame_gga_dbl trameggadblext, road_time_t rt){
  printf("-");
	//emit setproperty("GGA_DBL");
	trameggadbl.ID=TRAME_GGA_DBL;
	trameggadbl.rtime=rt;
	trameggadbl.trggadbl= trameggadblext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		//emit propertyset(TRAME_GGA_DBL);
		interMap[sockid]->updateGGADBL(&trameggadbl);
	}
// 	else  emit propertynotset(TRAME_GGA_DBL);
}


void cvisServer::setgsa(trame_gsa tramegsaext){
	emit setproperty("GSA");
	tramegsa.ID=TRAME_GSA;
	tramegsa.trgsa= tramegsaext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_GSA);
		interMap[sockid]->updateGSA(&tramegsa);
	}
	else emit propertynotset(TRAME_GSA);
}
void cvisServer::setgst(trame_gst tramegstext, road_time_t rt){
	//emit setproperty("GST");
	tramegst.ID=TRAME_GST;
	tramegst.rtime=rt;
	tramegst.trgst= tramegstext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		//emit propertyset(TRAME_GST);
		interMap[sockid]->updateGST(&tramegst);
	}
// 	else emit propertynotset(TRAME_GST);
}
void cvisServer::setgsv(trame_gsv tramegsvext){
	emit setproperty("GSV");
	tramegsv.ID=TRAME_GSV;
	tramegsv.trgsv= tramegsvext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_GSV);
		interMap[sockid]->updateGSV(&tramegsv);
	}
	else emit propertynotset(TRAME_GSV);
}
void cvisServer::sethdt(trame_hdt tramehdtext){
	emit setproperty("HDT");
	tramehdt.ID=TRAME_HDT;
	tramehdt.trhdt= tramehdtext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_HDT);
		interMap[sockid]->updateHDT(&tramehdt);
	}
	else emit propertynotset(TRAME_HDT);
}
void cvisServer::setrmc(trame_rmc tramermcext){
	emit setproperty("RMC");
	tramermc.ID=TRAME_RMC;
	tramermc.trrmc= tramermcext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_RMC);
		interMap[sockid]->updateRMC(&tramermc);
	}
	else emit propertynotset(TRAME_RMC);
}
void cvisServer::setrot(trame_rot tramerotext){
	emit setproperty("ROT");
	tramerot.ID=TRAME_ROT;
	tramerot.trrot= tramerotext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_ROT);
		interMap[sockid]->updateROT(&tramerot);
	}
	else emit propertynotset(TRAME_ROT);
}
void cvisServer::setvtg(trame_vtg tramevtgext, road_time_t rt){
	emit setproperty("VTG");
	tramevtg.ID=TRAME_VTG;
	tramevtg.rtime=rt;
	tramevtg.trvtg= tramevtgext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_VTG);
		interMap[sockid]->updateVTG(&tramevtg);
	}
	else emit propertynotset(TRAME_VTG);
}
void cvisServer::setzda(trame_zda tramezdaext){
	emit setproperty("ZDA");
	tramezda.ID=TRAME_ZDA;
	tramezda.trzda= tramezdaext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		emit propertyset(TRAME_ZDA);
		interMap[sockid]->updateZDA(&tramezda);
	}
	else emit propertynotset(TRAME_ZDA);
}

void cvisServer::setgyrokvh(data_gyroKVH trgyrokvhext,road_time_t rt) {
	//emit setproperty("GYRO");
	tramegyrokvh.ID=GYRO_KVH;
	tramegyrokvh.rtime=rt;
	tramegyrokvh.trgyrokhv= trgyrokvhext;
	iter  =interMap.find(sockid);
	if(iter != interMap.end()) {
		//emit propertyset(GYRO_KVH);
		interMap[sockid]->updateGYROKVH(&tramegyrokvh);
	}
// 	else emit propertynotset(GYRO_KVH);
}