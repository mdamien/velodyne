/*********************************************************************
// created:    2006/04/24 - 9:30
// filename:   MapEngine.h
//
// author:     Gerald Dherbomez
// 
// version:    $Id: MapEngine.h 300 2007-10-24 08:30:50Z gdherbom $
// 
// purpose:    Class which enables to work with BeNomad Mapping SDK
*********************************************************************/


#ifndef _MAPENGINE_H_
#define _MAPENGINE_H_


#include "BeNomad/BTypes.h"

#include "MapFrontEnd.h"


// Forward declarations
class CBGraphicChart;
class CBSVSMgr;



/*
//Pour le passage de param�tres � l'extraction de routes
typedef struct
{
TB_2D_LONGPOINT Point;
TBuint32 Radius;
} extract_roads_dll_parameter;
*/

class MapEngine 
{   
public:
  MapEngine();
  ~MapEngine();

  // Accessors
  inline const CBGraphicChart * getGraphicChart(void) const { return graphicChart_; }
  inline CBSVSMgr             * getSvsMgr(void)       const { return svsMgr_;       }
  inline MapFrontEnd          * getMapFrontEnd(void)  const { return mapFrontEnd_;  }

  bool initialize(const char * graphicChartFileName); 
  
  //unsigned long dist_coord_pt_segment(TB_2D_LONGPOINT PtCentral,TB_2D_LONGPOINT PtA,TB_2D_LONGPOINT PtB);
  int rechercheroute_dll(TB_2D_LONGPOINT PtCentral, TBuint32 inRadius, int *road_cache_size, int socketId = 0);
  void rechercheroute(TB_2D_LONGPOINT PtPremier, TB_2D_LONGPOINT PtSecond );
  
protected:
  CBGraphicChart * graphicChart_;
  CBSVSMgr * svsMgr_; 
  
  MapFrontEnd *mapFrontEnd_; 
  
  
private:
  road_time_t tmin_; 
  road_time_t tmax_; 
  

};
#endif
