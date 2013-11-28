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

#include "AlascaViewer3D.h"

class LidarInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	LidarInterface(QString name);
	~LidarInterface();

	virtual void stopActivity();
	virtual void startActivity();
	virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

	unsigned int getScans2Acquire(void)	{return scans2Acquire_;}
	void		 setFileCount(int value){fileCount_=value;}
	void		 startGetButton_(void)	{getButton_=true;}

protected:
	void run();

signals:
  void refreshLidarDisplay();   //flush the bird view window

private:
	bool			recording_;	
	bool			dbt2txt_;
	bool			getButton_;
	FILE*			dbt2txtFile_;
	QString			filePath_;
	QString			scanFolderName_;
	int				fileCount_;
	unsigned int	folderCount_;
	QString			subFolderName_;
	unsigned int	scans2Acquire_;

	// Display lidar module
	AlascaViewer3D * lidarViewer_;
	void updateLidarData2Display(void);

	// The shared memory where data are provided
	ShMem * shmem_;
	//incoming LidarData 
	ScanAlascaData		  incomingData_;
	SortedScanAlascaData  layers_;

};
#endif //LIDARINTERFACE_H