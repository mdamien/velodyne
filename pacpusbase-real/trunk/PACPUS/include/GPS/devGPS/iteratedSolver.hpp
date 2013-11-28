#ifndef _iteratedSolver_H
#define _iteratedSolver_H

#undef min  
#undef max 
#include "DataStructures.hpp"
#include "TypeID.hpp"
#include "Vector.hpp"
#include "ProcessingClass.hpp"
#include "SolverLMS.hpp"

/*! \class iteratedSolver
 *	\brief Allows iterating the computation of a one step solver
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date July 2008
 *	\bug None
 *	\warning None
 *
 */

class iteratedSolver : public gpstk::ProcessingClass
{
public: 

	/*! \brief Constructor. Intitialise the member variables*/
	iteratedSolver(gpstk::SolverLMS *pOneStepSolver);

	
	//iteratedSolver(gpstk::SolverLMS *pOneStepSolver, int nbItMax = 1, double convergenceThd = 1);


	/*! \brief Return the maximum number of iterations allowed*/
	inline int getNbItMax()
	{
		return nbItMax;
	};

	/*! \brief Return the threshold from which the solver is considered to have converged*/
	inline double getConvergenceThd()
	{
		return convergenceThd;
	};

	
	/*! \brief The solver is considered to have ended when either the convergence threshold 
	 *  or the maximum iteration number has been reached*/
	virtual inline bool isEnded()
	{
		return ((gpstk::RMS(pOneStepSolver->solution)<convergenceThd) || (curIt>=nbItMax));
	};

	
	/*! \brief The solver is considered successfull when the convergence threshold has been reached within the
	 *  maximum number of iteration*/
	virtual inline bool isSuccesful()
	{
		return ((gpstk::RMS(pOneStepSolver->solution)<convergenceThd) && (curIt<nbItMax));
	};

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/ 
	virtual gpstk::satTypeValueMap& Process(gpstk::satTypeValueMap& gData);

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/ 
	gpstk::gnssSatTypeValue& Process(gpstk::gnssSatTypeValue& gData)
		/*throw(gpstk::InvalidSolver)*/
	{ 
		Process(gData.body); return gData; 
	};

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/
	gpstk::gnssRinex& Process(gpstk::gnssRinex& gData) /*throw(gpstk::InvalidSolver)*/
	{ 
		Process(gData.body); return gData; 
	};

	/*! \brief Return the Equation Definition defined in the one step solver used by the class*/
	gpstk::gnssEquationDefinition getDefaultEqDefinition() const
	{ 
		return pOneStepSolver->getDefaultEqDefinition(); 
	};

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/
	std::string getClassName(void) const = 0;

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/
	int getIndex() const { return (*this).index; };

	virtual gpstk::satTypeValueMap & endStep(gpstk::satTypeValueMap& gData)
		{return gData;};


protected:

	/*! \brief Constructor for an herited class which wouldn't define the solver during the call
	 *   of the parent constructor*/
	iteratedSolver();

	/*! \brief Current Iteration. Contains the number of iterations already performed.
	 *   Is initialized to 0*/
	int curIt;

	/*! \brief Allows changing the convergence Threshold*/
	void setConvergenceThd(double convergenceThd);

	
	/*! \brief Allows changing the maximum number of iterations*/
	void setNbItMax(int nbItMax);

	/*! \brief Maximum Number of Iterations before the solver stops*/
	int nbItMax;

	/* \brief Convergence Threshold compared to the difference between two consecutive states*/
	double convergenceThd;

	/*! \brief Pointer to the one step solver which is iterated*/
	gpstk::SolverLMS *pOneStepSolver;
	
	/*! \brief virtual function which permit to modify and recompute data between two steps*/
	virtual gpstk::satTypeValueMap& recomputeForNextStep(gpstk::satTypeValueMap& gData) = 0;

private :

	/*! \brief Refer to the gpstk::ProcessingClass class*/
    static int classIndex;

	/*! \brief Refer to the gpstk::ProcessingClass class*/
	int index;
	
	/*! \brief Refer to the gpstk::ProcessingClass class*/
    void setIndex(void) { (*this).index = classIndex++; }; 
};

#endif