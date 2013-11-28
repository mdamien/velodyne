/*********************************************************************
//  created:    20011/02/12 - 16:25
//  filename:   CanInterface.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Planar Odometry using CAN (wheel speed sensors and yaw rate gyro)
*********************************************************************/
#ifndef CANINTERFACE_H
#define CANINTERFACE_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4996)
#endif // _MSC_VER

#include <highgui.h>
#include <cv.h>
#include <cvaux.h>
#include <cxcore.h>

#ifdef _MSC_VER
#   pragma warning(push)
#endif // _MSC_VER

#include <qapplication.h>
#include <qmutex.h>
#include <qthread.h>

#include "kernel/ComponentBase.h"
#include "PacpusTools/ShMem.h"
#include "structure/structureCanCarmen.h"

#define PI_ 3.141592653589793

class threadComponent;

class CanInterface : public QThread, public ComponentBase
{
	Q_OBJECT

public:
	CanInterface(QString name);
	~CanInterface();

	virtual void stopActivity();
	virtual void startActivity();
	virtual COMPONENT_CONFIGURATION configureComponent(XmlComponentConfig config); 
  
	inline void update(double* egoMotion){
	  canServerMutex_->lock();
	  memcpy(egoMotion,    rotationServer_->data.ptr, 3*sizeof(double));
		memcpy(egoMotion+3,  translationServer_->data.ptr, 3*sizeof(double));
		cvSetZero(rotationServer_);
		cvSetZero(translationServer_);
		cvSetIdentity(RotationServer_);
	  canServerMutex_->unlock();
	};
	
	inline float update(CvMat* RotationIn, CvMat* translationIn){ 
	  canMutex_->lock();
	  // update the estimated ego-motion and reinitializes the Bufferized transformations 
		memcpy(Rotation->data.ptr,      rotation_[2]->data.ptr,    3*sizeof(double));
		memcpy(translation->data.ptr,   translation_[2]->data.ptr, 3*sizeof(double));
		memcpy(RotationIn->data.ptr,    rotation_[2]->data.ptr,    3*sizeof(double));
		memcpy(translationIn->data.ptr, translation_[2]->data.ptr, 3*sizeof(double));
		cvSetZero(rotation_[2]);
		cvSetZero(translation_[2]);
		cvSetIdentity(Rotation_[2]);
		vehicleSpeed = vehicleSpeed_;
		canMutex_->unlock();
		return vehicleSpeed;
		};

protected:
	void run();

private:
  threadComponent* yawRateThread_;

	bool	recording_;
	QString filePath_;
	FILE*	logFile_;

	QMutex*	canMutex_;       //Direct Client component request
	QMutex* canServerMutex_; // Sencondary client
	QMutex* wssgyroMutex_;   //Internal multi threaded component
	
	ShMem*  shMemWSS_;
	
	TimestampedStructVehicleSpeed			odometry_;
	
	bool firstTimeOdometry;

	road_time_t motionTime_[2];
	double			motion_[4];

	//[0]:Global Bufferized transformation 
	//[1]:Last transformation
	//[2]:Ego-motion transformation (sampled at an external fequency)

	CvMat*	Rotation_[3];			// DCM rotation matrix
	CvMat*  rotation_[3];		  // Rodrigues rotation vector 
	CvMat*	translation_[3];  // translation vector
	CvMat*  Mat3x3;
	CvMat*  Vec3x3;
	
	CvMat*  RotationServer_;   //variables for a second client 
	CvMat*  rotationServer_;   //these variables can be only accessed through
	CvMat*  translationServer_;//the fonction void update(CvMat*,CvMat*)
	CvMat*  Mat3x3aux;
	CvMat*  Vec3x3aux;

	float	vehicleSpeed_; //local copy of vehicle speed

	CvMat* Rotation;         //Last Accessed (Rotation)		Ego-motion
	CvMat* translation;      //Last Accessed (translation)Ego-motion
	float  vehicleSpeed;     //current access vehicle speed

	void processing_(TimestampedStructVehicleSpeed    myOdometry);
	
	void update_(void);
};

class threadComponent
    : public QThread
{
	Q_OBJECT

  public:
	  threadComponent();
	  ~threadComponent();
	
	  void          stopActivity();
	  void          startActivity();
    inline void   setInternalMutex(QMutex* wssgyroMutex) { wssgyroMutex_ = wssgyroMutex; };
    inline double getCap(void) { double tempVar = bufferCap_; bufferCap_= cap_[2]; return (cap_[2]-tempVar)*PI_/180; };
	protected:  
	  void run();
	
	private:
	  ShMem* shMemGYRO_;
	  bool   THREAD_ALIVE_;
	  
	  QMutex* wssgyroMutex_;   //Internal multi threaded component
	  
	  TimestampedStructLateralDynamics		latDyn_;
	  bool firstTimeLatDyn;
	  
	  road_time_t capTime_[2];
  	double			cap_[3];
    double	    bufferCap_;
	  
	  void processing_(TimestampedStructLateralDynamics myLatDyn);	
};

#endif //CANINTERFACE_H
