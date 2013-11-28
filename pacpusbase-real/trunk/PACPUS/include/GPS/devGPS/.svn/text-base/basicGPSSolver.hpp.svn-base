#ifndef _basicGPSSolver_H
#define _basicGPSSolver_H


#undef min  
#undef max 
#include "DataStructures.hpp"
#include "Position.hpp"
#include "Vector.hpp"
#include "SolverWMS.hpp"
#include "iteratedSolver.hpp"



/*! \class basicGPSSolver
 *	\brief Simple GPS Solver with Weighted Mean Square
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date July 2008
 *	\bug None
 *	\warning None
 *
 */


class basicGPSSolver : public iteratedSolver
{
public: 

	enum solverType
	{
		basic,
		MOPS
	};

	
	/*! \brief Constructor. Intitialise the member variables with default values, i.e 10 maximum
	 *  iterations and a convergence threshold of 1e-4*/
	basicGPSSolver(gpstk::Vector<double> initialSolution, solverType type = basic) /*throw (gpstk::InvalidSolver)*/;

	/*! \brief Constructor. Intitialise the member variables with provided values*/
	basicGPSSolver(gpstk::Vector<double> initialSolution, int nbItMax, double convergenceThd, solverType type = basic) /*throw (gpstk::InvalidSolver)*/;
	
	/*! \brief Destructor, destroy the one step solver used*/
	~basicGPSSolver();

	/*! \brief Set the initial position. An exception is sent if the size of the solution does not match
	 *  the equation definition*/
	void setInitialPosition(gpstk::Vector<double> initialSolution) /*throw (gpstk::InvalidSolver)*/;

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/
	std::string getClassName(void) const;

	/*! \brief Provide the current solution*/
	virtual gpstk::Vector<double> getSolution();

	/*! \brief The solver has ended if the convervenge threshold is reached, if the maximum
	 *  number of iteration is reached or if the solution moves too far away from the initial solution*/
	virtual inline bool isEnded()
	{
		double conv = gpstk::RMS(pOneStepSolver->solution);
		bool tooFar = isTooFar();
		return ((conv<convergenceThd) || (curIt>=nbItMax) || (tooFar));
	};

	/*! \brief The solver is successfull if the convervenge threshold is reached within the maximum number of 
	 *   and a defined distance*/
	virtual inline bool isSuccessful()
	{
		return ((gpstk::RMS(pOneStepSolver->solution)<convergenceThd) && (curIt<nbItMax) && (!isTooFar()));
	};

	/*! \brief The solution is too far if it is moved away from the the inital solution with a distance
	 *  higher to the distance threshold*/
	inline bool isTooFar()
	{
		gpstk::Vector<double> initDist(4);
		initDist = curSolution - initialSolution;
		double dist = gpstk::RSS(initDist[0], initDist[1], initDist[2]);
		if (dist>distThd)
			return true;
		else
			return false;
	};

	//virtual gpstk::satTypeValueMap & endStep(gpstk::satTypeValueMap& gData);


protected:

	/*! \brief currrent solver type*/
	solverType curSolverType;
	
	/*! \brief Start solution of the solver*/
	gpstk::Vector<double> initialSolution;

	/*! \brief Current solution of the solver*/
	gpstk::Vector<double>  curSolution;

	/*! \brief Size of the solution vector as defined by the equation definition of the one step solver*/
	int solutionSize;

	/*! \brief Refer to the gpstk::ProcessingClass class*/
    static int classIndex;

	/*! \brief Distance Threshold*/
	int distThd;

	/*! \brief Allows initializing the herited iteratedSolver member variable and to check
	 *  the size of the initial solution with respect to the equation definition*/
	void initiateAndVerify(gpstk::Vector<double> initialSolution, int nbItMax, double convergenceThd) /*throw (gpstk::InvalidSolver)*/;

	/*! \brief Computation to perform between to steps of the one step solver*/
	gpstk::satTypeValueMap & recomputeForNextStep(gpstk::satTypeValueMap & gData);

};

#endif