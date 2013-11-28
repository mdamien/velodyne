/*********************************************************************
// created:    2007/04/12 - 16:30
//
// author:     Elie Al Alam & Gerald Dherbomez
//             Heudiasyc UMR UTC/CNRS 6599 Copyright
// 
// version:    $Id: $
//
// purpose:    Dbite Player User interface header file
*********************************************************************/


#ifndef _DBTPLYUSERINTERFACE_H_ 
#define _DBTPLYUSERINTERFACE_H_


#include <QString>
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>

#include "kernel/ComponentBase.h"
#include "kernel/ComponentFactory.h"

#include "DbtPlyFileManager.h"
#include "DbtPlyEngine.h"



// Forward declaration
class DbtPlyEngine;

class DbtPlyUserInterface : public QWidget, public ComponentBase
{
  Q_OBJECT

public:
  // Constructor
  DbtPlyUserInterface( QString name);      

  // Destructor
  ~DbtPlyUserInterface();

	inline int timeSliderValue() { return timeSlider->value(); }

public slots:
  void displayStateSlot(int state, float speed);
  void displayMinMaxTime( road_time_t min, road_time_t max);
  void displayTime(road_time_t time);


protected:

  virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);
  virtual void startActivity();
  virtual void stopActivity();

  void closeEvent(QCloseEvent * e);

  DbtPlyEngine * eng;
  
  QWidget* wTel_ ;
  QButtonGroup *butGroup;
  QPushButton * playBut ;
  QPushButton * pauseBut ;
  QPushButton * stopBut ;
  QPushButton * speedUpBut ;
  QPushButton * speedDownBut ;
  QLabel *lab;
  QCheckBox *rev;
  QSlider * timeSlider;
  QLabel * timeMinTitle;
  QLabel * timeMinValue;
  QLabel * timeMaxTitle;
  QLabel * timeMaxValue; 
  QLabel * timeCurTitle;
  QLabel * timeCurValue;

private:
  // current max time 
  road_time_t tMax_;
  // current min time
  road_time_t tMin_;
  // current absolute time
  road_time_t absTime_;
  // current relative time
  int relTime_;
};

#endif
