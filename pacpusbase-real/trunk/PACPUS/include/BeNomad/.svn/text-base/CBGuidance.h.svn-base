/*==========================================================  (-*- C++ -*-)
 *
 * @file CBGuidance.h
 * 
 * @version  $Id: CBGuidance.h,v 1.8 2005/09/29 13:31:47 dlabrousse Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBGUIDANCE_H__
#define __CBGUIDANCE_H__

/*!
  @file CBGuidance.h
	CBGuidance class definition.
*/

#include "CBRoadNetwork.h"
#include "CBPlanner.h"
#include "BCartoConst.h"
#include "CBNMEAParser.h"

class CBGuidanceImp;
class CBSVSMgr;
class CBSVS;
class CBRouteSheet;
class CBGeoRoadLocation;
class CBGuidanceUserCbk;
class CBGeoMapMatchedPoint;

/**
 * @class CBGuidance
 *
 * @brief This class defines a turn by turn navigator.
 *
 * CBGuidance is a class that defines a turn by turn navigator.
 * 
 * There are 2 different modes :
 * 
 * 1. Tracking mode : No route is defined (and in particular no destination point).
 * Navigation essentially consist in matching GPS point on map(s).
 * 2. Navigation mode : A destination point is defined by user and, optionally, a departure point.
 * If no departure point is defined, the navigator will first try to map match current GPS receiver
 * and as soon as a map-matching is successful, will compute a route from that position to destination point.
 * User can define route parameters like vehicle mode, fastest/shortest and toll/no toll.
 * Once a route is defined there are two possibilities : either vehicle is on defined route or not.
 * If the vehicle is not on the route, the navigator will check if next GPS positions are on route
 * and if it is not the case, will compute a new route from current position to destination (re-routing).
 * Each time a route is computed, the direction of motion of the vehicle is taken into account so that
 * route starts in the correct direction in order to avoid u-turn instructions at the beginning of route.
 * A specific algorithm is used for map-matching GPS position on defined route.
 * Since v1.7.0, in areas where GPS signal is poor or unavailable like in tunnels, the navigator will switch into a position
 * estimation mode so that navigation continues to function normally. Positions' estimations rely on the assumption
 * that receiver keeps following computed route and that its speed remains more or less constant.
 * 
 * All these different modes and situations are modelized by a state machine. There are all
 * together 8 different possible states (see #EB_NAV_STATE).
 * Four different user defined callbacks enable user to customize this navigator by updating current view and
 * displaying various types of information. It is up to user to implement these callbacks.
 * Each of these callbacks have a common parameter which is a user data of type \c void *.
 * This enables user to access, within the callbacks, to any type of data he may need (like
 * a pointer on an object of an user's defined class).
 * For more detail on these callbacks see #CBGuidanceUserCbk.
 */
class BNAV_EXPORT CBGuidance
{
public:

  /**
   * @enum EB_NAV_STATE
   * An enumeration that defines 8 possible states in which this class can be
   */  
  enum EB_NAV_STATE {
    INIT               = 0x00,  //!< Initial state    : first state after start
		TRACKING           = 0x01,  //!< Tracking state   : no route defined
    GET_START          = 0x02,  //!< Get start state  : a destination point was defined but route not yet computed
		ON_ROUTE           = 0x03,  //!< On route state   : a route is defined and vehicle is on the route
    ESTIMATE           = 0x04,  //!< Estimating state : a route is defined and vehicle is on the route but its position is estimated due to bad GPS conditions
    OFF_ROUTE          = 0x05,  //!< Off route state  : a route is defined but vehicle is not on the route
		NO_GPS             = 0x06,  //!< No GPS state     : no GPS data available (GPS receiver is not responding or insufficient GPS reception)
		STOP               = 0x07   //!< Stop state       : vehicle arrived to destination or user stopped the navigation process
  };

  /**
    * @enum EB_ERROR
    * This enum defines all the possible errors of a turn by turn navigator.
    */
  enum EB_ERROR {
    NONE                      =  0, //!< No error
		INVALID_NMEA_PARSER       =  1, //!< Invalid NMEA parser (null)
    INTERNAL_ERROR            =  2, //!< Internal error
		NOT_ENOUGH_MEMORY         =  3, //!< Not enough memory on device
		ALREADY_IN_PROCESS        =  4, //!< Method Start has been called during Start process
		DEPT_NOT_ACCESSIBLE       =  5, //!< A departure has been specified but it is not accesible
		DEST_NOT_ACCESSIBLE       =  6, //!< A destination has been specified but it is not accesible
		NO_ROAD_NETWORK           =  7, //!< Missing data for path computation in SVSs
		TRANSP_MODE_NOT_SUPPORTED =  8, //!< Transportation mode is note supported by SVSs
		NO_PATH                   =  9, //!< No route found from departure to destination : SVSs are probably not connex
		INVALID_ROUTE_SVS         = 10, //!< Invalid route SVS (null or not dynamic)
		INVALID_START_ARGUMENTS   = 11  //!< Start() method called with invalid arguments
  };

