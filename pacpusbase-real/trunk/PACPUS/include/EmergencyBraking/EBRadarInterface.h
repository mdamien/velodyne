#ifndef __RADARINTERFACE_H__
#define __RADARINTERFACE_H__



#include <QThread>


#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "EBAlascaDisplayModule.h"
#include "structure/structure_radar.h"



class RadarInterface : public QThread, public ComponentBase
{
  Q_OBJECT

public:
  RadarInterface(QString name);
  ~RadarInterface();

protected:
  void run(); 
  virtual void stopActivity(); 
  virtual void startActivity(); 
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

private:
  DONNEE_RADAR incomingRadarData; 

  // The shared memory where data are provided
  ShMem * shMem_;
  
  AlascaDataModule * processing_;

  };


#endif // __RADARINTERFACE_H__