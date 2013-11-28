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
#include "PacpusTools/ShMem.h"

enum EWarningLevel {
	NOTASSOCIATED,
	SAFE,
	WARNING,
	EMERGENCY
};

class AlascaDisplayModule : public QObject, public AlascaDataModule
{
  Q_OBJECT

public:
  AlascaDisplayModule(QString name);
  ~AlascaDisplayModule();
  void compute(GlobalAlascaData data);
  void setImage(QImage*){};
  void setEmergencyDatas(const DONNEES_GGA * local_gga, const trame_vtg * local_vtg, const DONNEES_GGA * distant_gga, const trame_vtg * distant_vtg);
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

  DONNEES_GGA local_gga, distant_gga;
  trame_vtg local_vtg, distant_vtg;

  DONNEES_GGA local_gga_old, distant_gga_old;
  trame_vtg local_vtg_old, distant_vtg_old;

  double getDistance(double x1, double y1, double x2, double y2);
  void calculerPositions(double * x, double * y, const DONNEES_GGA * tgga_local, const trame_vtg * tvtg_local, const trame_gga_dbl * tgga_distant, const trame_vtg * tvtg_distant);
  EWarningLevel getAlertLevel(double gps_x, double gps_y, double radar_x, double radar_y, double acceleration);
};