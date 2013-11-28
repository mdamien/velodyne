#ifndef _basicDopplerSolver_H
#define _basicDopplerSolver_H


#undef min  
#undef max 
#include "DataStructures.hpp"
#include "Position.hpp"
#include "Vector.hpp"
#include "SolverLMS.hpp"
#include"iteratedSolver.hpp"
#include"basicGPSSolver.hpp"
#include "ModelObsExt.hpp"



/*! \class basicDopplerSolver
 *	\brief GPS Solver with Boppler using Weighted Mean Square
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date July 2008
 *	\bug None
 *	\warning None
 *
 */

class basicDopplerSolver : public basicGPSSolver
{
public: 

	/*! \brief Constructor. Intitialise the member variables*/
	basicDopplerSolver(gpstk::Vector<double> initialSolution, solverType type = basic) /*throw (gpstk::InvalidSolver)*/;

	basicDopplerSolver(gpstk::Vector<double> initialSolution, int nbItMax, double convergenceThd, solverType type = basic) /*throw (gpstk::InvalidSolver)*/;
	
	gpstk::satTypeValueMap& Process(gpstk::satTypeValueMap& gData);

	std::string getClassName(void) const;

	/*! \brief Provide the current solution*/
	virtual gpstk::Vector<double> getDopplerSolution();

protected:

	/// Initial index assigned to this class.
    static int classIndex;

	/*! \brief distance threshold which implies to recompute the satellites position*/
	static const int distThd = 200;

	/*! \brief Least Square solver use to estimate the speed of the receiver*/
	gpstk::SolverLMS dopplerOneStepSolver;

	/*! \brief contains the speed of the receiver and the receiver clock drift*/
	gpstk::Vector<double> dopplerSolution;

	/* \brief Defines the coefficients which fullfill the observation matrix used for the doppler*/
	virtual gpstk::satTypeValueMap& computeDopplerCoeff(gpstk::satTypeValueMap& gData);

	void init();

};

#endif