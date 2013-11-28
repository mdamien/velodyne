/*==========================================================  (-*- C++ -*-)
 *
 * @file CBRoadNetwork.h
 * 
 * @version  $Id: CBRoadNetwork.h,v 1.24 2005/07/05 19:26:34 wkunkel Exp $ 
 * 
 * @author  David Labrousse
 *
 * @copyright  (c) 2002-2004 BeNomad S.A.R.L., All Rights Reserved
 *
 * BeNomad confidential file protected by international copyright laws
 * UNAUTHORIZED ACCESS, USE, REPRODUCTION OR DISTRIBUTION IS PROHIBITED.
 *
 *========================================================================*/

#ifndef __CBROADNETWORK_H__
#define __CBROADNETWORK_H__

/*!
  @file CBRoadNetwork.h
	CBRoadNetwork class definition.
*/

#include "BTypes.h"

class CBSVSMgr;
class CBRoadNetworkImp;


/**
 * @class CBRoadNetwork
 *
 * The CBRoadNetwork class defines a set of inter-connected road networks (one network per SVS).
 * This class is used by class #CBPlanner for route computation.
 *
 * @note This class supports arrival or deletion of SVS file(s) from the #CBSVSMgr (This means that
 * you do not need to call the #Build method each time you add a new SVS file).
 *
 * 
 */
class BPLN_EXPORT CBRoadNetwork
{
public:

	/**
	 * @enum EB_TRANSP_MODE
	 * This enum defines all the possible transportation modes.
	 */
	enum EB_TRANSP_MODE {
    EB_PEDESTRIAN     = 0, //!< Pedestrian
	  EB_PASSENGER_CAR  = 1, //!< Passenger car (tourist car)
	  EB_TAXI           = 2, //!< Taxi
	  EB_PUBLIC_BUS     = 3, //!< Public bus
	  EB_DELIVERY_TRUCK = 4, //!< Delivery truck
	  EB_BICYCLE        = 5, //!< Bicycle
    EB_EMERGENCY_VEH  = 6  //!< Emergency vehicle
	};

  /**
   * Constructor.
   * @param inSVSMgr SVS manager to build road networks from (see #CBSVSMgr)
   */
  CBRoadNetwork(CBSVSMgr * inSVSMgr);

  /**
   * Destructor.
   */
  ~CBRoadNetwork(void);

  /**
   * Builds a set of inter-connected road networks : one network per SVS in SVS manager.
   * @param inMinimizeMemory Flag that allows you to minimize considerably the memory footprint
   * required to build all inter-connected graphs (mandatory for development on PDA devices).
   * If you set this flags to \c true, a "xxxx.nod" file will be created (only the first time)
   * for each SVS file (xxxx = SVS filename). So make sure that the support where are installed
   * all SVS files is writable and has sufficient space (roughly 20% of SVS data volume).
   * @param inConnectFile An optional name of a <I>Network Connections File (.ncf)</I> which may be used to
   * speed up the Road Network construction. This file can be generated with the NCF-gen.exe tool which may also
   * be used to generate the ".nod" files.
   * @return \c true if at least one network was built, \c false otherwise
   * @since 1.5.2 : Added \a inNetworkFile argument.
   */
  TBbool Build(TBbool inMinimizeMemory = false, const TBchar * inNetworkFile = NULL);

  /**
   * Checks if \a inTranspMode is defined for all SVS in network's SVS manager.
   * @param inTranspMode Transportation mode to check (see #EB_TRANSP_MODE)
   * @return \c true if \a inTranspMode is defined for all SVS in network's SVS manager, \c false otherwise
   */
  TBbool IsValid(const EB_TRANSP_MODE& inTranspMode) const;
  
  /**
   * \internal
   */
  inline const CBRoadNetworkImp * GetRoadNetworkImp(void) const { return mImp; }
    
private:

  CBRoadNetworkImp * mImp;
};

#endif //__CBROADNETWORK_H__

