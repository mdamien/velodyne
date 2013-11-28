/*********************************************************************
// created:    2006/01/30 - 12:31
// filename:   xmlconfigfile.h
//
// author:     Gerald Dherbomez
//
// purpose:    Classe permettant d'enregistrer un fichier de 
//             configuration XML
//             Le fichier XML contient 2 sections : 
//             - parameters : contient les parametres de l'application 
//             - components : contient les composants
//             les composants ne peuvent pas avoir de noeuds fils
//
// todo:       Creer une dtd qui permet de definir la liste des classes possibles
//             que peuvent prendre les composants 
//             
*********************************************************************/


#ifndef _XMLCONFIGFILE_H_
#define _XMLCONFIGFILE_H_

#include <QDomDocument>
#include <QFile>
#include <QMutex>
#include <QStringList>

#include "XmlComponentConfig.h"


class XmlConfigFile
{
   friend XmlComponentConfig::XmlComponentConfig(QString);
   friend class ComponentManager;

public:
  static XmlConfigFile* create(); 
  static void destroy();  
  QDomElement getComponent(QString name); 
  QStringList getAllComponents(); 
  int loadFile(QString fileName); 

  // not used
  void saveFile(QString fileName);
  // not used
  void addComponent(QDomElement component); 
  // not used
  void delComponent(QDomElement component); 
 
protected:
private:
  XmlConfigFile(); 
  ~XmlConfigFile();
  static XmlConfigFile* _xmlConfigFile; 
  QDomElement createComponent(QString name); 
  QDomDocument _document; 

  QFile* _file; 
  QMutex _mutex; 
  int _numberOfComponents; 
};

#endif

