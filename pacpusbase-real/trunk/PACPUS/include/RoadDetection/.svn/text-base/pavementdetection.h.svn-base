/*********************************************************************
//  created:    2007/04/23 - 11:23
//  filename:   PavementDetection.h
//
//  author:     Maha El Nemri, Maged Jabbour, Gerald Dherbomez 
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id:  $
//
//  purpose:    Classe comportant les fonctions de détection des bords 
//              de route
//  
*********************************************************************/


#ifndef __PAVEMENTDETECTION_H__
#define __PAVEMENTDETECTION_H__

#include "pacpustools/matrice.h"
#include "kernel/pacpus.h"






class PavementDetection
{
public:

	PavementDetection(){}; 
	~PavementDetection(){}; 

	/*   
		donnee -> mesures télémétriques
	
	 	x_telem,y_telem,z_telem-> coordonnées des points
	    dx,dy,dz -> derivées des points
	    dyn -> sinus de la pente de dy+i*dz

	*/
	void derive(TELEMETER_DATA *donnee,double *dx,double *dy,double *dz);

	// Renvoie les indices de confiance de la detection
	bool evaldist(TELEMETER_DATA *donnee,float limited,float limiteg,int &m,int &k,int &indconfd,int &indconfg,bool &detectiond,bool &detectiong, double &hautd, double &hautg);

	
	void rotation1(double *x_tel,double *y_tel,double *z_tel,double *x,double *y,double *z,int angle);
	
	//
	void project_Rmonde(TELEMETER_DATA *donnee,s_MatchedPosition myMatchedPosition_,
									   double *X,double *Y,double *Z); 
	
	void incertitude(TELEMETER_DATA *donnee,int n,matrice *P);
    void pol_cartRUSL(TELEMETER_DATA *donnee,double *x_telem,double *y_telem,double *z_telem,double *dyn);

};

#endif
