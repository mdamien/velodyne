#ifndef __SensorTcpServerStructure_h__
#define __SensorTcpServerStructure_h__


#include "structure/structure_gyro.h"
#include "structure/structureCanCarmen.h"
#include "kernel/road_time.h"
#include "structure/structure_gps.h"
#include "kernel/io_hdfile.h"



// UTC\0
const long cvisMagicWord = 0x55544300;


typedef struct whSpeed{
	long mw;
	uint ID;
	road_time_t rtime;
	StructWheelSpeed speed;
}whspeed;

typedef struct suspension{
	long mw;
	uint ID ;
	road_time_t rtime;
	StructSuspension susp;
}suspension;

typedef struct vhSpeed{
	long mw;
	uint ID;
	road_time_t rtime;
	StructVehicleSpeed speed;
}vhSpeed;

typedef struct LDynamics{
	long mw;
	uint ID;
	road_time_t rtime;
	StructLateralDynamics dynamics;
}LDynamics;

typedef struct rLDynamics{
	long mw;
	uint ID;
	road_time_t rtime;
	StructRawLateralDynamics dynamics;
}rLDynamics;

typedef struct {
	long mw;
	uint ID;
	trame_avr travr;
}trameAVR;

typedef struct {
	long mw;
	uint ID;
	road_time_t rtime;
	trame_gga trgga;
}trameGGA;

typedef struct {
	long mw;
	uint ID;
	road_time_t rtime;
	trame_gga_dbl trggadbl;
}trameGGADBL;

typedef struct {
	long mw;
	uint ID;
	trame_gll trgll;
}trameGLL;

typedef struct {
	long mw;
	uint ID;
	trame_grs trgrs;
}trameGRS;

typedef struct {
	long mw;
	uint ID;
	trame_gsa trgsa;
}trameGSA;

typedef struct {
	long mw;
	uint ID;
	road_time_t rtime;
	trame_gst trgst;
}trameGST;

typedef struct {
	long mw;
	uint ID;
	trame_gsv trgsv;
}trameGSV;

typedef struct {
	long mw;
	uint ID;
	trame_hdt trhdt;
}trameHDT;

typedef struct {
	long mw;
	uint ID;
	trame_mss trmss;
}trameMSS;

typedef struct {
	long mw;
	uint ID;
	trame_rmc trrmc;
}trameRMC;

typedef struct {
	long mw;
	uint ID;
	trame_rot trrot;
}trameROT;

typedef struct {
	long mw;
	uint ID;
	road_time_t rtime;
	trame_vtg trvtg;
}trameVTG;

typedef struct {
	long mw;
	uint ID;
	trame_xte trxte;
}trameXTE;

typedef struct {
	long mw;
	uint ID;
	trame_zda trzda;
}trameZDA;

typedef struct {
	long mw;
	uint ID;
	trame_ptnlev trptnlev;
}tramePTNLEV;

typedef struct {
	long mw;
	uint ID;
	trame_ptnlid trptnlid;
}tramePTNLID;

typedef struct {
	long mw;
	uint ID;
	trame_ptnldg trptnldg;
}tramePTNLDG;

typedef struct {
	long mw;
	uint ID;
	trame_ptnlsm trptnlsm;
}tramePTNLSM;

typedef struct {
	long mw;
	uint ID;
	trame_ptnl_ggk travrptnlggk;
}tramePTNLGGK;

typedef struct {
	long mw;
	uint ID;
	trame_ptnl_ggk_sync trptnlggksync;
}tramePTNLGGKSync;

typedef struct {
	long mw;
	uint ID;
	trame_ptnl_pjk trptnlpjk;
}tramePTNLPJK;

typedef struct {
	long mw;
	uint ID;
	trame_ptnl_pjt trptnlpjt;
}tramePTNLPJT;

typedef struct {
	long mw;
	uint ID;
	trame_ptnl_vgk trptnlvgk;
}tramePTNLVGK;

typedef struct {
	long mw;
	uint ID;
	trame_ptnl_vhd trptnlvhd;
}tramePTNLVHD;

typedef struct {
	long mw;
	uint ID;
	road_time_t rtime;
	data_gyroKVH trgyrokhv;
}trameGYROKVH;

#endif