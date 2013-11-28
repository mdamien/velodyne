/*********************************************************************
//  created:    2009/04/29 - 11:18
//  filename:   GpsInterface.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Visual Odometry
*********************************************************************/
#ifndef GPSINTERFACE_H
#define GPSINTERFACE_H

#include <QThread>
#include <QMutex>
#include <QApplication>
#include "kernel/ComponentBase.h"
#include "PacpusTools/ShMem.h"
#include "structure/structure_gps.h"

//=============================================================================
// System Includes
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <conio.h>

class GpsInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	GpsInterface(QString name);
	~GpsInterface();

	virtual void stopActivity();
	virtual void startActivity();
	virtual COMPONENT_CONFIGURATION configureComponent (XmlComponentConfig config);

	inline void			setMutex(QMutex* gpsMutex) { gpsMutex_ = gpsMutex; };
	inline void			update(void){memcpy(gpsPosition, gpsPosition_, 3*sizeof(double));
	                                 memcpy(&gpsGeodetic, &gpsGeodetic_, sizeof(donnees_gps));};
	inline double*	    getGpsPosition(void){return gpsPosition;};
	inline donnees_gps* getGeodeticGps(void){return (&gpsGeodetic);};

protected:
	void run();

private:
	bool		recording_;
	QString filePath_;
	FILE*		logFile_;

	bool		firstTime_;

	QMutex*	gpsMutex_;
	ShMem*	shMem_;

	donnees_gps gpsData_;
	double	xMotion_[2];
	double	yMotion_[2];
	double  gpsPosition_[3];
	double  gpsAltitude_;
	
	double  gpsPosition[3]; //Access variables
	donnees_gps  gpsGeodetic_;
	donnees_gps  gpsGeodetic;

	void	processing_(void);
};
#endif //GPSINTERFACE_H