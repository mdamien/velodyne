/*********************************************************************
//  created:    2008/04/28 - 15:34
//  filename:   CameraInterface.h
//
//  author:     Gerald Dherbomez
//              Heudiasyc UTC/CNRS UMR6599 Copyright
// 
//  version:    $Id: $
//
//  purpose:    
//              
*********************************************************************/


#ifndef __CameraInterface_h__
#define __CameraInterface_h__


#include <QThread>

#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "EBAlascaDisplayModule.h"

class CameraInterface : public QThread, public ComponentBase
{
public:
  CameraInterface(QString name); 
  ~CameraInterface();

protected:
  void run();
  void startActivity();
  void stopActivity();
  ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

private:
  ShMem * shMem_;
  QImage * image_;

  AlascaDataModule * processing_;

  QString imageFormat_;
  int imageWidth_;
  int imageHeight_;
};



#endif // __CameraInterface_h__