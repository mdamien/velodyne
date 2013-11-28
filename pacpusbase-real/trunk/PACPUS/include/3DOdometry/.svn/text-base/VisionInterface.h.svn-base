/*********************************************************************
//  created:    2009/12/18 - 13:40
//  filename:   VisionInterface.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Obstacle detection
*********************************************************************/

#ifndef VISIONINTERFACE_H
#define VISIONINTERFACE_H

#include <QThread>
#include <QApplication>
#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"

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
//Disparity Map Lib Includes
//=============================================================================
#include "stereoMatching.h"
//=============================================================================
// Utiliy Includes
#include "mainWindow.h"  //openGL output window
#include "inifile.h"
#include "kernel/road_time.h"

//******************************
//#define SIMULATION
//******************************

class VisionInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	VisionInterface(QString name);
	~VisionInterface();
 
	virtual void stopActivity();
	virtual void startActivity();
	virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 

protected:
	void run();

private:

	ShMem * tobeRead_;
	ShMem * stereoBuffer_;
	ShMem * disparityBuffer_;

	void * offset;
	void * ptrLeftIm;
	void * ptrRightIm;
	void * ptrTimeStamp;
		
	IplImage*	srcright; // Available gray level images in OpenCV format
	IplImage*	srcleft;
	road_time_t	timeStamp_;

	CvSize ImageSize_;		// Image size variable
	bool color_;			// Color variable (Enable shared memory conversion)
	unsigned int depth_;	// number of channels
	int format_;			// Color packing (RGB, XRGB,BGRX,...)
	
	// Disparity map variables
	StereoMatching * stereoContext_;
	StereoImage    * dispImage_; 
	uchar          * leftSwapIm_; 
	uchar          * rightSwapIm_;
	IplImage       * disparityOut_;

	//Input Files
	CIniFile Calibdata;
	CIniFile ConfigData;

	//Time variables	
	road_time_t tic_;  
	road_time_t toc_;
	void tic() { tic_ = road_time(); }
	void toc(char * text) { toc_ = road_time() - tic_; 
	printf("elapsed time us= %d %s\n", (int)(toc_), text ); }

	//Private functions
	void initDisplaying(void);
	void displayingOutput(void);
	void logOutputFile(void);

	bool	recording_;
	QString	filePath_;
	FILE*	logFile_;
	FILE*   binDispMap_;
	FILE*   binLeftIm_;

};
#endif //VISIONINTERFACE_H