/*********************************************************************
// created:    2006/01/30
// created:    2006/01/30 - 10:58
// filename:   xmlcomponentconfig.h
//
// author:     Gerald Dherbomez
// 
// purpose:    définit la structure XML des paramètres de configuration
//             d'un composant
*********************************************************************/

#ifndef _XMLCOMPONENTCONFIG_H_
#define _XMLCOMPONENTCONFIG_H_


#include <qdom.h>


class XmlConfigFile; 

class XmlComponentConfig
{
public:
  XmlComponentConfig(QString name); 
  XmlComponentConfig(); 
  ~XmlComponentConfig(); 
  void addProperty(QString name); 
  int delProperty(QString name); 
  QString getProperty(QString name); 
  void setProperty(QString name, QString value); 
  QDomElement qDomElement(); 
  void localCopy(QDomElement elementToCopy); 
  QString const getComponentName(); 
  QString const getComponentType(); 
protected:
private:
  QDomElement _component; 
  XmlConfigFile* _parentDocument; 
};

#endif