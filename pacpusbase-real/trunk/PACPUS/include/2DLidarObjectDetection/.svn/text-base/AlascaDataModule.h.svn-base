/*********************************************************************
//  created:    2008/3/10 - 18:18
//  filename:   AlascaDataModule.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    abstract class
//
*********************************************************************/


#ifndef __AlascaDataModule_H__
#define __AlascaDataModule_H__


#include "kernel/ComponentBase.h"
#include "structure/structure_telemetre.H"
#include "sensor/ImageViewer.h"
#include "structure/structureCanCarmen.h"
#include "structure/structure_radar.h"

#define LIDAR_OBJECTS_LIMIT 300
//************************************************************************//
struct GlobalAlascaData{
	ScanAlascaData * alascaData; 
	SortedScanAlascaData * layers;
};
//These structures should be used for shmem data sharing
//#pragma pack(4) //32 bits padding
struct lidarObject{ //Structure used for describing an object detected from lidar data 
	double			coodinates[3];		//metric coordinates in lidar local frame
	double			boundingRadius;		//bounding cercle radius
	unsigned int	detectionQuality;	
	unsigned int	recognitionQuality; //for pedestian recognition
	double			speed[2];				//w.r.t lidar local frame
};
struct lidarObjectList{//Structure which contains all objects detected at time t from lidar data
	int			size;   //number of objects 
	road_time_t	date;	//timestamp
	double		navigationBoundaries[2];//[0] right navigation boundary in the lidar frame XYZ ={FLU}
										//[1] left  navigation boundary in the lidar frame XYZ ={FLU}				
	lidarObject	objects[LIDAR_OBJECTS_LIMIT]; // WARNING: The architecture supports a maximum of 300 objects
};
//#pragma pack()
//************************************************************************//

class AlascaDataModule : public ComponentBase
{
public:
  AlascaDataModule(QString name) : ComponentBase(name){d_.alascaData = NULL; d_.layers = NULL;};
  ~AlascaDataModule(){};
  virtual void compute(GlobalAlascaData data) = 0;
  virtual void setImage(QImage * image) = 0;
  virtual void setWheelSpeed(TimestampedStructWheelSpeed speed) = 0;
  virtual void setRadar(const DONNEE_RADAR &data_radar) = 0;


protected:
  ImageViewer * imViewer_;
  GlobalAlascaData d_;
  road_time_t tic_;  
  void tic() { tic_ = road_time(); }
  void toc(char * text) { printf("duration = %d %s\n", (int)(road_time() - tic_), text ); }
};


#endif // __AlascaDataModule_H__
