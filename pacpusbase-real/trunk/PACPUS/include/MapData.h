/*********************************************************************
// created:    2006/05/06 - 18:28
// filename:   MapData.h
//
// author:     Gerald Dherbomez
// 
// version:    $Id: MapData.h 300 2007-10-24 08:30:50Z gdherbom $
//
// purpose:    identification of exchanged data between clients and 
//             server
*********************************************************************/


#ifndef _MAPDATA_H_
#define _MAPDATA_H_



#define MAP_EVENT_BASE  65000

// need to suppress this include at term
#include "BeNomad/BTypes.h"
#include "kernel/pacpus.h"




// List of class Id of displayed objects in the graphical chart (XML File)
// Standard
#define CLASS_BLUEPOINT                 0
#define CLASS_REDPOINT                  0
#define CLASS_YELLOWPOINT               0
#define CLASS_GREENPOINT                0
// Specific
#define CLASS_VEHICLE                   1230140
#define CLASS_VEHICLE_TRACE             0
#define CLASS_MATCHED_POSITION          900001 
#define CLASS_MATCHED_POSITION_TRACE    0
#define CLASS_GPS                       10005
#define CLASS_GPS_TRACE                 0
#define CLASS_POSE                      1230120
#define CLASS_POSE_TRACE                0



// enumeration of the requests id known by the map server
enum MAP_DATA
{
  XY_VEHICLE_POSITION =           1,
  XY_MATCHED_POSITION =           2, 
  XY_GPS =                        3,
  XY_POINT =                      4,
  XY_POSE =                       5,
  ROADS_EXTRACTION_REQUEST =      20, 
  ROADS_EXTRACTION_OK =           21, 
  ROADS_EXTRACTION_FAILED =       22
};


// Structure of the vehcle objects in the map
// use this to display : 
// - the car position
// - the matched position 
// - the gps position 
// - the pose of the filter
typedef struct {
  long x;                 // Position x, y in centimeters
  long y;
  float heading;          // angle in radians 
  float ellipseWidth;     // ellipse dimensions in meters
  float ellipseHeight;    // width = 0x & heigth = 0y
  float ellipseAngle;     // angle in radians | 0rad => 0x and sense+ => clock-wise
} VEHICLE_POSITION;


// Structure of a point or object to display
// you must specify the class identifier relatively to  
// the graphical chart (xml file) of the Benomad SDK 
typedef struct {
  long x; 
  long y; 
  short xmlClassId; 
} OBJECT_POSITION; 


// Structure containing the parameters of a road extraction request
// x, y in centimeters, r in meter
typedef struct {
  unsigned long x; 
  unsigned long y; 
  unsigned long r;
} ROADS_EXTRACTION_AREA;

// Strcuture used by the MapServerSocketInterface to communicate with MapMainWindow
// socketId is the socket identifier of the emitter interface for the response
typedef struct {
  ROADS_EXTRACTION_AREA area; 
  int socketId; 
} ROADS_EXTRACTION_AREA_REQUEST;


// Structure containing:  
//- the road geometry
//- the connexity of each road with the others
//- some attributes (name, speed limit, driving_direction) 
typedef struct
{
	unsigned long  id;
	char name[4];
	unsigned long speed_limit;
	unsigned long driving_direction; //verifier avec Benomad
	unsigned long graph_number;
	unsigned long nb_geometry_pts;
	TB_2D_LONGPOINT *geometry_pts;
	unsigned long nb_connex_origin;
	unsigned long *id_connex_origin;
	unsigned long nb_connex_end;
	unsigned long *id_connex_end;
} hds_polyline;


#endif
