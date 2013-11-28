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
#include "LidarInterface.h"
#include "StereoInterface.h"

class dashBoard : public QWidget
{
	Q_OBJECT
public:
	QLCDNumber *lcdLidar_;
	QCheckBox  *ckbxLidar_;

	QLCDNumber *lcdStereo_;
	QCheckBox  *ckbxStereo_;

	bool startStopToggle_;
	QPushButton *startStop_;
	QPushButton *quit_;
	QPushButton *getDataButton_;

	dashBoard(QWidget *parent = 0);

public slots:
	void startStopComponents(void);
	void lidarStateComponent(bool state);
	void stereoStateComponent(bool state);
	inline void getData(void){
		lidarComponent->setFileCount(0); 
		stereoComponent->setFileCount(0);
		lidarComponent->startGetButton_();
		stereoComponent->startGetButton_();}

private:
	ComponentManager*	componentManager_;
	LidarInterface*		lidarComponent;
	StereoInterface*	stereoComponent;
};
#endif
