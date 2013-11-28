/*********************************************************************
//  created:    2008/01/14 - 12:45
//  filename:   StereoCameraInterface.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Visual Odometry
*********************************************************************/

#ifndef STEREOCAMERAINTERFACE_H
#define STEREOCAMERAINTERFACE_H

#include <QThread>
#include <QApplication>
#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "CanInterface.h"
#include "GpsInterface.h"

//=============================================================================
// System Includes
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <conio.h>
//=============================================================================
//OpenCV Includes
//=============================================================================
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#include "cvcam.h" 
#include "highgui.h"
//=============================================================================
// Project Includes
#include "StereoRig.h"
//=============================================================================
// Utiliy Includes
#include "mainWindow.h"  //openGL output window
#include "inifile.h"
#include "kernel/road_time.h"

//******************************
//#define SIMULATION
//******************************

class StereoCameraInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	StereoCameraInterface(QString name);
	~StereoCameraInterface();
 
	virtual void stopActivity();
	virtual void startActivity();
	virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

protected:
	void run();

private:
#ifdef SIMULATION
	char leftFiles [64];
	char rightFiles[64];
	int indexFile;
#endif
	ShMem * tobeRead_;
	ShMem * stereoBuffer_;
	ShMem * disparityBuffer_;

	//Output for SensorComponent (All results:: Odometry, inliers, outliers)
	ShMem* tobeReadOutputStereo_;
	ShMem* outputStereoBuffer_;
	//Output for GEComponent (Google Earth)
	ShMem* outputVoComponent_;
	ShMem* outputGpsComponent_;

	void * offset;
	void * ptrLeftIm;
	void * ptrRightIm;
	void * ptrDisparity;
	void * ptrTimeStamp;
		
	IplImage* srcright; // Available gray level images in OpenCV format
	IplImage* srcleft;
	IplImage* srcdispmap; // Disparity map

	CvSize ImageSize_; // Image size variable
	bool color_;			// Color variable (Enable shared memory conversion)
	bool displaying_; // Enable stereo image output 
	unsigned int depth_; // number of channels
	int format_; // Color packing (RGB, XRGB,BGRX,...)
	
	//Input Files
	CIniFile Calibdata;
	CIniFile ConfigData;

	//Time variables	
	road_time_t tic_;  
	road_time_t toc_;
	void tic() { tic_ = road_time(); }
	void toc(char * text) { toc_ = road_time() - tic_; 
	printf("elapsed time us= %d %s\n", (int)(toc_), text ); }

////////////////////////////////////////////////
// COMPONENTS 
////////////////////////////////////////////////
	StereoRig		Odometry;      // StereoRig component

	CanInterface*	canOdometry;	// ABS car odometry 
	QMutex*			canMutex;
	bool			canState_;		// Can activation flag	
	bool            gpsState_;      // Gps activation flag
	GpsInterface*	gpsTrajectory;  // GPS position using GGA data
	QMutex*			gpsMutex;
	
////////////////////////////////////////////////
// COMPONENTS 
////////////////////////////////////////////////

	//Private functions
	void initDisplaying(void);
	void displayingOutput(void);
	void logOutputFile(void);
	//Display and output variables
	CvFont*		numbFont;
	mainWindow  openglWindow_;

	bool	recording_;
	QString	filePath_;
	FILE*	logFile_;
	CvMat*	Vect3x1_;
	CvMat*  Matrix6x6;

};
#endif //STEREOCAMERAINTERFACE_H