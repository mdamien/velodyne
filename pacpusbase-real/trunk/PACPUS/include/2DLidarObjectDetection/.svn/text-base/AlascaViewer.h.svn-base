/*********************************************************************
//  created:    2007/11/08 - 16:45
//  filename:   AlascaViewer.h
//
//  author:     Gerald Dherbomez
// 
//  version:    $Id: $
//
//  purpose:    
*********************************************************************/

#include <QApplication>

#include <QMutex>

#include "Plot2D.h"
#include "kernel/ComponentBase.h"


#define POLAR_DISTANCE_RESOLUTION 20


class AlascaViewer : public Plot2D, public ComponentBase
{
  Q_OBJECT
public:
  AlascaViewer(QString name);
  ~AlascaViewer();

  virtual void stopActivity(); 
  virtual void startActivity(); 
  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

protected slots:
  void updateDisplay(); 

signals:
  void replot();

private:
  void setPointsOfOpenAngleCurve(); 

  bool displayOpeningAngle_;
  double xOpenAngleCurve_[3]; 
  double yOpenAngleCurve_[3]; 
  double openingAngle_; 

  double polarDistStep_; 
  double range_; 
  int nbPolarDistCurves_; 

  int minRefreshPeriod_; // microseconds
  road_time_t tk_;
  road_time_t tkOld_; 

};
