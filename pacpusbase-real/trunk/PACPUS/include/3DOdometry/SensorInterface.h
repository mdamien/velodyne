/*********************************************************************
//  created:    2009/11/10 - 15:34
//  filename:   SensorInterface.h
//
//  author:     Sergio Rodriguez
//              Heudiasyc UTC/CNRS UMR6599 Copyright
// 
//  version:    $Id: $
//
//  purpose:    
//              
*********************************************************************/


#ifndef __SENSORINTERFACE_H__
#define __SENSORINTERFACE_H__


#include <QThread>

#include "kernel/ComponentBase.h"
#include "pacpusTools/ShMem.h"
#include "kernel/road_time.h"

#include "ImageProjection.h"
#include "AlascaDataModule.h"
#include "ImageViewer.h"
#include "StereoRig.h"
#include "window.h"
#include "inifile.h"
//=============================================================================
//OpenCV Includes
//=============================================================================
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"


class SensorInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	SensorInterface(QString name);  
	~SensorInterface();

protected:
	void run();
	void startActivity();
	void stopActivity();
	ComponentBase::COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config);

signals:
	void leftImageEmission(QImage*);
	void rightImageEmission(QImage*);

private:

	//BEGIN log files variables
	bool	recording_;
	QString filePath_;
	FILE*	logFile_;

	FILE*   binaryStereo_;
	FILE*   binaryLidar_;
	//END log files variables

	QMap<int,ShMem*>	shMemArray_;
	
	//Output for SensorComponent (All results:: Odometry, inliers, outliers)
	ShMem*				outputStereoBuffer_;
	void*				offsetStereoOutput_;
	void*				stereoOutputPtr_;
	stereoObject*		visualOdometry_;

	//Stereo vision control and data variables 
	void*				leftPtrIm_;
	void*				rightPtrIm_;

	QImage*				leftImage_;
	QImage*				rightImage_;

	QImage*				leftEnhancedImage_;
	QImage*				rightEnhancedImage_;

	ImageViewer*		leftImageViewer_;
	QMutex*				leftMutex_;

	ImageViewer*		rightImageViewer_;
	QMutex*				rightMutex_;
	
	QString				imageFormat_;
	unsigned int		depth_;			// number of channels
	int					imageWidth_;
	int					imageHeight_;
	
	// Lidar control and data variables
	ShMem*				lidarBuffer_;
	void*				offsetLidar_;
	void*				lidarDataPtr_;
	void*				lidarObjectListPtr_;
	ScanAlascaData*		lidarPoints_;
	lidarObjectList*	lidarObjects_;

	// lidar - vision fusion variables
	CIniFile			Calibdata;
	// declaration of Camera-Alasca calibration parameters
	CvMat*				K;
	CvMat*				R;
	CvMat*				t;

	// Slider Window 
	window				dashboard_;
	//Projector
	ImageProjection		projector; //to be use for image dara projection

	void processingStereo_(void);
	void processingLidar_ (void);

	void StereoLidarProjection(void);
	void YtoRGB32(unsigned char *, const unsigned char *, int, int);
};
#endif // __SENSORINTERFACE_H__