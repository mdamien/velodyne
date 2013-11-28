#ifndef _ionoCorrections_H
#define _ionoCorrections_H

#define MAX_NB_IGP 201

#include "PRNMask.hpp"
#include "structure/structureSBAS.h"
#include "DayTime.hpp"
#include "Position.hpp"
#include <set>
#include "IonoModel.hpp"
#include "Geodetic.hpp"
#include "geometry.hpp"
#include "icd_200_constants.hpp"
#include "WGS84Geoid.hpp"
#include "TypeID.hpp"
#include <math.h>
//#include "uiIonoGrid.hpp"
//#include "VectorOperators.hpp"

namespace Ui
{
	class uiIonoGrid;
	class uiIonoCompute;
};



namespace SBAS
{
	/*! \class bandIGPCoord
	 *	\brief Contains the coordinates of all Ionospheric grid */
	/*! IGP : Ionospheric Grid Point
	 *  All the points are divided in five bands with 201 points each*/
	class bandIGPCoord
	{

		friend class ionoCorrections;

		private:

			/*!\brief singleton to keep a unique instance of this class*/
			static bandIGPCoord singleton;

			/*!\brief Constructor, Initialise all the point's coordinates*/
			/*! One can note that the constructor is private, as only one object of this class 
			 *  has to instanciated (principle of the singleton)*/
			bandIGPCoord();

			/*!\brief Equlity operator function on pointer overload*/
			bandIGPCoord& operator=(bandIGPCoord&);

			/*!\brief Copy Constructor*/
			/*! One can note that the constructor is private, as only one object of this class 
			 *  has to instanciated (principle of the singleton)*/
			bandIGPCoord(const bandIGPCoord&);

		protected:

			/*!\brief Array of coordinates of the 3rd band*/
			gpstk::Position thirdBand[201];
			/*!\brief Array of coordinates of the 4th band*/
			gpstk::Position fourthBand[201];
			/*!\brief Array of coordinates of the 5th band*/
			gpstk::Position fifthBand[201];
			/*!\brief Array of coordinates of the 6th band*/
			gpstk::Position SixthBand[201];
			/*!\brief Array of coordinates of the 9th band*/
			gpstk::Position NinthBand[201];

		public:

			/*!\brief Used to create a pointer on the single objet of this class (principle of the singleton)*/
			static bandIGPCoord& instance() {return singleton;};

		};


	/*! \class bandIGPCoord
	 *	\brief Constructs the ionospheric grid and compute thecorrections*/
	/*! The ionospheric corrections are based on a grid of points on all the earth, divided in ten bands.
	 *  SBAS provides a mask which defined the points which are monitored, then it send corrections values 
	 *  for each point. <BR>
	 *  The data record and access is performed with the help of two data structure : <BR>
	 *  - fullIonoGrid is a STL map whose key is the bandNumber, and the content is another STL map whose key
	 *  is the mask ID of a point ant the content is the corrections values associated to this point<BR>
	 *  - physicalGrid is an 2D-array whose represent the physcial grid. It associate a bandNumber and a mask ID
	 *  to each point monitored by the SBAS. It makes easier the search of the point which surround the satellite 
	 *  pierce point<BR>
	 *  Both data structure are simultaneously maintained*/
	class ionoCorrections
	{
		/* ! \brief Allow the graphical user interface to access to the member variables */
		friend class Ui::uiIonoGrid;
		/* ! \brief Allow the graphical user interface to access to the member variables */
		friend class Ui::uiIonoCompute;

	public:

		/*! \struct IGPDataStruct
		 *  \brief Store all the data associated to one point of the IGP*/
		typedef struct {

			/*! \brief Position of the point*/
			gpstk::Position position;

			/*! \brief Grid Ionospheric Vertical Error*/
			float GIVE;

			/*! \brief Variance of the GIVE (Grid Ionospheric Vertical Error)*/
			float sigmaGIVE;

			/*! \brief Vertical Delay (m)*/
			float verticalDelay;

			/*! \brief Store if the point is currently monitored or not*/
			bool monitored;

			/*! \brief Time of reception of the current Values*/
			gpstk::DayTime timeOfReception;

		}IGPDataStruct;

		/*! \brief Constructor, initialise the member variables and the physicalGrid as empty*/
		ionoCorrections();

		/*! \brief Add a name to the gpstk::TypeID variables created (EGNOSSlantIono and EGNOSSigma2UIRE)*/
		void iniateTypeID();

		/*! \brief Add a Ionospheric Grid Point Mask message*/
		/*! If the iono Mask is unknown for a band or if the IODI has changed, store the correspondance
		 *  between the maskID and the coordinates' points in the fullIonoGrid map. Values of the points 
		 *  are set to 0. 
		 * \param pointer to the structIonosphericGridPointMask data
		 *  \return return an integer, equal to 1 if the data are correct 0 otherwise
		 */ 
		int addMT18(const SBAS::structIonosphericGridPointMask* data);

