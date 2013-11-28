/*********************************************************************
// created:    2006/03/30 - 14:39
// filename:   DummyComponent.h
//
// author:     Gerald Dherbomez
// 
// purpose:    How to create a component 
*********************************************************************/

#ifndef _DUMMYCOMPONENT_H_
#define _DUMMYCOMPONENT_H_


#include <QThread>
#include "kernel/ComponentBase.h"

#include <QtPlugin>

class DummyComponent : public QThread, public ComponentBase
{
  Q_OBJECT
    
public:
  DummyComponent(QString name); 
  ~DummyComponent(); 
  
  virtual void stopActivity(); /*!< to stop the processing thread */
  virtual void startActivity(); /*!< to start the processing thread */
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

protected:
private:
  void run(); /*!< the main loop of the thread */ 

  bool ComponentAlive; 

};


#endif