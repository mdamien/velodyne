#ifndef _GPSTK_Nav_H
#define _GPSTK_Nav_H

#include "structure/structureUBX.h"
#include "structure/structure_septentrio.h"
#include "GPSTK_Obs.hpp"

#undef min  
#undef max 
#include "DataStructures.hpp"
#include "SourceID.hpp"
#include "DayTime.hpp"
#include "SatID.hpp"
#include "TypeID.hpp"
#include "GPSEphemerisStore.hpp"
#include "GPSAlmanacStore.hpp"
#include "IonoModelStore.hpp"
#include "IonoModel.hpp"
#include "TropModel.hpp"
#include "ModelObsExt.hpp"
#include "SimpleFilter.hpp"
#include "RinexNavStream.hpp"
#include "RinexNavData.hpp"
#include "RinexNavData.hpp"
#include "RinexUtilities.hpp"

#include "EphemerisRange.hpp"
#include"iteratedSolver.hpp"
#include "Position.hpp"
#include "ComputeMOPSWeights.hpp"



/*! \class GPSTK_Nav
 *	\brief Store the GPS navigation data coming from a Ublox Receiver in the gpstk framework
 *	\author Olivier LE MARCHAND
 *	\version 1.0
 *	\date February 2008
 *	\bug None
 *	\warning None
 *
 */


class GPSTK_Nav
{
public: 

	
	//! Current GPS Week
	long gpsWeek;

	/*! \brief transmit the informationText variable to be printed and clear it*/
	/*! \param computeMOPS Defines if MOPS weight have to be computed for a SolverWMS*/
	std::string getInformationText();


	/*! \brief Constructor. Intitialise the member variables*/
	GPSTK_Nav(bool useMopsTM = true, bool computeMOPS = false);

	/*! \brief Constructor. Intitialise the member variables and extract information from a RINEX Navigation file*/
	/*! Member variables are initialized at the same values as in the default Constructor\n
	 *  Then it tries to open the RINEX files whose path is given in parameter. If ionospheric parameter are in, 
	 *  they are extracted and added to the ionoStore variables. Hence epehemeris are extracted, and added to the 
	 *  ephStore variable
	 * \param useMopsTM Defines if tropospheric corrections from MOPS have to be used
	 * \param computeMOPS Defines if MOPS weight have to be computed for a SolverWMS*/
	GPSTK_Nav(std::string Eph_FilePath, bool useMopsTM = true, bool computeMOPS = false);

	//Gestion des RINEX directement par cette classe

	/*! \brief Add the GPS broadcasted navigation data in our Navigation Observation Model */
	/*! 10 DWORDs of the GPS broadcasted data are sent by the Ublox receiver through a 
	 * RXM-SFRB message. Information contained in this message is stored in appropriate
	 * structure. If a complete Ephemeris, Almanac or Ionospheric model is obtained, it is 
	 * decoded and automatically added in the observation Model  */
	bool addRXM_SFRB(const Ublox::structRXM_SFRB &inputData, gpstk::DayTime DT[4])throw();

	/*! \brief Add the GPS broadcasted navigation data in our Navigation Observation Model */
	/*! 10 DWORDs of the GPS broadcasted data are sent by the PolarX receiver through a 
	 * SbfDataGPSRaw message. Information contained in this message is stored in appropriate
	 * structure. If a complete Ephemeris, Almanac or Ionospheric model is obtained, it is 
	 * decoded and automatically added in the observation Model  */
	bool addGPSRaw(const SbfDataGPSRaw &inputData, gpstk::DayTime DT[4])throw();

	/*! \brief Set the elevation threholsd used for satellite filtering */
	void setElevationThd(int elevThd);

	/*! \brief Set the CNO threholsd used for satellite signal filtering */
	void setCNOThd(int CNOThd);

	bool addFromRinexFile(std::string Eph_FilePath);


	/*! \brief Extract the Sub Frame ID from the HOW word with no parity*/
	static unsigned char extractSFIDNoParity(const long *DWRD);

	/*! \brief Extract the Sub Frame ID from the HOW word*/
	static unsigned char extractSFID(const long *DWRD);
	
	/*! \brief Extract the SV ID from the 3rd word with no parity*/
	static unsigned char extractSVIDNoParity(const long *DWRD);

	/*! \brief Extract the SV ID from the 3rd word*/
	static unsigned char extractSVID(const long *DWRD);
	
	/*! \brief Extract the Time Of Week from the HOW word with no parity*/
	static unsigned short extractTOWNoParity(const long *DWRD);

	/*! \brief Extract the Time Of Week from the HOW word*/
	static unsigned short extractTOW(const long *DWRD);

	inline gpstk::Position getRxPos()
	{
		return pObsModel->rxPos;
    }

	
	SBAS::ionoCorrections *getSBASIonoModel() const
	{
		return &pObsModel->SBASIonoModel;
    }