		/*! \brief Add the correction values to some points of the ionospheric grid*/
		/*! 
		 * \param pointer to the structIonosphericDelayCorrections data
		 * \param msgReceptionTime Time at which the data have been received
		 * \return return an integer, equal to 1 if the data are correct 0 otherwise
		*/ 
		int addMT26(const SBAS::structIonosphericDelayCorrections* data, gpstk::DayTime msgReceptionTime);

		/*! \brief Add data from a degradation factor message*/
		/*! \param pointer to the structDegradationParameters data
		 *  \return return an integer, equal to 1 if the data are correct 0 otherwise
		 */ 
		int addMT10(const SBAS::structDegradationParameters* data);

		/* !\brief get the ionospheric correction value.*/
        /* !\param time the time of the observation
          * \param rxgeo the WGS84 geodetic position of the receiver
          * \param svel the elevation angle between the rx and SV (degrees)
          * \param svaz the azimuth angle between the rx and SV (degrees)
          * \param freq the GPS frequency the observation was made from
		  * \param sigma2UIRE output sigma correction
		  * \param slantIonoDelay output iono delay correction
		  * \param epsIonoGrid[4] for debugging purpose
          * \return the ionospheric correction (meters)
          */
		void getCorrection(const gpstk::DayTime& time,
						   const gpstk::Position& receiverPos,
                           double svel,
                           double svaz,
						   double *sigma2UIRE,
						   double *slantIonoDelay,
						   gpstk::IonoModel::Frequency freq = gpstk::IonoModel::L1,
						   double debugOutput[6] = NULL) const
							/*throw(gpstk::IonoModel::InvalidIonoModel)*/ ;


		/*! \brief Return the Issue of Data Iono*/
		unsigned short getIODI() const
		{return IODI;};

		/*!\brief Array which makes the correspondance between the GIVE Indicator and the corresponding variance*/
		static const float sigma2GIVETable[15];

		/*! \brief Pointer to the singleton IGPCoord object*/
		static SBAS::bandIGPCoord& IGPCoord;

		/*! \sruct structIGPID
		 *  \brief simple structure to associate a bandNumber and a maskID, what defines  point in the ionospheric grid*/
		/*! used in the physicalGrid array to point to elements of fullIonoGrid object (bandIonoGridMap STL map)*/
		typedef struct{
			/* \brief number of the band (between 0 and 10), */
			/* !to use with the IGPCoord pointer fullIonoGrid object (bandIonoGridMap STL map)
			 * Set to 11 to notify that it does not points to an existing grid point*/
			unsigned char bandNumber;

			/* \brief mask ID of the grid point, with repect to its band number*/
			/*! Set to MAX_NB_IGP+1 to notify that it does not points to an existing grid point*/
			unsigned int maskID;
		}
		structIGPID;

		/* \brief Map to associate a */
		typedef std::map<unsigned int,IGPDataStruct> maskIGPDataMap;
		typedef std::pair<unsigned int,IGPDataStruct> maskIGPDataPair;

		/* \brief Map to associate a */
		typedef std::map<unsigned char,maskIGPDataMap> bandIonoGridMap;
		typedef std::pair<unsigned char,maskIGPDataMap> bandIonoGridPair;

		/* \brief Maximum height of the electron Density (m), assumed to be 350km for SBAS*/
		const long maxElectronDensityHeight; 

		//typedef std::pair<unsigned char,SBAS::structIonosphericGridPointMask> ionoGridMaskPair;
		//typedef std::map<unsigned char,SBAS::structIonosphericGridPointMask> ionoGridMaskMap;

		/*! \brief New TypeID to store the SBAS ionospheric correction into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSlantIono;
		
		/*! \brief New TypeID to store the variance of the User Ionospheric Range Error into the gsptk data strcutures*/
		static gpstk::TypeID EGNOSSigma2UIRE;


	protected:
		
		
		/*! \brief number of element in the latitude dimension of the physicalGrid*/
		/*! 35 beacause it starts at -85 (index 0) and ends at +85 (index 35)*/
		static const int ILATMAX;
		
		/*! \brief number of element in the longitude dimension of the physicalGrid*/
		/*! 35 beacause it starts at -60 (index 0) and ends at +95 (index 32)*/
		static const int ILONGMAX;

		/*! \brief element in the latitude dimension of the physicalGrid which refers to the latitude 0*/
		/*! 17 beacause it starts at -85 (index 0)with 5deg steps*/
		static const int ILATZERO;

