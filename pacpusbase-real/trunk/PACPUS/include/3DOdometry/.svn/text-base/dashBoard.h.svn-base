/*********************************************************************
//  created:    2009/07/07 - 14:50
//  filename:   dashBoard.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Visual Odometry
*********************************************************************/
#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QApplication>
#include <QFont>
#include <QGroupBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QWidget>

#include "kernel/ComponentBase.h"
#include "StereoCameraInterface.h"
#include "CanInterface.h"
#include "GpsInterface.h"
#include "LidarInterface.h"
#include "VisionInterface.h"
#include "SensorInterface.h"

class dashBoard : public QWidget
{
	Q_OBJECT
public:
	QLCDNumber *lcdStereo_;
	QLCDNumber *lcdCan_;
	QLCDNumber *lcdGps_;
	QLCDNumber *lcdLidar_;
	QLCDNumber *lcdVision_;
	QLCDNumber *lcdSensor_;

	QCheckBox  *ckbxStereo_;
	QCheckBox  *ckbxCan_;
	QCheckBox  *ckbxGps_;
	QCheckBox  *ckbxLidar_;
	QCheckBox  *ckbxVision_;
	QCheckBox  *ckbxSensor_;

	bool		startStopToggle_;
	QPushButton *startStop_;
	QPushButton *quit_;

	dashBoard(QWidget *parent = 0);
public slots:
	void startStopComponents(void);
	void stereoStateComponent(bool state);
	void canStateComponent(bool state);
	void gpsStateComponent(bool state);
	void lidarStateComponent(bool state);
	void visionStateComponent(bool state);
	void sensorStateComponent(bool state);

private:
	ComponentManager*		componentManager_;
	
	StereoCameraInterface*	stereoComponent;
	CanInterface*			canComponent;
	GpsInterface*			gpsComponent;
	LidarInterface*			lidarComponent;
	VisionInterface*		visionComponent;
	SensorInterface*		sensorComponent;
};
#endif
