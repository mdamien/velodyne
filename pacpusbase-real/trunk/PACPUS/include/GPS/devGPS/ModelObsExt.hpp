#ifndef _ModelObsExt_H
#define _ModelObsExt_H

#include "ModelObs.hpp"
#include "ionoCorrections.hpp"
#include "tropoCorrections.hpp"
#include "PRNMask.hpp"
#include "fastCorrections.hpp"
#include "SBASCorrectedEphemerisRange.hpp"

namespace gpstk
{
	class ModelObsExt
        : public ModelObs
	{
	public:

		ModelObsExt(const Position& RxCoordinates, IonoModelStore& dIonoModel, TropModel& dTropoModel, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/
			:ModelObs(RxCoordinates, dIonoModel, dTropoModel, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}


        ModelObsExt(const Position& RxCoordinates, IonoModelStore& dIonoModel, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/ 
			:ModelObs( RxCoordinates,dIonoModel, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}


        ModelObsExt(const Position& RxCoordinates, TropModel& dTropoModel, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/
			:ModelObs(RxCoordinates, dTropoModel, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}


        ModelObsExt(const Position& RxCoordinates, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/ 
			:ModelObs(RxCoordinates, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}


        ModelObsExt(IonoModelStore& dIonoModel, TropModel& dTropoModel, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/ 
			:ModelObs(dIonoModel, dTropoModel, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}


        ModelObsExt(IonoModelStore& dIonoModel, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/ 
			:ModelObs(dIonoModel, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}


        ModelObsExt(TropModel& dTropoModel, XvtStore<SatID>& dEphemeris, const TypeID& dObservable, bool usetgd = true) /*throw(Exception)*/ 
			:ModelObs(dTropoModel, dEphemeris, dObservable, usetgd), SBAScerange(&dEphemeris)
		{ModelObsExt::initVar();
		 SBASfastCorr.setPRNMask(&SBASprnMask);
         SBAScerange.setPRNMask(&SBASprnMask);}

		satTypeValueMap& Process(const DayTime& time, satTypeValueMap& gData) /*throw(Exception)*/;

		static gpstk::TypeID::ValueType ddx;      ///< In the position domain: Velocity bias, X component; in the range domain: ddx coefficient
		static gpstk::TypeID::ValueType ddy;      ///< In the position domain: Velocity bias, Y component; in the range domain: ddy coefficient
		static gpstk::TypeID::ValueType ddz;      ///< In the position domain: Velocity bias, Z component; in the range domain: ddz coefficient
		static gpstk::TypeID::ValueType cddt;      ///< In the position domain: Receiver drift offset, meters; in the range domain: cddt coefficient

		static gpstk::TypeID::ValueType velSatX;      ///< Satellite Velocity, X component
		static gpstk::TypeID::ValueType velSatY;      ///< Satellite Velocity, Y component
		static gpstk::TypeID::ValueType velSatZ;      ///< Satellite Velocity, Z component

		static gpstk::TypeID::ValueType C1corr; 
		static gpstk::TypeID::ValueType prefitD;
		static gpstk::TypeID::ValueType ddtSat;
	 

		SBAS::ionoCorrections SBASIonoModel;

		SBAS::tropoCorrections SBASTropoModel;

		SBAS::PRNMask SBASprnMask;

		SBAS::fastCorrections SBASfastCorr;

		SBAS::SBASCorrectedEphemerisRange SBAScerange;
			
		typedef struct
		{
			bool ionoCorrections;
			bool FastCorrections;
			bool LongTermCorrections;
			bool IntegrityInformation;
		} structEGNOSConfiguration;

		inline structEGNOSConfiguration getEGNOSConfiguration() const
            {return EGNOSConfig;}

		inline void setEGNOSConfiguration(structEGNOSConfiguration EGNOSConfig) 
            {this->EGNOSConfig = EGNOSConfig;}

	protected : 

		structEGNOSConfiguration EGNOSConfig;

		void initVar();

        /// Initial index assigned to this class.
        static int classIndex;

        /// Index belonging to this object.
        int index;

        /// Sets the index and increment classIndex.
        void setIndex(void) { (*this).index = classIndex++; }

	};

}

#endif
