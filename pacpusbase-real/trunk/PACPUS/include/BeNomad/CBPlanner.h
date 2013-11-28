/*==========================================================  (-*- C++ -*-)
 *
 * @file CBPlanner.h
 * 
 * @version  $Id: CBPlanner.h,v 1.63 2006/06/12 09:23:28 wkunkel Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBPLANNER_H__
#define __CBPLANNER_H__

/*!
  @file CBPlanner.h
	CBPlanner class definition.
*/

#include "CBSVS.h"
#include "CBRoadNetwork.h"

class CBRoute;
class CBPlannerImp;
class CBGeoRoadLocation;


/**
 * @class CBPlanner
 *
 * @brief This class defines a route planner
 *
 * CBPlanner is a class that defines a route planner. Route computation uses 
 * class #CBRoadNetwork. If a route is found between two points a #CBRoute object
 * is built which can be used for :
 *  - building a route sheet with class #CBRouteSheet
 *  - route display on a map.
 *
 * @warning Contrary to the #CBRoadNetwork class, the CBPlanner class does not support 
 * arrival or deletion of SVS file(s) from the #CBSVSMgr. In this case, you have to 
 * reconstruct a new instance of the CBPlanner class.
 *
 * @note Multithreading support : The CBPlanner class can be used in separate threads to
 * perform route computations.
 */
class BPLN_EXPORT CBPlanner
{
public:

  /**
   * \enum EB_CRITERIA
   * An enumeration that defines route criteria
   */  
  enum EB_CRITERIA {
    DEFAULT  = 0x00,  //!< Finds a route which may have tolls (optimization on route time).
    NO_TOLL  = 0x01,  //!< Finds a route with no toll.
    SHORTEST = 0x02   //!< Optimization on route length.
  };

	 
  /**
    * @enum EB_ERROR
    * This enum defines all the possible errors of a route computation between two points.
    */
  enum EB_ERROR {
    NONE                      =  0, //!< No error : a route is found
    NO_GRAPH_MGR              =  1, //!< Road network is null (see #CBRoadNetwork)
    NO_GRAPH_IN_GRAPH_MGR     =  2, //!< Road network is empty (see #CBRoadNetwork)
    NO_NODES_IN_START_SVS     =  3, //!< Internal error
    NO_NODES_IN_STOP_SVS      =  4, //!< Internal error
    NO_GRAPH_FOR_START_SVS    =  5, //!< Internal error
    NO_GRAPH_FOR_STOP_SVS     =  6, //!< Internal error
		INTERNAL_ERROR            =  7, //!< Internal error
    START_NOT_ACCESSIBLE      =  8, //!< Start point is not accessible with route computation parameters
    STOP_NOT_ACCESSIBLE       =  9, //!< Stop point is not accessible with route computation parameters
    NO_PATH                   = 10, //!< No possible route with route computation parameters
    TRANSP_MODE_NOT_SUPPORTED = 11, //!< Transportation mode is not supported by at least one opened SVS in road network (see #CBRoadNetwork)
    NO_START                  = 12, //!< For route computation with multiple points : no start point defined
    NO_STOP                   = 13, //!< For route computation with multiple points : no stop point defined
		NOT_ENOUGH_MEMORY         = 14  //!< Not enough memory
  };

  /**
   * Constructor.
   * @param inNetwork Road network (see #CBRoadNetwork)
   * @param inDestroyRouteForms If \c true (default), forms in class CBRoute will be destroyed in destructor
   */
  CBPlanner(const CBRoadNetwork * inNetwork, TBbool inDestroyRouteForms = true);

  /**
   * Destructor.
   */
  ~CBPlanner(void);

  /**   
   * Returns the maximum speed for vehicles in range [0, 115] (km/h).
   * The default value (0 km/h) means that no maximum speed is defined.
   * @return The maximum speed for vehicles.
   * @since v1.5 Creation
   */
  TBuint16 GetMaxSpeed(void) const;

  /**   
   * Specifies a maximum speed for vehicles in range [0, 115] (km/h).
   * The default value (0 km/h) means that no maximum speed is defined.
   * @param inMaxSpeed The maximum speed for vehicles in range [0, 115] (km/h).
   * @since v1.5 Creation
   */
  void SetMaxSpeed(TBuint16 inMaxSpeed = 0);

  /*
   * Returns the current ponderation factor for speeds (Default = 1.0).
   * @return The current ponderation factor for speeds.
   * @since v1.5 Creation
   */
  TBfloat GetSpeedPonderation(void) const;

  /**   
   * Specifies a new ponderation factor for speeds (Default = 1).
   * @param inFactor New ponderation factor for speeds.
   * @since v1.5 Creation
   */
  void SetSpeedPonderation(TBfloat inFactor = 1.0f);

