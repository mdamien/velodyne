#ifndef _tropoCorrections_H
#define _tropoCorrections_H

#include "PRNMask.hpp"
#include "structure/structureSBAS.h"
#include "DayTime.hpp"
#include "DataStructures.hpp"
#include "Position.hpp"
#include "TypeID.hpp"
#include <map>

namespace Ui
{
	class uiTropoCorrections;
}

namespace SBAS
{

	

	/*! \class tropoCorrections
	 *	\brief Contains the data necessary to compute the tropo correction for one satellite */
	class tropoCorrections
	{
		friend class Ui::uiTropoCorrections;

	public:

		/*!\brief Array which makes the correspondance between the latitude and the pressure (mbar)*/
		static const double lat2Pressure[5][2];

		/*!\brief Array which makes the correspondance between the latitude and the temperature (K)*/
		static const double lat2Temperature[5][2];

		/*!\brief Array which makes the correspondance between the latitude and the Water Vapour Pressure (mbar)*/
		static const double lat2WVP[5][2];

		/*!\brief Array which makes the correspondance between the latitude and the Temperature Lapse Rate (K/m)*/
		static const double lat2TLR[5][2];

		/*!\brief Array which makes the correspondance between the latitude and the Water Vapour Lapse Rate (-)*/
		static const double lat2WVLR[5][2];

		/*!\brief Constant (k/mbar)*/
		static const double k1;

		/*!\brief Constant (k^2/mbar)*/
		static const double k2;

		/*!\brief Constant (J/Kg.K)*/
		static const double Rd;

		/*!\brief Constant (m/s^2)*/
		static const double gm;

		/*!\brief Constant (m/s^2)*/
		static const double g;

		/*!\brief Initialize the static gpstk:TypeID variables*/
		void iniateTypeID();

		static gpstk::TypeID EGNOSSlantTropo;

		static gpstk::TypeID EGNOSSigma2Tropo;

		/*!\brief Constructor*/
		tropoCorrections();

		/*! \brief Compute the tropo correction for a satellite at the desired time*/
		/*! \param RcvPos Position of the receiver
		    \param svel elevation of the satellite in degrees
		    \param time Time at which the tropo correction has to be computed
		    \return return the tropospheric correction in meters
		*/ 
		double getCorrection(gpstk::Position RcvPos, double svel, gpstk::DayTime time);

		


	protected:

	};

}
#endif
