/*********************************************************************
//  created:    2008/12/10 - 17:33
//  filename:   mathFunctions.cpp
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Visual Odometry
*********************************************************************/
#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <string.h>
#include <limits> 
//=============================================================================
//OpenCV Includes
//=============================================================================
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#include "cvcam.h" 
#include "highgui.h"
//=============================================================================
//Levenberg Marquard (levmar v2.3) using LAPACK-BLAS
//=============================================================================
#include "lm.h"
//=============================================================================
using namespace std;
//=============================================================================

//Genaral functions
CvMat* expMat(CvMat* input);
void skewMat(CvMat* w, CvMat wHat);
double soNorm(CvMat* R);
double meanMat(CvMat* input, string type_, int index);
void StereoTriangulation (CvMat* feature, CvPoint2D32f x_left, CvPoint2D32f x_right, double fx, double fy, double baseline);
inline void dbSubs(double* x, double* y, double* output, int dim){for(int i=0;i<dim;i++)output[i]=x[i]-y[i]; }
inline double dbSum(double* x, int dim){double sum=0; 
for(int i=0;i<dim;i++)
	sum = sum + x[i];
return sum;}
inline double dbNorm(double* x) { return sqrt(pow(x[0],2)+pow(x[1],2)+pow(x[2],2)); }
inline double cvArrayNorm(CvMat* A) { double sum=0; 
for(int i=0;i<A->rows;i++)
	sum=sum+pow(A->data.db[i],2); 
return sqrt(sum); }
double cvVectorDirectionError(CvMat* x, CvMat* y);
//Conversion functions
void rigidTrans(CvMat*  output, double* input); //Overloaded function 
void rigidTrans(double* output, CvMat*  input); 

inline void   SETCVd_(CvMat* input, double val, int row, int col){cvSetAt(input,cvScalar(val),row-1,col-1);}
inline double GETCVd_(CvMat* input, int row, int col){return(cvGetAt(input,row-1,col-1).val[0]);}

//Specific Functions
void partialLogSO3(CvMat* partial, CvMat* R);
inline bool cvCheckDiag(CvMat* A){
	for(int i=0;i<A->cols;i++){
		if (numeric_limits<double>::infinity() == A->data.db[(A->rows*i)+A->cols]){		
			cvSetIdentity(A);
			return false;
		}
	}
	return true;
}
inline void swap(double* x, double* y) {double temp; temp = *x; *x = *y; *y = temp;}
int  splitArray(double* array_, double pivotValue, int startIndex, int endIndex);
void quickSort(double*  array_, int startIndex, int endIndex);

//Displaying Functions
void getNset (CvPoint2D32f srcPoint, IplImage* imSrc, CvPoint2D32f dstPoint, IplImage* imDst, CvSize patchDim); 
void takeNset(CvMat* patch,  CvPoint2D32f dstPoint, IplImage* imDst);
void cvimageSub(CvMat* src1, CvMat* src2, CvMat* dst);

//Quaternion Functions
void axisAngle2quat(double* w, double* q);

#endif //MATHFUNCTIONS_H