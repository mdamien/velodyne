/*********************************************************************
//  created:    2008/01/14 - 12:45
//  filename:   StereoRig.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Visual Odometry
*********************************************************************/
#ifndef STEREORIG_H
#define STEREORIG_H

//=============================================================================
//OpenCV Includes
//=============================================================================
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
//=============================================================================
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <string.h>

#include "mathFunctions.h"
#include "Tensor.h"
#include "irls.h"

#include "CanInterface.h"
//*****************************
//#define SIMULATION
//******************************
#define FEATURE_POINTS_LIMIT 600

///////////////////////////////////////////////////////////////
/// Stereo Feature Point Structure
///////////////////////////////////////////////////////////////
//#pragma pack(4) //32 bits padding
struct imFeaturePoint{
	double leftCoord	[2]; // non centered image coordinates 
	double rightCoord	[2]; // non centered image coordinates
	double leftOpFlow	[2]; // left image optical flow 
	double rightOpFlow	[2]; // right image optical flow
	double weight		[2]; // robust weight: [0]left weight [1] right weight
};
///////////////////////////////////////////////////////////////
/// Stereo Object Structure which is broadcasting as component output
///////////////////////////////////////////////////////////////

struct stereoObject{
	road_time_t		timeStart;  //timestamp first stereo pair
	road_time_t		timeEnd;	//timestamp second stereo pair
	road_time_t		timeProcc;	//time elapse for visual odometry
	double			odometry[6];	//Visual Odometry [Rotation angle(rad) + translation (mts)] 
	unsigned int	nbPoints;	//number of stereo features
	imFeaturePoint	stereoFeatures[FEATURE_POINTS_LIMIT];
};
//#pragma pack() //32 bits padding
///////////////////////////////////////////////////////////////
//=============================================================================
using namespace std;
//=============================================================================
class StereoRig
{
public:

	StereoRig();
	~StereoRig();
	
	//Public functions
	//Initialization functions
	void initObject(CvSize ConfigImageSize, CvMat* leftIntrinsicParam, CvMat* rightIntrinsicParam, CvMat* ExtrinsicParam, 
									int MaxFeatures, string FeatureDescriptor, CvPoint2D32f Clustering, 
									int half_windowSize, double correlation_threshold, double epipolar_threshold, double nearRange, double farRange, double rangeOffset, double maxSpeed, 
									int pyramid_levels, 
									int max_cycle_iter, double* lm_opts,
									int min_features_tracked, int max_irls_iter);

	void computeImageCluster(CvSize ConfigImageSize, CvPoint2D32f Clustering);
	//Principal function
	void Computing(IplImage* LeftImage, IplImage* RightImage, road_time_t timeStamp, CanInterface* canInit=NULL);
	//Stereo Computation functions
	void FeatureExtraction (IplImage* LeftImage, IplImage* RightImage, CvPoint2D32f* LeftPoints, CvPoint2D32f* RightPoints, int leftFeatureCount, int rightFeatureCount);
	void StereoMatching(IplImage* LeftImage, IplImage* RightImage,CvPoint2D32f* LeftPoints, CvPoint2D32f* RightPoints, int leftFeatureCount, int rightFeatureCount,
		char* leftStatus ,char* rightStatus, int* noCorresp, double* stereoCorresp, CvMat** intensityVector = NULL);
	
	void StereoFeatureDetection(IplImage* LeftImage, IplImage* RightImage);
	//Tracking functions
	void lkTracker(void);
	//Quadrifocal warping
	void quadWarping(void);
	//Quadrifocal Warping Function (Optimized Version)
	void quadWarpingOp(CanInterface* canComponentData);
	//3d Structure computation functions
	CvPoint3D64f Compute3Dpoint (CvPoint2D32f x_left,CvPoint2D32f x_right);

	//Access functions
	int				getCorrespNum(void)     {return noCorresp_[0];}
	double			getMaxDisparity(void)   {return MAX_DISPARITY;}
	double*			getStereoCorresp(void)  {return stereoCorresp_[0];}
	CvMat**			getIntensityVector(void){return intensityVector_[0];}
	CvMat*			getTranslation(void)	{return translation;}
	CvMat*			getRotation(void)		{return Rotation;}
	int				getIntegrity(void)		{return estimationIntegrity;}
	CvMat*			getCovariance(void)		{return estimationCovariance;}
	void			setTimeStart(void)		{prevTime = road_time();}
	road_time_t		getTimeStart(void)		{return currentTime;}
	road_time_t		getTimeEnd(void)		{return prevTime;}

	void			setProcessTime(road_time_t computationTime){outputStereoResults_->timeProcc = computationTime;}
	stereoObject*	getOdometryResults(void){return outputStereoResults_;}

private:
#ifdef SIMULATION
  int timeIdx;
#endif
	// TensorStruct object
	Tensor Trifocal;  
	//Feature parameters
	int				MAX_FEATURES;
	string			FEATURE_DESCRIPTOR;
	CvRect*			IM_CLUSTERS;
	CvPoint2D32f	IM_CLUSTER_DIM;
	bool			clustering_;
	//Matching parameters
	int				HALF_WINDOWSIZE;
	double			MAX_DISPARITY;
	double			MIN_DISPARITY;
	double			CORR_THRES;
	double			EPIPOLAR_THRES;
	double			MAX_RANGE;
	double			MIN_RANGE;
	double			RANGE_OFFSET;
	double			MAX_SPEED;
  //Traking parameters 
	int				PYRAMID_LEVELS;
	//Levenberg_Marquard parameters 
	int				MAX_CYCLE_ITER;
	double			LM_OPTS[5];
	//re-initialization parameters
	int				MIN_FEATURES_TRACKED;
	int				MAX_IRLS_ITER;

