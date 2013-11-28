#ifndef _STRUCTURERADAR_H_
#define _STRUCTURERADAR_H_

#include "kernel/road_time.h"

//structure de donnée des données du Radar TRW

#define NB_TARGET 12
#define NB_TRACK 8

typedef struct {

int IIV;
int NLIV;
float Range;
float VRel;
float Det_Lvl;
int ID;
int Cred;
int Sel_Stat;
int Tr_Stat;
int CWS;
float Tr_LD;
float UAng;
int Ta_Idx;
float TaLd;
} DONNEE_TRACK;


typedef struct {
int ID;
float Range;
float VRel;
float Det_Lvl;
float RelAz;
char AStat;
char ndId;
int R123;
int R1234;
int R12;
float N21_1;
int LinErr;
} DONNEE_TARGET;


typedef struct {
DONNEE_TRACK Tracks[NB_TRACK];
DONNEE_TARGET Targets[NB_TARGET];
} DONNEE_RADAR;

typedef struct{
	DONNEE_RADAR donnees_radar;
	road_time_t t;
	road_timerange_t tr;
}RECORD_RADAR;

#endif // _STRUCTURERADAR_H_
