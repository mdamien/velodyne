#ifndef _RAIMSolver_H
#define _RAIMSolver_H


#include "basicGPSSolver.hpp"
#include "chisquaredistr.h"

#define MAX_NB_SV 16



/*! \class RAIMSolver
 *	\brief GPS Solver with RAIM
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date Mar 2009
 *	\bug None
 *	\warning None
 *
 */


class RAIMSolver : public basicGPSSolver
{
public: 
	
	/*! \brief Constructor. Intitialise the member variables with default values, i.e 10 maximum
	 *  iterations and a convergence threshold of 1e-4*/
	RAIMSolver(gpstk::Vector<double> initialSolution, double pfa, solverType type = basic) throw (gpstk::InvalidSolver);

	/*! \brief Constructor. Intitialise the member variables with provided values*/
	RAIMSolver(gpstk::Vector<double> initialSolution, int nbItMax, double convergenceThd, double pfa, solverType type = basic) throw (gpstk::InvalidSolver);
	
	/*! \brief Destructor, destroy the one step solver used*/
	~RAIMSolver();

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/ 
	virtual gpstk::satTypeValueMap& Process(gpstk::satTypeValueMap& gData);

	/*! \brief Virtual function, refer to the gpstk::ProcessingClass class*/
	std::string getClassName(void) const;

	inline bool isValid() const
		{return valid;};

protected:

	/*! \brief Refer to the gpstk::ProcessingClass class*/
    static int classIndex;

	/*! \brief Allows initializing the herited iteratedSolver member variable and to check
	 *  the size of the initial solution with respect to the equation definition*/
	void initiateAndVerify(gpstk::Vector<double> initialSolution, int nbItMax, double convergenceThd) throw (gpstk::InvalidSolver);

	double chi2Thd[MAX_NB_SV];

	double sigmaC1;

	bool valid;

};

#endif