	//SVS Parameters
	CvSize ImageSize; 
	CvMat* leftIntrinsicParam_;
	CvMat* rightIntrinsicParam_;
	CvMat* ExtrinsicParam_;

	//Output variables
	int     noCorresp_[2];
	double* stereoCorresp_[2];
	CvMat** intensityVector_[2];

	stereoObject* outputStereoResults_;
	//swapping output variables
	int     swapNoCorresp;
	double* swapStereoCorresp;
	CvMat** swapIntensityVector;

	//Temporal variables
	IplImage* h1; 
	IplImage* h2; 
	int* LR_MatchIndex;								
	int* RL_MatchIndex;
	CvPoint2D32f* leftFeatures;
	CvPoint2D32f* rightFeatures;
	int noLeftFeatures; 
	int noRightFeatures;

	//LK AND KLT Tracker Variables;
	bool initTrack;

	//LK Traker variables
	int					flagPyramid;
	char*				leftStatus;								  //Index of tracked points
	char*				rightStatus;
	CvPoint2D32f*		leftTracks[2];      //Matched Features tracked from t_{0} to t_{1} 
	CvPoint2D32f*		rightTracks[2];
	IplImage*			currentLeftImage;			
	IplImage*			currentRightImage;
	IplImage*			prevLeftImage;
	IplImage*			prevRightImage;
	IplImage*			leftPyramid;
	IplImage*			rightPyramid;
	IplImage*			prevleftPyramid;
	IplImage*			prevrightPyramid;
	road_time_t			currentTime;
	road_time_t			prevTime;

	IplImage*			swapImage;						//Swapping variables
	IplImage*			swapPyramid;
	CvPoint2D32f*		swapTracks;
	road_time_t			swapTime;

	CvMat* Rotation;
	CvMat* translation;
	CvMat* axeAngleRotation;
	int	   estimationIntegrity;
	CvMat* estimationCovariance; //covariance of parameters !!!constant declaration!!
	
	//Private functions
	inline void updateStereoRange(CanInterface* canInit){
		double computation; 
		computation = MIN_RANGE+(static_cast<double>(canInit->getVehicleSpeed())*(RANGE_OFFSET/MAX_SPEED));		 
		MAX_DISPARITY = (ExtrinsicParam_->data.db[3])*(leftIntrinsicParam_->data.db[0]/computation);//delta max distance/max speed(Km/h)
		computation = MAX_RANGE+(static_cast<double>(canInit->getVehicleSpeed())*(RANGE_OFFSET/MAX_SPEED));
		MIN_DISPARITY = (ExtrinsicParam_->data.db[3])*(leftIntrinsicParam_->data.db[0]/computation);//delta max distance/max speed(Km/h)
	}
	//Stereo computation functions
	void Quick_Matching (IplImage* LeftImage, IplImage* RightImage, CvPoint2D32f* LeftPoints, CvPoint2D32f* RightPoints,
												int LeftPointsCounter, int RightPointsCounter,char* leftStatus ,char* rightStatus,int* MatchList, int half_windowSize, 
												const double matching_threshold,const double vertical_offset_threshold, bool INV_PARAMETERS=false);
	double nccCorrelation(CvMat* patch1, CvMat* patch2);
	void   SurfFeatures(IplImage* CvIm, CvPoint2D32f *surfFeatures, int* counter, int samplingStep, int octaves, double thres, bool doubleImageSize, int initLobe, bool upright, bool extended, int indexSize, bool bLaplacian);
	void   cvSurfFeatures(IplImage* CvIm, CvPoint2D32f *surfFeatures, int* counter);
	//Conversion functions
	void convertCvSeq2CvPoint(CvSeq* source, CvPoint2D32f* destination, int noElements);
	//Mouvement estimation
	void svdRegistration(CvPoint2D32f** leftFeatures, CvPoint2D32f** rightFeatures, int noFeatures, CvMat* R, CvMat* t);
	//Mouvement estimation by using optical flow
	void mouvementEstimation(CvPoint2D32f** leftFeatures, CvPoint2D32f** rightFeatures, int noFeatures, CvMat* R, CvMat* t);
	// Quadrifocal Objetif Warping function (Comport's approach)
	static void quadObjFunc(double* p, double* x, int m, int n, void* data);
	// Quadrifocal Objetif Warping function (Heudiasyc's approach)
	static void quadObjFunc_v2(double* p, double* x, int m, int n, void* data);
	// Quadrifocal Objectif Warping function (Optimized quadObjFunc_v2)
	int preLoadObjFunc(CvPoint2D32f* refPairs,CvPoint2D32f* trackedLKPairs); 
	static void quadObjFuncOp(double* p, double* x, int m, int n, void* data);
	static void jacobianObjFuncOp(double* p, double* jac, int m, int n, void* data);
};
#endif