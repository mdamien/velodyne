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


struct GlobalAlascaData{
  ScanAlascaData * alascaData; 
  SortedScanAlascaData * layers;
};


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
