/*********************************************************************
//  created:    2010/03/26 - 14:30
//  filename:   VelodyneComponent.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/



#ifndef _VELODYNECOMPONENT_H_
#define _VELODYNECOMPONENT_H_

#include <QThread>
#include <QUdpSocket>
#include "kernel/road_time.h"
#include "PacpusTools/ShMem.h"
#include "kernel/ComponentBase.h"
#include "structure_velodyne.h"




class VelodyneComponent : public QThread, public ComponentBase
{
  Q_OBJECT

public:
  VelodyneComponent(QString name);
  ~VelodyneComponent();

  virtual void stopActivity(); /*!< to stop the processing thread */
  virtual void startActivity(); /*!< to start the processing thread */
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

public slots:
  void readPendingDatagrams();
  
protected:
  void initSocket();
  void closeSocket();
  void run();
  void processTheDatagram(road_time_t time, QByteArray data);
  void record();
  void exposeData();
  void switchBuffer();


private:
  QUdpSocket *socket_;
  
  bool startOfScan_, endOfScan_;
  unsigned short idxBlock_;  
  // The Velodyne IP or hostname
  QHostAddress  host_; 
  // The Velodyne port
  quint16 port_; 
  
  struct VelodynePolarData velodyneDataBuffer_[2];
  struct VelodynePolarData *velodyneData_; // a pointer to the current velodyneDataBuffer_
  struct VelodynePolarData *fullBuffer_;   // a pointer to the velodyne data which is completly filled

  int currentVelodyneData_;
  
  int previousAngle_;
  
  bool running_;
  
  // dbt files 
  hdfile_t * velodyneSphericDataFile_;
  
};

#endif

