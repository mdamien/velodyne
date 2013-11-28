// RoadDetect.h: interface for the RoadDetect class.
//
//////////////////////////////////////////////////////////////////////


#ifndef __RoadDetect_H__
#define __RoadDtect_H__

#include "pacpustools/matrice.h"
#include "kernel/pacpus.h"

#include <qapplication.H>
#include <qwt_plot.H>
#include <qstring.h> 
#include <qlineedit.h> 
#include <qcheckbox.h> 
#include <QThread.H>
#include <qlayout.h> 


#include "RoadDetection/sound.h"

#include "kernel/ComponentFactory.h"
#include "kernel/ComponentBase.h"
#include "memoire_partagee.H"
#include "RoadDetection/Constantes.H"
#include "../moc/mainwindow.h"
#include "RoadDetection/PavementDetection.h"
//---------------------------
#include "LandmarkFileManager.h"


 class RoadDetect :public QObject, public QThread , public ComponentBase
{
	Q_OBJECT


  public:
	  
	
	//--------------------------------------------------------
		void configureComponent (XmlComponentConfig config); 
		void startActivity(); 
		void stopActivity(); 
	    RoadDetect(const char *name = 0);
	    ~RoadDetect() {} ;

	    void run();
	
 private:
	
	int wait_val;
    bool CONTINUE;
    HANDLE GivePosition;
	HANDLE Data_telem;
	HANDLE data_ready ;
	
    

};

#endif 