  /**   
   * Specifies a location where route must not go through. As many road blocks as desired can be set.
   * @note if \a inLocation is NULL, this method will remove all road blocks from planner.
   * @param inLocation The location of road block.
   * @since v1.6 Creation
   */
  void SetRoadBlock(const CBGeoRoadLocation * inLocation);

  /**
   * Removes first road block (in chronological order) from road blocks' list
   * @return \c true if road blocks' list was not empty, \c false otherwise
   * @since v1.7.0 Creation
   */
  TBbool UnsetFirstRoadBlock(void);

  /**
   * Removes last road block (in chronological order) from road blocks' list
   * @return \c true if road blocks' list was not empty, \c false otherwise
   * @since v1.7.0 Creation
   */
  TBbool UnsetLastRoadBlock (void);

  /**
   * Returns error of a route computation (#NONE if no error).
   * @return Error of a route computation
   */
  EB_ERROR GetError(void) const;
  
  /**
   * Returns number of routes (for route computation with multiple start points).
   * @return Number of routes
   */
  TBuint32 GetNbRoute(void) const;
  
  /**
   * Returns \a inIndex -th route (for route computation with multiple start points).
   * @param inIndex Route index (default = 0)
   * @return \a inIndex -th route
   */
  const CBRoute * GetRoute(TBuint32 inIndex = 0) const;
  

  /**
   * Computes a route between two road locations (\a inStart and \a inStop).
   * @param inStart Start point for route computation
   * @param inStop Stop point for route computation
   * @param inTranspMode Transportation mode (default CBRoadNetwork::EB_PASSENGER_CAR)
   * @param inCriteria Route criteria (See CBPlanner::EB_CRITERIA) (default 0: fastest and route with tolls are allowed).
   * Flags for mode fastest or shortest and with or without tolls.
   * @param inUseStartAngle If \c true, \a inStart's angle (see #CBGeoRoadLocation) will be used as a general direction for departure from start point (default = \c false).   
   * @return \c true if a route is found (i.e. \c mError = #NONE), \c false otherwise
   * @note if \a inTranspMode is one of CBRoadNetwork::EB_PEDESTRIAN or CBRoadNetwork::EB_BICYCLE
	 * route will allways be computed in mode shortest.
   * @note \c inStart's angle (see #CBGeoRoadLocation) will be used as a general direction for departure from start point.
   */
  TBbool PlanRoute(const CBGeoRoadLocation *     inStart,
                   const CBGeoRoadLocation *     inStop,
                   CBRoadNetwork::EB_TRANSP_MODE inTranspMode    = CBRoadNetwork::EB_PASSENGER_CAR,
                   CBPlanner::EB_CRITERIA        inCriteria      = CBPlanner::DEFAULT,
                   TBbool                        inUseStartAngle = false);

  /**   
   * Computes \a inNbVia - 1 routes between successive couples of road locations.
   * @param inVia Array of CBGeoRoadLocation.
   * @param inNbVia Number of road locations (or via points).
   * @param inTranspMode Transportation mode (default CBRoadNetwork::EB_PASSENGER_CAR)
   * @param inCriteria Route criteria (See CBPlanner::EB_CRITERIA) (default 0: fastest and route with tolls are allowed).
   * Flags for mode fastest or shortest and with or without tolls.
   * @return \c true if a route is found for each couple of points, \c false otherwise
   * @note if \a inTranspMode is one of CBRoadNetwork::EB_PEDESTRIAN or CBRoadNetwork::EB_BICYCLE
	 * route will allways be computed in mode shortest.
   */
	TBbool PlanRoute(const CBGeoRoadLocation * const * inVia,
									 TBuint32                          inNbVia,
									 CBRoadNetwork::EB_TRANSP_MODE     inTranspMode = CBRoadNetwork::EB_PASSENGER_CAR,
									 CBPlanner::EB_CRITERIA            inCriteria   = CBPlanner::DEFAULT);                   
       
  /**   
   * Computes \a inNbStart routes between \a inNbStart road locations and a unique arrival \a inStop point.
   * @param inStarts Array of start road locations for route computations
   * @param inNbStart Number of start road locations.
   * @param inStop Stop The arrival road location.
   * @param inTranspMode Transportation mode (default CBRoadNetwork::EB_PASSENGER_CAR)
   * @param inCriteria Route criteria (See CBPlanner::EB_CRITERIA) (default 0: fastest and route with tolls are allowed).
   * Flags for mode fastest or shortest and with or without tolls.
   * @return \c true if a route is found for each start point, \c false otherwise
   * @note if \a inTranspMode is one of CBRoadNetwork::EB_PEDESTRIAN or CBRoadNetwork::EB_BICYCLE
	 * route will allways be computed in mode shortest.
   */
  TBbool PlanRoute(const CBGeoRoadLocation * const * inStarts,
                   TBuint32                          inNbStart,
                   const CBGeoRoadLocation *         inStop,
                   CBRoadNetwork::EB_TRANSP_MODE     inTranspMode = CBRoadNetwork::EB_PASSENGER_CAR,
                   CBPlanner::EB_CRITERIA            inCriteria   = CBPlanner::DEFAULT);                   

