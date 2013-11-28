/*********************************************************************
//  created:    2007/01/24 - 14:42
//  filename:   MapRoadExtraction.h
//
//  author:     Gerald Dherbomez 
//              Copyright Heudiasyc UMR UTC/CNRS 6599
// 
//  version:    $Id: MapRoadExtraction.h 299 2007-10-23 16:11:29Z gdherbom $
//
//  purpose:    Use this class to extract roads from the map. 
//              The provided functions enable to access to the shared 
//              memory or to decode the cache encoded in a string
*********************************************************************/


#ifndef _MAPROADEXTRACTION_H_
#define _MAPROADEXTRACTION_H_


#include "PacpusTools/ShMem.h"
#include "MapData.h"
#include <qstring.h>



class MapRoadExtraction
{
public:
	MapRoadExtraction( char * shMemName, int size);
	~MapRoadExtraction();
  
  // Return the size of the roads structure in bytes
  int size(hds_polyline* roads, int nbRoads); 

  // Write the extracted roads in shared memory
  void setRoads(hds_polyline* roads, int nbRoads); 
  
  // Method used to recover the roads structure of the shared memory
  // You must provide a structure 'roads' correctly allocated to the function
  // This method do a lot of memory allocation : geometry_pts, id_connex_origin
  // and id_connex_end for each road. 
  // So don't forget to free memory with the freeRoads method
  int getRoads(hds_polyline* roads); 

  // Use this method to uninitialize the memory
  void freeRoads(hds_polyline * addr, int nbRoads);

  // Return the number of roads in shared memory
  int nbRoads();

  // Return the number of roads in the roadString cache
  int nbRoads(QString roadString);

  // Display the road structure to stdout
  void printRoads(hds_polyline* roads, int nbRoads); 
  
  // convert the roads structure in QString
  QString hdsPolyline2String(hds_polyline* roads, int nbRoads); 

  // fill the hds_polyline from a string created during the road extraction
  bool string2HdsPolyline( QString roadString, hds_polyline* roads );

protected:
	
private:
  // Dynamic shared memory that contains the extracted road structure
  ShMem *roadExtractionShMem;

};





#endif
