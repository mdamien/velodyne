/*********************************************************************
//
// created:    2006/01/30 - 10:58
//
// filename:   xmlcomponentconfig.h
//
// author:     Gerald Dherbomez
// 
// purpose:    definit la structure XML des paramètres de configuration
//             d'un composant
*********************************************************************/

#ifndef _XMLCOMPONENTCONFIG_H_
#define _XMLCOMPONENTCONFIG_H_


#include <QDomElement>


class XmlConfigFile; 

class XmlComponentConfig
{
  friend class ComponentManager;
  
public:
  XmlComponentConfig(QString name); 
  XmlComponentConfig(); 
  ~XmlComponentConfig(); 
  void addProperty(QString name); 
  int delProperty(QString name); 
  QString getProperty(QString name); 
  void setProperty(QString name, QString value); 

private:
  QDomElement qDomElement(); 
  void localCopy(QDomElement elementToCopy); 
  QString const getComponentName(); 
  QString const getComponentType(); 
  QDomElement component_; 
  XmlConfigFile* parentDocument_; 
};

#endif
