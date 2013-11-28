/*********************************************************************
// created:     2006/02/07 - 11:59
// filename:    component.h
//
// author:      Gerald Dherbomez
// 
// purpose:     generic ComponentBase class. This is an abstract class
// 
// todo:        - see if some methods can be private with ComponentManager
//              friendship 
//              - include the copy of Xml node in param here
//              - see if there is a possibility to avoid the constraint
//              on parameters in the constructor of derived class
*********************************************************************/

#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <qstring.h>

#include "pacpus.h"
#include "XmlComponentConfig.h"
#include "ComponentManager.h"

class ComponentBase
{
  friend class ComponentManager;
public:
  // Here is the enumeration of the state that can take a component
  // The 3 last states suppose that the component is started
  enum COMPONENT_STATE {STOPPED, NOT_MONITORED, MONITOR_OK, MONITOR_NOK};
  
  // The different identifying the configuration of the component
  enum COMPONENT_CONFIGURATION { CONFIGURED_OK, NOT_CONFIGURED, CONFIGURATION_DELAYED, CONFIGURED_FAILED };
  
  // constructor - your derived component must have only one parameter
  // in its constructor which is name
  ComponentBase(QString name);

  // destructor
  virtual ~ComponentBase(); 
  
  // return the state of the component 
  COMPONENT_STATE getState();

  // return true if the component is configured, false else
  inline bool isConfigured() 
  {
    if (configuration_ == CONFIGURED_OK) 
    return true; 
  else 
    return false;
  }

protected:
  // convenient function to initialize quickly a DBT file. Parameters are: 
  // - the name of the DBT file
  // - the type of data. refer to constantes in io_hdfile.h
  // - the size of data, typically apply sizeof() on the structure you create
  hdfile_t* inithdFile( char *nom, int type, int size);

  // define the state of the component
  void setState(COMPONENT_STATE state); 

  // pure virtual function - what to do when the component starts? 
  virtual void startActivity() = 0; 

  // pure virtual function - what to do when the component stops? 
  virtual void stopActivity() = 0;   

  // This function is called by the ComponentManager when it loads the XML file
  // It gives to the component the XML node corresponding to its
  // So the component can handle some properties defined in the XML config file 
  // via XmlComponentConfig methods
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config) = 0; 
  
  // The XML node that is got in the configureComponent method
  XmlComponentConfig param; 

  // the name of the component. It is this one in the XML config file
  QString componentName; 

  // is the component is recording data?
  bool recording; 

  // provided for compatibility with old DBITE framework
  bool THREAD_ALIVE; 

  // is the component active?
  bool activity;

  // a pointer to the manager of components
  ComponentManager* mgr;

private:
  // called by the ComponentManager to start the component
  int startComponent(); 

  // called by the ComponentManager to stop the component
  int stopComponent(); 

  // store the state of the component
  COMPONENT_STATE componentState_; 

  // is the component configured (ie configureComponent method was called)
  COMPONENT_CONFIGURATION configuration_;
};


#endif
