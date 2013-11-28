/*********************************************************************
// created:    2007/04/12 - 16:30

//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player Telemetre Manager header file
*********************************************************************/



#ifndef _DBTPLYTELEMETREMANAGER_H_
#define _DBTPLYTELEMETREMANAGER_H_

#include <QThread>
#include <QObject>
#include <QLCDNumber>

#include "kernel/ComponentBase.h"
#include "DbtPlyFileManager.h"
#include "kernel/ComponentFactory.h"
#include "DbtPlyUserInterface.h"
#include "DbtPlyIOShMemTel.h"


class DbtPlyTelemetreManager : public DbtPlyFileManager
{
  Q_OBJECT

public:
  DbtPlyTelemetreManager(QString name);      
  ~DbtPlyTelemetreManager();     
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

  QLCDNumber *lcd_;
  float *bufTel;
#ifdef WIN32
  DbtPlyIOShMemTel *sharedMemory;
#endif
  TELEMETER_DATA dataTelem;
protected:
  void processData (road_time_t, road_timerange_t, void *);
  virtual void startActivity();
  virtual void stopActivity();
  HANDLE hd_data;
  void displayUI();


signals :
  void displayTel(double);


};

#endif