  /**
    * @struct EB_NAV_OPTIONS
    * This structures defines additional navigation options
    * @since v1.7.0
    */
  struct EB_NAV_OPTIONS {
    TBbool getAdminPath;            //!< This option determines if administrative path should be computed on matched points (default \c false)
    TBbool computeRouteSheetAngles; //!< This option determines if field \a angles of #CBRouteSheet::TB_INSTRUCTION should be filled (default \c false)
  };

	/**
   * Constructor.
   * @param inSVSMgr The SVS manager (see #CBSVSMgr).
	 * @param inNMEAParser The NMEA parser object (see #CBNMEAParser)
	 * @param inLanguageCode Preferential language for objects' names (see #EB_LANGUAGE_CODE).
   * @param inNetwork Road network for route calculations (see #CBRoadNetwork). Default value = NULL
   * @param inTranspMode Transportation mode (see #CBRoadNetwork::EB_TRANSP_MODE). Default value = #CBRoadNetwork::EB_PASSENGER_CAR
   * @param inCriteria Criterias for route calculation (see #CBPlanner::EB_CRITERIA) (for navigation mode only). Default value = #CBPlanner::DEFAULT
   * @param inDynamicRouteSVS Dynamic SVS in which route forms will be added (for navigation mode only). Default value = NULL
   * @param inRouteClassID Class ID of the graphical route (for navigation mode only). Default value = #KB_ROUTE_CLASS
   * @note For tracking mode use default values for parameters 4 to 8. If parameter \a inNetwork is NULL only tracking mode is possible.
	 */
  CBGuidance(CBSVSMgr                    * inSVSMgr,
						 CBNMEAParser                * inNMEAParser,
						 EB_LANGUAGE_CODE              inLanguageCode    = DEFAULT_LANGUAGE,
						 const CBRoadNetwork         * inNetwork         = NULL,
						 CBRoadNetwork::EB_TRANSP_MODE inTranspMode      = CBRoadNetwork::EB_PASSENGER_CAR,
						 CBPlanner::EB_CRITERIA        inCriteria        = CBPlanner::DEFAULT,
						 CBSVS                       * inDynamicRouteSVS = NULL,
						 TBuint32                      inRouteClassID    = KB_ROUTE_CLASS);

  /**
   * Destructor.
   */
  virtual ~CBGuidance(void);

  /**
	 * Starts the guidance or tracking process. 
   * @note The calling thread/process will be blocked until you call explicitly the #Stop method
   * or your guidance callbacks implementation return \c false (See #BChangeStateCbk and #BPositionCbk).
   * @param inDestination Defines a destination point (default NULL)
   * @param inDeparture Defines a departure point (default NULL)
	 * @note If \a inDestination is NULL, navigation will function in tracking mode.
   * @return Error of navigation
   */
  EB_ERROR Start(const CBGeoRoadLocation * inDestination = NULL,
								 const CBGeoRoadLocation * inDeparture   = NULL) const;
  
  /**
   * Starts the guidance process with multiple via points. 
   * @note The calling thread/process will be blocked until you call explicitly the #Stop method
   * or your guidance callbacks implementation return \c false (See #BChangeStateCbk and #BPositionCbk).
   * @param inVia Defines an array of via points + final point
   * @param inNbVias Number of via points
   * @param inDeparture Defines a departure point (default NULL)
   * @return Error of navigation
   * @since v1.5
   */
  EB_ERROR Start(const CBGeoRoadLocation ** inVia,
								 TBuint32                   inNbVias,
								 const CBGeoRoadLocation  * inDeparture = NULL) const;
  
  /**
	 * Stops the current guidance or tracking process.
   * @note Since the #Start method blocks the calling thread/process, this method should be called
   * from another thread of execution (multithreading support is required if you want to use this method).
   */
  void Stop(void) const;
   
  /**
	 * Forces rerouting (for navigation mode only): recomputes route after blocking road segments of
   * current route starting from next intersection and within a given length.
   * Call this method during navigation process if you wish to force rerouting
   * @note Since the #Start method blocks the calling thread/process, this method should be called
   * from another thread of execution (multithreading support is required if you want to use this method).
   * @note A rerouting is operated if and only if current state is #ON_ROUTE.
   * Each call to this method removes all road blocks set by previous calls to this method before adding new ones.
   * If \a inLength is 0, this method simply removes all road blocks (if any) and reroutes
   * without adding any new road blocks.
   * @param inLength The length in meters of current route to block before rerouting
   * @since v1.7.0
   */
  void Reroute(TBuint32 inLength);
 
  /**
	 * Sets additional navigation options
   * @param inOptions The navigation options
	 * @note This method will not be effective if called after #Start method.
   * @since v1.7.0
   */
	void SetOptions(const EB_NAV_OPTIONS& inOptions);

