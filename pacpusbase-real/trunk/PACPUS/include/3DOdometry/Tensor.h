/*********************************************************************
//  created:    2008/01/10 - 12:45
//  filename:   Tensor.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Visual Odometry
*********************************************************************/
#ifndef TENSOR_H
#define TENSOR_H

//=============================================================================
//OpenCV Includes
//=============================================================================
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#include "cvcam.h" 
//=============================================================================
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
//=============================================================================
#include "mathFunctions.h"
//=============================================================================
using namespace std;
//=============================================================================
class Tensor
{
public:
	typedef struct TrifocalStruct
	{
		CvMat* H;
		CvMat* P;
		CvMat* P_p;
		CvMat* P_pp;
		CvMat* a;  //Constant tensor part
		CvMat* b;	 //Dynamic tensor part (Mouvement function)
		CvMat**  Slides;
		CvMatND* T_ijk; //Tensor
	};
	
	Tensor();
	~Tensor();

	void init(CvMat* left_IntParam, CvMat* right_IntParam, CvMat* ExtParam);	
	void updateTensor(CvMat* Mouvement); // Mouvement update 
	void contraction(CvPoint2D32f* point, CvPoint2D32f* point_p, CvPoint2D32f* p123, CvPoint2D32f* p214);// Point transfer from first to third view via tensor contraction			
	//Access functions
	inline CvMat* getLeftIntParam(void)				 {return left_IntParam_ ;};
	inline CvMat* getRightIntParam(void)			 {return right_IntParam_;};
	inline CvMat* getLeftExtParam(void)				 {return left_ExtParam_ ;};
	inline CvMat* getRightExtParam(void)			 {return right_ExtParam_;};
	inline CvMat* getFundamentalMat(void)			 {return FundamentalMatrix_;}
	inline TrifocalStruct* getTTensor(int TNumber) { if (TNumber==1)return &C123; else if(TNumber==2) return &C214;} 

private:
	CvMat* left_IntParam_;
	CvMat* right_IntParam_;
	CvMat* left_ExtParam_;
	CvMat* right_ExtParam_;
	CvMat* FundamentalMatrix_;
	TrifocalStruct C123;					//Trifocal tensor 1 
	TrifocalStruct C214;					//Trifocal tensor 2

	void skew(CvMat* Input, CvMat* Output); // Returns a skew-symetric matrix
	void freeTensor(TrifocalStruct Tensor);
};
#endif