		/*! \brief element in the longitude dimension of the physicalGrid which refers to the longitude 0*/
		/*! 12 beacause it starts at -60 (index 0)with 5deg steps*/
		static const int ILONGZERO;


//		/*! \sruct triangleInterpolationCase
//		 *  \brief Structure used to compute the ionospheric error based on three Grid Point forming a right-angled triangle*/
//		typedef struct{
//		   /*! \brief Contains the data of the three grid points*/
//		   /*! the IGP1 is the corner of the triangle with the 90degrees angle*/
//		   IGPDataStruct IGP1, IGP2, IGP3;
//
//		   /*! \brief Type of the triangle, what means how it is oriented regarding to north and est*/
//		   /*! the IGP1 is the corner of the triangle with the 90degrees angle, IGP2 has to be on the 
//		    *  same latitude as IGP1, IGP3 has to be on the same longitude as IGP1
//		    * type = 1 - IGP2: right, IGP3: up
//		    * type = 2 - IGP2: right, IGP3: down
//		    * type = 3 - IGP2: left , IGP3: down
//		    * type = 4 - IGP2: left , IGP3: up*/
//		   int type;
//	   }triangleInterpolationCase;

//		/*! \sruct squareInterpolationCase
//		 *  \brief Structure used to compute the ionospheric error based on four Grid Point forming a square*/
//		typedef struct{
//			/*! \brief Contains the data of the up left point*/
//		   IGPDataStruct IGPul; 
//			/*! \brief Contains the data of the up right point*/
//		   IGPDataStruct IGPur; 
//			/*! \brief Contains the data of the down right point*/
//		   IGPDataStruct IGPdr; 
//			/*! \brief Contains the data of the down left point*/
//		   IGPDataStruct IGPdl; 
//	   }squareInterpolationCase;

		/* !\brief Find the points of the grid which surround the piercepoint with respect to the SBAS specifications*/
        /* !\param piercePoint Coordinates of the pierce point
          * \param triangle pointer on boolean which return if the surrounding points have a triangle shape 
          * \param square pointer on boolean which return if the surrounding points have a square shape
          * \param triangleType pointer on the type of triangle. : <BR>
		  *	type = 1 - IGP2: right, IGP3: up <BR>
		  * type = 2 - IGP2: right, IGP3: down <BR>
	      * type = 3 - IGP2: left , IGP3: down <BR>
	      * type = 4 - IGP2: left , IGP3: up
		  * \param IGP pointer on an array of four IGPDataStruct which contains the data of the surrounding points 
		  *  of the gridContains the data of the three grid points. Points position is defined as follows : <BR>
		  *  IGP[0] is the corner of the triangle with the 90degrees angle or the dow left point in a square case <BR>
		  *  IGP[1] has to be on the same latitude as IGP[0] <BR>
		  *  IGP[2] has to be on the same longitude as IGP[0] <BR>
		  *  IGP[3] is the up rigth corner in the square case <BR>
          */
		void findInterpolationCase(gpstk::Position piercePoint,
									bool *triangle,
									bool *square,
									char *triangleType,
									IGPDataStruct *IGP) const;

		int test_interpolation_cases(const double &lat_pp, 
									 const double &long_pp, 
									 const int &latID_pp, 
									 const int &longID_pp,
									 bool &IGPdl, 
									 bool &IGPdr, 
									 bool &IGPul, 
									 bool &IGPur,
									 bool &squareUpRight, 
									 bool &squareUpLeft,
									 int &surrounding, 
									 bool *square, 
									 bool *triangle, 
									 int incr) const;

		/*! \brief Issue of Data Ionosphere*/
		short IODI;

		/*! \brief Bound on the update error for ionospheric grid delay (from MT10)*/
		double Ciono_step;

		/*! \brief Rate of change for the ionospheric grid delay values (from MT10)*/
		double Ciono_ramp;

		/*! \brief Update intervalfor ionospheric corrections (from MT10)*/
		unsigned short Iiono;

		/*! \brief root-sum-square flag for ionospheric information (from MT10)*/
		bool RSSIono;

		/*! \brief bandIonoGridMap object which store the data (coordinates and corrections values) 
		 *  of all the monitored points of the ionospheric grid. They can be accessed by their maskID
		 *  and band Number*/
		bandIonoGridMap fullIonoGrid;

		/*! \brief Earth Grid to associate geographic coordinates to elements of fullIonoGrid*/
		/* ! Quantification is 5 degrees on lattitude and longitude.
		 *   Fisrt dimension is longitude, between -60 (index 0) and +95 (index 32)
		 *   Second dimenstion is latitude, between -85 (index 0) and +85 (index 35) 
		 *   Each structIGPID element of the array give a reference to the bandNumber and the maskID of the point.
		 *	 If no iono grid point exists for these coordinates or no values are available for it, data of the 
		 *	 structure has specific values (see sruct structIGPID). <BR>
		 *	 Mainly used to search a surrounding point aroud the pierce point in findInterpolationCase() */
		structIGPID physicalGrid[32][35];

		/* !\brief Give the correction values of a point based on the number of the band it belongs and its mask ID*/
        /* !\param input structIGPID wich contains the band number and the mask ID of the point
          * \return the corrections values in a IGPDataStruct
          */
		IGPDataStruct getIGPDataFromPhysicalGrid(structIGPID input) const;

		gpstk::Position getSBASIonosphericPiercePoint(gpstk::Position Rx,
														const double elev,
														const double azim,
														const double ionoht) const;


	private:

		static const float EarthElecRatio;



	};

}
#endif
