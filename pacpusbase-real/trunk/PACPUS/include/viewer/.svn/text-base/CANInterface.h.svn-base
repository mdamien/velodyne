/*********************************************************************
//  created:    2008/04/28 - 15:34
//  filename:   CANInterface.h
//
//  author:     Gerald Dherbomez
//              Heudiasyc UTC/CNRS UMR6599 Copyright
// 
//  version:    $Id: $
//
//  purpose:    
//              
*********************************************************************/


#ifndef __CANInterface_h__
#define __CANInterface_h__


#include <QThread>

#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "structure/structureCanCarmen.h"
#include "driver/CanDriverBase.h"
#include "AlascaDisplayModule.h"
#include "AlascaLOVeComputing.h"


class CANInterface : public QThread, public ComponentBase
{
public:
  CANInterface(QString name);
  ~CANInterface();


protected:
	void run();
  void startActivity();
  void stopActivity();
  ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

  TimestampedCanFrame canFrame_;
  TimestampedStructSuspension suspension_;
  TimestampedStructWheelSpeed wheelspeed_;
  TimestampedStructVehicleSpeed odometry_;
  TimestampedStructRawLateralDynamics rawLatDyn_;
  TimestampedStructSteeringWheel steeringWheel_;
  TimestampedStructLateralDynamics latDyn_;

  QMap<int,ShMem*> shMem_;

private:
  AlascaDataModule * processing_;

};


#endif // __CANInterface_h__