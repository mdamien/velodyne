/*********************************************************************
//  created:    2008/01/14 - 12:45
//  filename:   AlascaInterface.h
//
//  author:     Gerald Dherbomez
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/


#ifndef __ALASCAINTERFACE_H__
#define __ALASCAINTERFACE_H__

#include <QThread>

#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "structure/structure_telemetre.H"
#include "AlascaViewer.h"
#include "AlascaViewer3D.h"
#include "AlascaLOVeComputing.h"

class AlascaInterface : public QThread, public ComponentBase
{
  Q_OBJECT

public:
  AlascaInterface(QString name);
  ~AlascaInterface();

  virtual void stopActivity(); 
  virtual void startActivity(); 
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

  ScanAlascaData incomingAlascaData; 
  SortedScanAlascaData alascaData,filteredAlascaData,groundAlascaData,groundAlascaDataHds,groundAlascaDataIbo;

signals:
  void dataReady();
  void refreshDisplay();
  void displayLayer(QString name, double *x, double *y, int size, const QColor color);
  void displayTrack(QString name, double xc, double yc, double width, double height, const QColor color);
  void displayText(QString name, double x, double y, QString text);
  void displayLine(QString name, double x1, double y1, double x2, double y2, const QColor color);

protected:
  void run();

private:
  // The shared memory where data are provided
  ShMem*			shmem_;
  AlascaDataModule* processing_;
  road_time_t		tic_;  

  void tic() { tic_ = road_time(); }
  void toc(char * text) { printf("duration = %d %s\n", (int)(road_time() - tic_), text ); }
};


#endif // __ALASCAINTERFACE_H__