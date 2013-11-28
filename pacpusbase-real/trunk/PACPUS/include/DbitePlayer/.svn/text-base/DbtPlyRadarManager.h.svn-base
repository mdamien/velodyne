/*********************************************************************
//  created:    2007/07/28 - 11:51
//  filename:   DbtPlyGyrokvhManager.h
//
//  author:     Gerald Dherbomez 
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    Dbite Player Gyrokvh Manager
*********************************************************************/


#ifndef _DBTPLYRADARMANAGER_H_
#define _DBTPLYRADARMANAGER_H_

//#include <qlcdnumber.h>
//#include <qgroupbox.h>
//#include <qlabel.h>

#include "DbitePlayer/DbtPlyFileManager.h"
#include "structure/structure_radar.h"
#include "PacpusTools/ShMem.h"


class DbtPlyRadarManager : public DbtPlyFileManager
{
  //Q_OBJECT

public:
	int a;
	
	DbtPlyRadarManager(QString name);
	~DbtPlyRadarManager();
	virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);


protected:
	void processData(road_time_t t, road_timerange_t tr , void *buf);
	virtual void startActivity();
	virtual void stopActivity();
	void displayUI();

  	
//signals:
//  void displayGyroPsiS(double);
//	void displayGyroPPsiS(double);
  

private:
	// variables for output
	ShMem * shMem_; 
	RECORD_RADAR dataToTransmit_;
};


#endif
