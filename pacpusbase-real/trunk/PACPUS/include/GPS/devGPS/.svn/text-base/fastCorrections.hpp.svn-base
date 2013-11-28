#ifndef _fastCorrections_H
#define _fastCorrections_H

#include "PRNMask.hpp"
#include "structure/structureSBAS.h"
#include "DayTime.hpp"
#include "DataStructures.hpp"
#include "TypeID.hpp"
#include <map>

namespace Ui
{
	class uiFastCorrections;
}

namespace SBAS
{

	/*! \class fastCorrData
	 *	\brief Contains the data necessary to compute the fast correction for one satellite */
	/*! For each satellites the IODF, the UDRE, its variance, the degradation factor are stored
	  as well as all the PRCorrections received which can be used to compute the RRC*/
	class fastCorrData
	{

	public:

		/*!\brief Defines a type equivalent to a map which contain all the fast correction data with their respective time 
		of reception*/
		typedef std::map<gpstk::DayTime,double> PRCorrTimeMap;

		typedef std::pair<gpstk::DayTime,double> PRCorrTimePair;

		/*!\brief Issue Of Data of the current Fast Corrections */
		unsigned char IODF;

		/*!\brief Defines if the Pseudorange fast corrections are available or not*/
		bool PRcorrAvailable;

		/*!\brief Defines if the degradation factor of the fast corrections are available or not*/
		bool degradationFactorsAvailable;

		/*!\brief last Pseudorange corrections (m)*/
		double lastPRCorrection;

		/*!\brief Time of reception of the last Pseudorange corrections*/
		gpstk::DayTime lastPRcorrReceptionTime;

		/*!\brief Map of the PRC corrections with their time of reception*/
		PRCorrTimeMap PRCorrTime;

		/*!\brief Computed Range Rate corrections (m/s)*/
		double RRC;

		/*!\brief delta time used to compute the RRC (s)*/
		double dtRRC;

		/*!\brief User Differential Range Estimate*/
		double UDRE;

		/*!\brief Variance of the User Differential Range Estimate*/
		double sigma2UDRE;

		/*!\brief Defines if the satellite is monitored or not*/
		bool notMonitored;

		/*!\brief Defines if the satellite is considered as unhealthy or not*/
		bool doNotUse;

		/*!\brief UDRE degradation factor*/
		double a;

		/*!\brief Time-out for Non Precision Approach*/
		int ToNPA;

		/*!\brief Time-out for Precision Approach*/
		int ToPA;

		unsigned int maxUpdateInterval;

		/*!\brief Constructor*/
		fastCorrData();
	};


	/*! \class fastCorrections
	 *	\brief Contains the data necessary to compute the fast correction for one satellite */
	class fastCorrections
	{
		friend class Ui::uiFastCorrections;

	public:
		
		/*!\brief Defines a type equivalent to a map which contains the fast correction for each satellite*/
		typedef std::map<gpstk::SatID,fastCorrData> fastCorrSatMap;

		typedef std::pair<gpstk::SatID,fastCorrData> fastCorrSatPair;

		/*!\brief Array which makes the correspondance between the UDRE Indicator and the corresponding variance*/
		static const double sigma2UDRE[14];

		/*!\brief Array which makes the correspondance between the degradation factor and the Time-Out in the case 
		of Non Precision Approach*/
		static const int ToNPA[16];

		/*!\brief Array which makes the correspondance between the degradation factor and the Time-Out in the case 
		of Precision Approach*/
		static const int ToPA[16];
		
		//! save if MT0 messages can be considered as MT2 messages or not
		bool MT0included;

		/*!\brief Initialize the static gpstk:TypeID variables*/
		void iniateTypeID();

		/*!\brief Constructor*/
		fastCorrections(bool MT0enabled = false);
		
		/*!\brief Save a pointer to the current PRNMask and the current IODP*/
		void setPRNMask(SBAS::PRNMask *pMask)
			{pRelatedMask = pMask;
			if(pRelatedMask!=NULL)
				currentIODP = pRelatedMask->getIODP();};

		/*! \brief Add data from a MT2, MT3, MT4 or MT5 message, which contain PR corrections
		and integrity information. Can be used for MT24 too*/
		/*!\param data constant pointer to a Fast correction message structure
		  \param start_Read_Pos the position at which we have to start reading the buffer
		  \param MTNumber message type (2, 3, 4 or 5)
		  \param ToR Times of reception of the message
		  \return an integer, equal to 1 if the data are correct 0 otherwise
		*/ 
		int addMT2to5(const SBAS::structFastCorrections* data, unsigned char MTNumber, gpstk::DayTime ToR, bool MT24=false);

