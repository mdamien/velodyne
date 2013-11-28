// PPinterface.h: interface for the PPinterface class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __PPINTERFACE_H__
#define __PPINTERFACE_H__

//#include "RoadDetection/memoire_partagee.H"
#include "RoadDetection/constantes.H"
#include "../moc/mainwindow.h"
#include "pacpustools/matrice.h"
#include "kernel/pacpus.h"
#include "RoadDetection/sound.h"

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentBase.h"
#include "memoire_partagee.H"
#include "RoadDetection/constantes.H"
#include "../moc/mainwindow.h"
#include "RoadDetection/PavementDetection.h"
#include <windows.h>
#include "kernel\road_time.h"

#include <qsocket.h>
#include <qApplication.h>
//--------------------





class PPinterface :public QObject, public QThread , public ComponentBase 
{
   Q_OBJECT

public:
	PPinterface(const char *name = 0);
	~PPinterface() {};
	void run();
	//--------------------------------------------------------
		void configureComponent (XmlComponentConfig config); 
		void startActivity(); 
		void stopActivity(); 

private:

	HANDLE GivePosition;
	HANDLE MPsent;
	HANDLE Request;
	HANDLE Data_Ready;
	HANDLE posEvents[2];

	int wait_val;
	bool CONTINUE;
};

#endif 