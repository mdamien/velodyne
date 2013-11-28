/****************************************************************************/
/* Projet SY27 : Filtrage Particulaire                                      */
/*                                                                          */
/* Suiveur: Philippe Bonnifait                                              */
/* Date: Autonme 2005                                                       */
/*                                                                          */
/* Auteurs:                                                                 */
/*     Adrien Sanglier                                                      */
/*     Cyril Nahon                                                          */
/*                                                                          */
/* Licence: GNU/GPL 2                                                       */
/****************************************************************************/


#ifndef __GPS_H_TRANSMIS__
#define __GPS_H_TRANSMIS__

#include <windows.h>

//Structure rassemblant les données transmises au système de traitement

typedef struct{
	long  ind_qualite;
	double x, y;
	float a,b,phi,sigma_lat,sigma_lon;
}donnees_gps;


typedef struct
{
	double lon, lat, alt_msl, d_geoidal;
	int type;
	char nom[32];
} gpsdata;

#endif