/*********************************************************************
//  created:    2009/03/03 - 17:05
//  filename:   irls.h
//
//  author:     Sergio Rodriguez
// 
//  version:    $Id: $
//
//  purpose:    Iterative Re-Weighted Least Squares Template
*********************************************************************/
#ifndef IRLS_H
#define IRLS_H

//=============================================================================
//OpenCV Includes
//=============================================================================
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"

#include "mathFunctions.h"

namespace IRLS_NAMESPACE{
	///////////////////////////////////////////////////////////////
	/// Robust reweighting using BeatonTukey weighting function
	/// (type BeatonTukey) for IRLS.
	/// This structure can be passed as the second template argument in IRLS.
	///////////////////////////////////////////////////////////////
	struct BeatonTukey {
		double sdInlier;
		double scale;
		inline double reweight(double x, bool* state){ 
			if(x <= sdInlier ){*state = false; // this is normally weighted
				return pow(1 - pow(x/sdInlier, 2.0), 2.0);
			}
			else{*state = true; // this is a new outlier!!!
			return 0;}
		}
		inline double trueScale(double x) {return x/scale; }
		};
	///////////////////////////////////////////////////////////////
	/// Robust reweighting using Huber weighting function
	/// (type Huber) for IRLS.
	/// This structure can be passed as the second template argument in IRLS.
	///////////////////////////////////////////////////////////////
	struct Huber {
		double sdInlier;
		double scale;
		inline double reweight(double x, bool* state)	{ if(x <= sdInlier)	// this is normally weighted
			return 1;	
		else if (x > sdInlier) 	// it should be an outlier 
			return ( sdInlier * ( x/fabs(x) ) )/x; 
		else{
			cout << "Incosistent behavior on irls algorithm" << endl;
			return -1;}}
		inline double trueScale(double x) {return x/scale; }
		};
	///////////////////////////////////////////////////////////////
	/// Robust reweighting (type I) for IRLS.
	/// A reweighting class with \f$w(x)=\frac{1}{\sigma + |x|}\f$.
	/// This structure can be passed as the second template argument in IRLS.
	///////////////////////////////////////////////////////////////
	struct RobustI {
		double sd_inlier; ///< The inlier standard deviation, \f$\sigma\f$.
		inline double reweight(double x) {return 1/(sd_inlier+fabs(x));}  ///< Returns \f$w(x)\f$.
		inline double trueScale(double x) {return reweight(x) - fabs(x)*reweight(x)*reweight(x);}  ///< Returns \f$w(x) + xw'(x)\f$.
		inline double objective(double x) {return fabs(x) + sd_inlier*log(sd_inlier*reweight(x));}  ///< Returns \f$\int xw(x)dx\f$.
	};
	///////////////////////////////////////////////////////////////
	/// Robust reweighting (type II) for IRLS.
	/// A reweighting class with \f$w(x)=\frac{1}{\sigma + x^2}\f$.
	/// This structure can be passed as the second template argument in IRLS.
	///////////////////////////////////////////////////////////////
	struct RobustII {
		double sd_inlier; ///< The inlier standard deviation, \f$\sigma\f$.
		inline double reweight(double d){return 1/(sd_inlier+d*d);} ///< Returns \f$w(x)\f$.
		inline double trueScale(double d){return d - 2*d*reweight(d);} ///< Returns \f$w(x) + xw'(x)\f$.
		inline double objective(double d){return 0.5 * log(1 + d*d/sd_inlier);} ///< Returns \f$\int xw(x)dx\f$.
	};
	///////////////////////////////////////////////////////////////
	/// A reweighting class representing no reweighting in IRLS.
	/// \f$w(x)=1\f$
	/// This structure can be passed as the second template argument in IRLS.
	///////////////////////////////////////////////////////////////
	struct ILinear {
		inline double reweight(double d){return 1;} ///< Returns \f$w(x)\f$.
		inline double trueScale(double d){return 1;} ///< Returns \f$w(x) + xw'(x)\f$.
		inline double objective(double d){return d*d;} ///< Returns \f$\int xw(x)dx\f$.
	};
	///////////////////////////////////////////////////////////////
	/// Performs iterative reweighted least squares.
	/// @param Size the size
	/// @param Reweight The reweighting functor. This structure must provide reweight(), 
	/// true-scale() and objective() methods. Existing examples are  Robust I, Robust II and ILinear.
	///////////////////////////////////////////////////////////////
	template < class Reweight >
	class Irls: public Reweight
	{
	public:
		//Constructor
		Irls(){}
		//Destructor
		~Irls(){cvReleaseMat(&cvWeightedMatrix_); 
		delete [] outlierLog;}
		//weighted matrix update function
		inline bool update(double* residuals){int outlierLevel=0; 
							double weight;
							scale = madCompute(residuals);
							for(int i=0; i<Size_; i++){
								weight = reweight(trueScale(residuals[i]), &outlierLog[i]);
								if(weight==0)
									outlierLevel++;
								SETCVd_(cvWeightedMatrix_, weight, i+1, i+1);} 
							printf("Outliers %d point pairs \n", outlierLevel/2);
							return (outlierLevel<(Size_/2))?true:false;}
		//weighted matrix update function
		inline bool updateStereo(double* residuals){int outlierLevel=0; 
							double weight1;
							double weight2;
							scale = madCompute(residuals);
							for(int i=0; i<Size_; i=i+2){
								weight1 = reweight(trueScale(residuals[i]), &outlierLog[i]);
								weight2 = reweight(trueScale(residuals[i+1]), &outlierLog[i+1]);
								if((weight1==0)||(weight2==0)){
									outlierLevel=outlierLevel+2;
									if(weight1==0)
										outlierLog[i+1]=true;
									else
										outlierLog[i]=true;
									SETCVd_(cvWeightedMatrix_, 0, i+1, i+1);
									SETCVd_(cvWeightedMatrix_, 0, i+2, i+2);
								}
								SETCVd_(cvWeightedMatrix_, weight1, i+1, i+1);
								SETCVd_(cvWeightedMatrix_, weight2, i+2, i+2);
							}
							printf("Outliers %d point pairs \n", outlierLevel/2);
							return (outlierLevel<(Size_/2))?true:false;
		}
		//irls object initialization function 
		void   irlsInit(int Size, double mySdInlier){
			Size_ = Size;  
			cvWeightedMatrix_ = cvCreateMat(Size_, Size_, CV_64F);
			cvSetIdentity(cvWeightedMatrix_); 
			myResidual_=0;
			sdInlier = mySdInlier;
			outlierLog = new bool[Size_];
			fill_n(outlierLog, Size_, false);}

		//weighted matrix access function
		CvMat* getWeightedMatrix(){return cvWeightedMatrix_;}
		bool*  getOutlierLog(){return outlierLog;}

	private:
		int Size_;								//number of observations
		double myResidual_;				//normalized residuals (MAD normalization)
		CvMat* cvWeightedMatrix_; //weighted matrix 
		bool*  outlierLog;        //state of irls elements (outlier/inlier)

		Irls( Irls& copyof);
		int operator = ( Irls& copyof );
		//Median Absolute Deviation (MAD) computation function
		inline double madCompute(double *x) {
			double* tmpResidual = new double[Size_];
			double myMedian = median(x);
			for(int i=0; i<Size_; i++)
				tmpResidual[i] = fabs( x[i] - myMedian );
			double sigma = 1.48 * median(tmpResidual);
			delete[] tmpResidual;
			return sigma;}
		//Median function
		inline double median(double* x) {
			double* myX = new double[Size_]; 
			memcpy(myX, x, Size_*sizeof(double));
			quickSort(myX, 0, Size_-1); // recursive function!
			double ans = myX[int((Size_/2)-1)];
			delete[] myX;
			return ans;}
	};
}
#endif