  /**      
   * Computes \a inNbStop routes between a unique departure road location \a inStart and \a inNbStop arrival road locations.
   * @param inStart Start road location.
   * @param inStops Array of stop road locations for route computations
   * @param inNbStart Number of stop road locations.
   * @param inTranspMode Transportation mode (default CBRoadNetwork::EB_PASSENGER_CAR)
   * @param inCriteria Route criteria (See CBPlanner::EB_CRITERIA) (default 0: fastest and route with tolls are allowed).
   * Flags for mode fastest or shortest and with or without tolls.
   * @param inUseStartAngle If \c true, \a inStart's angle (see #CBGeoRoadLocation) will be used as a general direction for departure from start point (default = \c false).   
   * @return \c true if a route is found for each stop point, \c false otherwise
   * @note if \a inTranspMode is one of CBRoadNetwork::EB_PEDESTRIAN or CBRoadNetwork::EB_BICYCLE
	 * route will allways be computed in mode shortest.
   * @since v1.5
   */
  TBbool PlanRoute(const CBGeoRoadLocation *         inStart,
                   const CBGeoRoadLocation * const * inStops,
                   TBuint32                          inNbStop,
                   CBRoadNetwork::EB_TRANSP_MODE     inTranspMode    = CBRoadNetwork::EB_PASSENGER_CAR,
                   CBPlanner::EB_CRITERIA            inCriteria      = CBPlanner::DEFAULT,
                   TBbool                            inUseStartAngle = false);

  void DestroyRoutes(void);
 
  /**
   * \internal
   */
  inline CBPlannerImp * GetPlannerImp(void) const { return mImp; }

protected:
	
	const CBSVSMgr * GetSVSMgr(void) const;

private:

  CBPlannerImp * mImp;

  friend class CBRouteSheet;
};


/**
 * @class CBRoute
 * A class that represents a route between two points.
 */
class BPLN_EXPORT CBRoute
{
public:
  /**
	 * @struct TB_ROUTE_ELEM
	 * A structure that represents a route element.
	 */
	struct TB_ROUTE_ELEM {
	  const CBSVS * svs;      //!< SVS of route element (see #CBSVS)
	  CBForm      * frm;      //!< SVS object of route element (see #CBForm)
	  TBuint32      classID;  //!< Class ID of route element
    TBuint32      privData; //!< A private data for internal use
	};
 
  /** 
   * Returns the route status (\c NONE if no error).
   * @return The route status (\c NONE if no error).
   */
  CBPlanner::EB_ERROR GetStatus(void) const { return mError; }

  /** 
   * Returns the route length in meters.
   * @return The route length in meters.
   */
  inline TBuint32 GetLength(void) const { return mLength; }

  /** 
   * Returns the route time in seconds.
   * @return The route time in seconds.
   */
  inline TBuint32 GetTime(void) const { return mTime; }

  /** 
   * Returns the number of route elements in route.
   * @return The number of route elements in route.
   */
  inline TBuint32 GetNbElements(void) const { return mNbElem; }

  /** 
   * Returns a reference to the specified internal route element.
   * @return The a reference to the specified internal route element.
   */
  inline const CBRoute::TB_ROUTE_ELEM & GetRouteElement(TBuint32 inIndex) const
	{
    B_ASSERT(inIndex < mNbElem);
    return mElems[inIndex];
  }

  /** 
   * @example routing.cpp
   * This is an example of how to perform Routing computation.
   */

protected:
 
  /**
   * Constructs an empty route.
   */
  CBRoute(CBPlannerImp      * inPlanner,
          CBPlanner::EB_ERROR inError,
          TBbool              inDestroyRouteForms = true);

  /**
   * Destructor
   */
  ~CBRoute(void);

protected:

  CBPlannerImp      * mPlanner;  
	TBuint32            mLength;            //!< Route length in meters
	TBuint32            mTime;              //!< Route time in seconds
	TBuint32            mNbElem;            //!< Number of route elements in route
	TB_ROUTE_ELEM     * mElems;             //!< Array of route elements
	CBPlanner::EB_ERROR mError;             //!< Error status (\c NONE if no error)
  TBbool              mDestroyRouteForms; //!< If true forms will be destroyed in destructor

  friend class CBPlannerImp;
  friend class CBRouteSheet;
};

#endif //__CBPLANNER_H__

