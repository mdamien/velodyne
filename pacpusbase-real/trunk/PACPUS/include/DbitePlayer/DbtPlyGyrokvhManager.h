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


#ifndef _DBTPLYGYROKVHMANAGER_H_
#define _DBTPLYGYROKVHMANAGER_H_

#include <QLCDNumber>
#include <QGroupBox>
#include <QLabel>

#include "DbitePlayer/DbtPlyFileManager.h"
// #include "structure/structure_gyro.h"
#include "kernel/ComponentManager.h"//added
#include "DbitePlayer/SensorTcpServer.h" //added

#include "PacpusTools/ShMem.h"




class DbtPlyGyrokvhManager : public DbtPlyFileManager
{
  Q_OBJECT

public:
	DbtPlyGyrokvhManager(QString name);
	~DbtPlyGyrokvhManager();
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

protected:
  void processData(road_time_t t, road_timerange_t tr , void *buf);
  virtual void startActivity();
  virtual void stopActivity();
  void displayUI();


signals:
  void displayGyroPsiS(double);
  void displayGyroPPsiS(double);
  

private:
  data_gyroKVH val; 
  QWidget *w; 
  QGroupBox *gyroData; 
  QLabel* labPsiS; 
  QLCDNumber *lcdPsiS;
  QLabel *labPPsiS;
  QLCDNumber *lcdPPsiS;

  SensorTcpServer* ptrser; //added
  ComponentManager* ptr; //added
  
  // variables for output
#ifdef WIN32
  ShMem * shMem_;
#endif
  donnees_gyro dataToTransmit_;
};


#endif
