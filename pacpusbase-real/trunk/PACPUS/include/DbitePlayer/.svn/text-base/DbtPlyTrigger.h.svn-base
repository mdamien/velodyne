/*********************************************************************
// created:    2007/04/12 - 16:30

//
// author:     Elie Al Alam & Gerald Dherbomez
// 
// version:    $Id: $
//
// purpose:    Dbite Player Trigger header file
*********************************************************************/




#ifndef _DBTPLYTRIGGER_H_
#define _DBTPLYTRIGGER_H_

#include <QThread>

#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"
#include "DbitePlayer/DbtPlyEngine.h"


#ifdef WIN32
#include <windows.h>
#include <mmsystem.h>
#endif

class DbtPlyEngine;

class DbtPlyTrigger : public QThread, public ComponentBase
{
 
  Q_OBJECT

public:
  DbtPlyTrigger(QString name);      //Constructeur
  ~DbtPlyTrigger();     //Destructeur
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
  DbtPlyEngine *eng ;
  //QTimer *timer_;
  virtual void run();

signals:
  void triggerSig();

protected:
  virtual void startActivity();
  virtual void stopActivity();

  

   

};

#endif
