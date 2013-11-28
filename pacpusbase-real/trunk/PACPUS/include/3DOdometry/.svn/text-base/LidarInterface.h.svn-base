/*********************************************************************
//  created:    2009/11/03 - 16:12
//  filename:   LidarInterface.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Lidar Odometry
*********************************************************************/

#ifndef LIDARINTERFACE_H
#define LIDARINTERFACE_H

#include <QThread>
#include <QMutex>
#include <QApplication>
#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "structure/structureCanCarmen.h"
#include "structure/structure_telemetre.H"

class LidarInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	LidarInterface(QString name);
	~LidarInterface();

	virtual void stopActivity();
	virtual void startActivity();
	virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

protected:
	void run();

private:
	bool	recording_;	
	bool	dbt2txt_;
	FILE*	dbt2txtFile_;
	QString filePath_;
	QString scanFolderName_;

	// The shared memory where data are provided
	ShMem * shmem_;
	//incoming LidarData 
	ScanAlascaData incomingData_;

};
#endif //LIDARINTERFACE_H