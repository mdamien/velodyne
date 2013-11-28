#ifndef _SBASCorrectedEphemerisRange_H
#define _SBASCorrectedEphemerisRange_H

#include "EphemerisRange.hpp"
#include "GPSEphemerisStore.hpp"
#include "GPSGeoid.hpp"
#include "MiscMath.hpp"
#include "TypeID.hpp"

#include "structureSBAS.h"
#include "PRNMask.hpp"

namespace Ui
{
	class uiLongTermCorrections;
}

namespace SBAS
{


	struct structLongTermCorr
	{
	/* !\brief Set if velocity corrections are available or not*/
	bool velocityPresent;

	/* !\brief Issue of Data Ephemeris. Has to be compared to GPS broadcated ones*/
	unsigned char IODE;

	/* !\brief Issue of Data PRN Mask*/
	unsigned char IODP;

	/* !\brief Satellite Mask*/
	int satMask;

	/* !\brief Error on the satellite position along the X axis in the ECEF referential (m)*/
	double deltaXECEF;

	/* !\brief Error on the satellite position along the Y axis in the ECEF referential (m)*/
	double deltaYECEF;

	/* !\brief Error on the satellite position along the Z axis in the ECEF referential (m)*/
	double deltaZECEF;

	/* !\brief Error on the satellite velocity along the X axis in the ECEF referential (m/s)*/
	double deltaXROC;

	/* !\brief Error on the satellite velocity along the Y axis in the ECEF referential (m/s)*/
	double deltaYROC;

	/* !\brief Error on the satellite velocity along the Z axis in the ECEF referential (m/s)*/
	double deltaZROC;

	/* !\brief Error on the satellite clock bias (s)*/
	double deltaAf0;

	/* !\brief Error on the satellite clock drift (s/s)*/
	double deltaAf1;

	/* !\brief Time of Applicability of the correction*/
	gpstk::DayTime t0;
	};

	/*! \class SBASCorrectedEphemerisRange
	 *	\brief */
	/*! */
	class SBASCorrectedEphemerisRange : public gpstk::CorrectedEphemerisRange
	{
		friend class Ui::uiLongTermCorrections;

	public:
		
		typedef std::pair<gpstk::SatID,structLongTermCorr> satLongTermCorrPair;

		/*! \brief Store Long Term Corrections for each satellite*/
		typedef std::map<gpstk::SatID,structLongTermCorr> satLongTermCorrMap;

		void iniateTypeID();

		/*! \brief Constructor, initialise the member variables and the stl::map longTermCorr as empty*/
		SBASCorrectedEphemerisRange(gpstk::XvtStore<gpstk::SatID> *pXvtS);

		/*! \brief Constructor, initialise the member variables and the stl::map longTermCorr as empty*/
		SBASCorrectedEphemerisRange(gpstk::GPSEphemerisStore *pEph);

		/*! \brief Add long term corrections*/
		int addMT24(const SBAS::structMixedFastCorrectionLongTermError* data);

		/*! \brief Add long term corrections*/
		int addMT25(const SBAS::structLongTermSatelliteErrorCorrections* data);

		/*! \brief Makes all the satellite position computation, including SBAS corrections*/
		double 	ComputeAtTransmitTime (const gpstk::DayTime &tr_nom, const double &pr, const gpstk::Position &Rx, const gpstk::SatID sat, bool applySBASCorr = false);

		inline void setCurTime(gpstk::DayTime time)
			{curTime = time;};
		
		/*!\brief Save a pointer to the current PRNMask and the current IODP*/
		void setPRNMask(SBAS::PRNMask *pMask)
			{pRelatedMask = pMask;
			if(pRelatedMask!=NULL)
				currentIODP = pRelatedMask->getIODP();};

		/*! \brief Reset the longTermCorr variable*/ 
		void PRNMaskHasChanged();

		/*! \brief Return the value of the corrAppliedOnLastRq variable*/ 
		bool getCorrAppliedOnLastRq() const
		{
			return corrAppliedOnLastRq;
		};

		const gpstk::Xvt &getLastCorrection()
			{return svPosVelCorr;};

		/*! \brief New TypeID to store set if slow corrections have been applyed or not into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSlowCorrAvailble;
		
		/*! \brief New TypeID to store satellite position correction along the X axis, into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSlowCorrX;
		
		/*! \brief New TypeID to store satellite position correction along the Y axis, into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSlowCorrY;
		
		/*! \brief New TypeID to store satellite position correction along the Z axis, into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSlowCorrZ;
		
		/*! \brief New TypeID to store satellite clock correction along the X axis, into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSlowCorrClock;

	protected:

		/* !\brief Store the current Long Term Coirrections parameters for each satellite*/
		/* ! Normally it should be possible to store few Long Term Coirrections parameters for one
		 *   satellite because you can receive corrections whose time of applicability is in the future.
		 *   But I consider that the time of applicability is the time of reception, so it's eaiser*/
		satLongTermCorrMap longTermCorr;

		gpstk::GPSEphemerisStore *pEphStore;

		/* !\brief Set if a correct Ephemeris pointer is available or not*/
		bool EphAvailable;

		/* !\brief Current Time, used to check if long term corrections messages have to be used or not*/
		gpstk::DayTime curTime;

		/*!\brief Pointer to the PRNMask which gives the relation between satellite mask and the satellite id*/
		SBAS::PRNMask* pRelatedMask;

		/*!\brief Issue Of Data of the current PRNMask*/
		short currentIODP;

		void addLongTermCorrection(const structLongTermCorr &LTC);

		/* ! \brief Time out interval for Non Precision Approach (s)*/
		static const double ToNPA;

		/* ! \brief Time out interval for Precision Approach (s)*/
		static const double ToPA;
		
		/* ! \brief Contains the last corrections computed by the ComputeAtTransmitTime function*/
		gpstk::Xvt svPosVelCorr;

		/* ! \brief Store if SBAS correction have been applied on the last call of ComputeAtTransmitTime function*/
		bool corrAppliedOnLastRq;

	};

}
#endif