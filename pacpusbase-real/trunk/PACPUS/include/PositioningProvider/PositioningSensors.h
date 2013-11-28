/*********************************************************************
//  created:    2006/10/16 - 11:49
//  filename:   PositioningSensors.h
//
//  author:     Pierre-Michel Bonnifait Copyright Heudiasyc UMR UTC/CNRS 6599
//
//  version:    $Id: PositioningSensors.h 277 2007-09-04 15:47:11Z gdherbom $
//
//  purpose:    Class definition for the sensors
				It captures the results in shared memory
*********************************************************************/

#ifndef _POSITIONINGSENSORS_H_
#define _POSITIONINGSENSORS_H_

#include "struct.h"

class PositioningSensors : public QObject, public QThread, public ComponentBase
{
  Q_OBJECT

public:
	PositioningSensors (const char*);
	~PositioningSensors ();
	void					configureComponent(XmlComponentConfig config);
	void					startActivity ();
	void					stopActivity();
	struct s_SensorsData	getSensors ();
	void					run ();

signals:
	void					absSignal ();
	void					gyroSignal ();

private:
	void					initGpsShGet ();
	void					initAbsShGet ();
	void					initGyroShGet ();

  // Shared memory created and updated by the sensors 
  ShMem *shMemAbs_; 
  ShMem *shMemGyro_; 
  ShMem *shMemGps_; 

  // local copy of sensor data 
	struct donnees_gps*		gpsShGet_;
	struct donnees_abs_zy*	absShGet_;
	struct donnees_gyro*	gyroShGet_;

  // a compilation of all data coming from the sensors
 	struct s_SensorsData sensorData_;

  // variable that says if the thread is running
	bool ended_;

};

#endif /* !_POSITIONINGSENSORS_H_ */
