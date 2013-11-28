/*********************************************************************
//  created:    2010/03/26 - 14:30
//  filename:   VelodyneViewer.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/

#ifndef VELODYNEVIEWER_H
#define VELODYNEVIEWER_H

#include <qframe.h>
#include <qthread.h>

#include "kernel/road_time.h"
#include "PacpusTools/ShMem.h"
#include "kernel/ComponentBase.h"
#include "structure/structure_velodyne.h"
#include "glWidget.h"
#include "VelodyneViewerConfig.h"

namespace pacpus {

class VELODYNEVIEWER_API VelodyneViewer
    : public QThread
    , public ComponentBase
{
  Q_OBJECT

public:
  VelodyneViewer(QString name);
  ~VelodyneViewer();

  virtual void stopActivity(); /*!< to stop the processing thread */
  virtual void startActivity(); /*!< to start the processing thread */
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 
  
signals: 
  void motion(double*);
  void display();

protected:
  void run();

private:
  QFrame window_;
  struct VelodynePolarData velodyneData_;
  ShMem* shMem_; 
  bool running_;  
  
  glWidget * glWidget_;
};

} // namespace pacpus

#endif // VELODYNEVIEWER_H
