/*********************************************************************
//  created:    2008/3/10 - 18:41
//  filename:   AlascaDisplayModule.h
//
//  author:     Gerald Dherbomez
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/



#include "viewer/AlascaDataModule.h"
#include "viewer/AlascaViewer3D.h"
#include "structure/structure_radar.h"


class AlascaDisplayModule : public QObject, public AlascaDataModule
{
  Q_OBJECT

public:
  AlascaDisplayModule(QString name);
  ~AlascaDisplayModule();
  void compute(GlobalAlascaData data);
  void setImage(QImage*){};
  void setWheelSpeed(TimestampedStructWheelSpeed);

  void setRadar(const DONNEE_RADAR &data_radar);

signals:
  void refreshDisplay();

protected:
  virtual void startActivity(){};
  virtual void stopActivity(){};
  virtual ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config)
	{ return ComponentBase::CONFIGURED_OK; };

private:
  // A pointer on the 3D viewer component
  AlascaViewer3D * viewer3d_;
  DONNEE_RADAR dataRadar_;
  StructWheelSpeed dataSpeed_;
};