  /**
	 * Returns the user defined callbacks and data.
	 * @note Use this method to set your user defined guidance callbacks (see #CBGuidanceUserCbk).
   */
  inline CBGuidanceUserCbk * GetUserCbk(void) const { return mUserCbk; }
  
	/**
   * \internal
   */
  inline const CBGuidanceImp * GetGuidanceImp(void) const { return mImp; }

private:
  CBGuidance(void);
  // Disable copy
  CBGuidance(const CBGuidance&);
  CBGuidance & operator=(const CBGuidance&);

private:
  CBGuidanceImp     * mImp;
	CBGuidanceUserCbk * mUserCbk;
};



/**
 * @struct TB_TIME_AND_DIST
 * A structure that contains a time (or period) in seconds and a corresponding distance in meters.
 */
typedef struct {
	TBuint32 time;     //!< Time in seconds
	TBuint32 distance; //!< Distance in meters
} TB_TIME_AND_DIST;

/**
 * @struct TB_POSITION_DATA
 * A structure that contains information accesible to user with user's defined callback #mPositionCbk.
 */
typedef struct {
	CBGuidance::EB_NAV_STATE     state;       //!< Current navigation state (see #EB_NAV_STATE)
	const CBGeoMapMatchedPoint * pos;         //!< Vehicle's matched position
	const CBRouteSheet         * routeSheet;  //!< Route sheet that allows you to retrieve all route sheet instructions.
  TBuint32                     curInstrIdx; //!< Index of the current route sheet's instruction  
	TB_TIME_AND_DIST             toNext;      //!< Time and distance left to reach next manoeuvre
	TB_TIME_AND_DIST             toDest;      //!< Time ans distance left to reach destination
  TB_GPS_POS_INFO              gpsData;     //!< GPS position used to match the vehicle position
} TB_POSITION_DATA;

/**
 * \typedef BChangeStateCbk
 * This typedef defines the prototype of the user callback called by the navigation  
 * process each time the navigation's state changes.
 * @param inUserData  A user data.
 * @param inFromState Previous navigation state
 * @param inToState   Next navigation state
 * @return if \c false, navigation process will be stopped.
 */
typedef TBbool (*BChangeStateCbk) (TBany                           inUserData,
																	 const CBGuidance::EB_NAV_STATE& inFromState,
																	 const CBGuidance::EB_NAV_STATE& inToState);

/**
 * \typedef BGPSInfoCbk
 * This typedef defines the prototype of the user callback called by the navigation  
 * process each time a new position is available from GPS receiver.
 * @param inUserData A user data.
 * @param inGPSData  New GPS Data (see #TB_GPS_POS_INFO)
 */
typedef void (*BGPSInfoCbk) (TBany                  inUserData,
														 const TB_GPS_POS_INFO& inGPSData);

/**
 * \typedef BPositionCbk
 * This typedef defines the prototype of the user callback called by the navigation  
 * process each time a GPS point is successfully matched on map.
 * @param inUserData     A user data.
 * @param inPositionData Information on position, current route instruction, etc. (see #TB_POSITION_DATA)
 * @return if \c false, navigation process will be stopped.
 */
typedef TBbool (*BPositionCbk) (TBany                   inUserData,
																const TB_POSITION_DATA& inPositionData);

/**
 * \typedef BAutoRerouteCbk
 * This typedef defines the prototype of the user callback called by the navigation  
 * process each time a re-routing is necessary. If this callback is not defined or return value is \c true,
 * rerouting will be processed. If return value is \c false, navigation will enter in #TRACKING state.
 * @param inUserData  A user data.
 * @return if \c false, navigation will enter in #TRACKING state, if \c true re-routing will be processed.
 */
typedef TBbool (*BAutoRerouteCbk) (TBany inUserData);


/**
 * @class CBGuidanceUserCbk
 *
 * @brief This class defines a set of user callbacks for the turn by turn navigator.
 *
 * CBGuidanceUserCbk is a class that defines a set of 4 different user callbacks for the turn by turn navigator.
 */
class BNAV_EXPORT CBGuidanceUserCbk
{
public:

  /**
   * Constructor.
	 */
	CBGuidanceUserCbk();

	/**
   * Destructor.
	 */
	~CBGuidanceUserCbk();

public:

	TBany           mUserData;       //!< User's data
	BChangeStateCbk mChangeStateCbk; //!< Callback called each time the state changes in guidance/tracking process (see #EB_NAV_STATE)
	BGPSInfoCbk     mGPSDataCbk;		 //!< Callback called each time a new position is available from GPS receiver
	BPositionCbk    mPositionCbk;    //!< Callback called each time a GPS point is successfully matched on map
	BAutoRerouteCbk mAutoRerouteCbk; //!< Callback called each time a re-routing is necessary
};

#endif // __CBGUIDANCE_H__