	SBAS::SBASCorrectedEphemerisRange * getSBASLongTermCorrections() const
	{
		return &pObsModel->SBAScerange;
    }
	
	SBAS::PRNMask *getSBASprnMask() const
	{
		return &pObsModel->SBASprnMask;
    }

	
	SBAS::fastCorrections *getSBASfastCorrections() const
	{
		return &pObsModel->SBASfastCorr;
    }

	inline int getElevThd()
	{
		return (int)(*this).pObsModel->getMinElev();
	}

	inline int getCNOThd()
	{
		return CNOThd;
	}

	inline const gpstk::GPSEphemerisStore & getEphStore()
	{
		return ephStore;
	}

	inline int estimateFirstPosition(GPSTK_Obs& obsData)
	{
		/*int i; // for debug purpose
		std::vector<SatID> vSat;
        std::vector<double> vPR;
        Vector<SatID> Satellite( obsData.measures.body.getVectorOfSatID() );
        Vector<double> Pseudorange( obsData.measures.body.getVectorOfTypeID( (*pObsModel).getDefaultObservable() ) );

        // Convert from gpstk::Vector to std::vector
        for (i = 0; i < (int)Satellite.size(); i++)
            vSat.push_back(Satellite[i]);

        for (i = 0; i < (int)Pseudorange.size(); i++)
            vPR.push_back(Pseudorange[i]);

		int result = pObsModel->Prepare(obsData.measures.header.epoch, vSat, vPR, (*( (*pObsModel).getDefaultEphemeris())) );
        return result;*/
		return pObsModel->Prepare(obsData.measures);
	}

	int setRxPos(gpstk::Position rxPos);

	inline void setGpsWeek(gpstk::DayTime Time)
	{
		gpsWeek = Time.GPSfullweek();
	}

	int prepareWithBancroft(gpstk::gnssSatTypeValue& gData)
	{
		return pObsModel->Prepare(gData.header.epoch,gData.body);
	}

	friend gpstk::gnssSatTypeValue& operator >>(gpstk::gnssSatTypeValue& gData, GPSTK_Nav& navData);

	friend gpstk::gnssSatTypeValue& operator>>(GPSTK_Obs& obsData, GPSTK_Nav& navData);

	inline void setEGNOSConfiguration(ModelObsExt::structEGNOSConfiguration EGNOSConfig) 
        {this->pObsModel->setEGNOSConfiguration(EGNOSConfig);}

protected:

	/*! \brief useMopsTM defines if the troppospheric corrections from the MOPS have to be applied or not*/
	bool useMopsTM;

	/*! \brief computeMOPS defines if MOPS weight have to be computed for a SolverWMS*/
	bool computeMOPS;

	/*! \brief Algorithms for computing MOPS weights*/
	gpstk::ComputeMOPSWeights MOPSWeights;

	/*! \brief Used to transfers textual information when an error or something else happen */
	string informationText;

	//!Minimun threshold for the CN0 on the pseudoranges
	int CNOThd;

	//Ground Truth position
	gpstk::Position GTPos;

	//! Store all the Satellite Ephemeris
	gpstk::GPSEphemerisStore ephStore;

	//! Store all the Satellite almanach
	gpstk::GPSAlmanacStore almStore;

	//! Store all the Ionospheric models
	gpstk::IonoModelStore ionoStore;

	// doit pouvoir �tre param�tr� au d�but
	gpstk::SimpleFilter *pFilter;

	//! Troppospheric model defined in the MOPS
	MOPSTropModel mopsTM;

	//! Pointer to the Observation Model
	gpstk::ModelObsExt *pObsModel;

	/*! \brief Add the DWORDS to the ionoStore object */
	bool addIonoFromDWord(const long subframe[10], unsigned short TOW)throw();

	/*! \brief Add the DWORDS to the almStore object */
	bool addAlmFromDWord(const long subframe[10])throw();

	/*! \brief Add the DWORDS to the lastEphSubframesStore map, and if complete 
	     to the ephStore object*/
	bool addEphFromDWord(const long subframe[10], gpstk::SatID curSatID,  int SFID, int SVID, short CHN)throw();

	/*! \brief Store the last subframes 1 to 3 for each Satellite*/
	std::map<gpstk::SatID,gpstk::EngEphemeris> lastEphSubframesStore;

	/*! \brief Iterator on private member variable lastEphSubframesStore*/
	std::map<gpstk::SatID,gpstk::EngEphemeris>::iterator itSatEph;

};


gpstk::gnssSatTypeValue& operator >>(gpstk::gnssSatTypeValue& gData, GPSTK_Nav& navData);


/*! \brief Allows to directly use the measurements (gpstk::gnssSatTypeValue) from a GPSTK_Obs object 
 *  in the observation model (gpstk::ModelObs) of a GPSTK_Nav object*/
inline gpstk::gnssSatTypeValue& operator>>(GPSTK_Obs& obsData, GPSTK_Nav& navData)
{
	return obsData.measures >> navData;
}


#endif