		/*! \brief Add data from a MT6 message, which contains the integrity information*/
		/*!\param data constant pointer to a Fast correction message structure
		  \param start_Read_Pos the position at which we have to start reading the buffer
		  \param ToR Times of reception of the message
		  \return an integer, equal to 1 if the data are correct 0 otherwise
		*/ 
		int addMT6(const SBAS::structIntegrityInformation* data, gpstk::DayTime ToR);

		/*! \brief Add data from a MT7 message*/
		/*!\param data constant pointer to a Fast correction message structure
		  \param start_Read_Pos the position at which we have to start reading the buffer
		  \param ToR Times of reception of the message
		  \return an integer, equal to 1 if the data are correct 0 otherwise
		*/ 
		//int addMT7(const SBAS::structIntegrityInformation* data, gpstk::DayTime ToR);

		/*! \brief Add data from a MT6 message*/
		/*!\param data constant pointer to a Fast correction message structure
		  \param start_Read_Pos the position at which we have to start reading the buffer
		  \param ToR Times of reception of the message
		  \return an integer, equal to 1 if the data are correct 0 otherwise
		*/ 
		int addMT24(const SBAS::structMixedFastCorrectionLongTermError* data, gpstk::DayTime ToR);

		/*! \brief Compute the fast correction for a satellite at the desired time*/
		/*!\param data Pointer to the typeValueMap of this satellite, where the computed corrections will be addded
		  \param sat Satellite identifier
		  \param time Time at which the fast correction has to be computed
		  \return return the PRC correction
		*/ 
		double getCorrection(gpstk::typeValueMap *data, gpstk::SatID sat, gpstk::DayTime time);

		/*! \brief Remove the unhealthy satellites from the given gnssSatTypeValue map*/
		/*!\param gData gnssSatTypeValue map to check
		  \return resulting gnssSatTypeValue map
		*/ 
		inline gpstk::gnssSatTypeValue& removeNoIntegritySVs(gpstk::gnssSatTypeValue& gData)
			{return gData.removeSatID(noIntegritySVs);};

		/*! \brief Remove the unmonitored satellites from the given gnssSatTypeValue map*/
		/*!\param gData gnssSatTypeValue map to check
		  \return resulting gnssSatTypeValue map
		*/ 
		inline gpstk::gnssSatTypeValue& removeNotMonitoredSVs(gpstk::gnssSatTypeValue& gData)
			{return gData.removeSatID(notMonitoredSVs);};

		/*! \brief Reset the corrections variable and the gpstk::SatIDSet */ 
		void PRNMaskHasChanged();

		/*! \brief New TypeID to add Pseudorange corrections into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSPRCorrection;

		/*! \brief New TypeID to add User Differential Tange Error variances into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSigma2UDRE;

		/*! \brief New TypeID to notify a satellite is unhealty into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSNoIntegrityFlag;

		//const fastCorrSatMap getCorrectionsMap(){return corrections;};


	protected:


		/*!\brief Time out interval for Non Precision Approach*/
		static gpstk::DayTime timeOutIntervalNPA; 

		/*!\brief Time out interval for Precision Approach*/
		static gpstk::DayTime timeOutIntervalPA; 

		/*!\brief Pointer to the PRNMask which gives the relation between satellite mask and the satellite id*/
		SBAS::PRNMask* pRelatedMask;

		/*!\brief Issue Of Data of the current PRNMask*/
		short currentIODP;

		/*!\brief map which contain all the received fast correction data for each satellite*/
		fastCorrSatMap corrections;

		//unsigned char curIODF[6];

		/*!\brief List of the unmonitored satellites*/
		gpstk::SatIDSet notMonitoredSVs;

		/*!\brief List of the unhealthy satellites*/
		gpstk::SatIDSet noIntegritySVs;

		/*!\brief Check if the IODP of the current PRN mask has changed or not*/
		inline bool maskChanged()
			{return currentIODP!=pRelatedMask->getIODP();};

		
		/*!\brief Fullfill the corrections regarding to the UDRE Indicator and manage the list of 
			unmonitored and unhealthy satellites*/
		/*!\param corrValues pointer to the structure to fullfill
		  \param UDREI User Differential Range Estimate Indicator
		  \param sat constant reference to the satellite
		*/ 
		void fillUDRE(fastCorrData *corrValues,unsigned short UDREI, const gpstk::SatID& sat);

		void fillPartOfMT6(const SBAS::structIntegrityInformation* data, unsigned char IODFNb, gpstk::DayTime &ToR);
		

	};

}
#endif
