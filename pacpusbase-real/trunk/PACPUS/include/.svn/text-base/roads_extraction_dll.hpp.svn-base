#ifndef ROADS_EXTRACTION_DLL_HPP
#define ROADS_EXTRACTION_DLL_HPP

#ifdef ROADS_EXTRACTION_DLL_EXPORTS
#define ROADS_EXTRACTION_DLL_API __declspec(dllexport)
#else
#define ROADS_EXTRACTION_DLL_API __declspec(dllimport)
#endif

#include "../../include/rue_data.h"

ROADS_EXTRACTION_DLL_API void put_particles(TB_2D_LONGPOINT *,unsigned long);
ROADS_EXTRACTION_DLL_API TB_2D_LONGPOINT * get_particles(unsigned long*);

ROADS_EXTRACTION_DLL_API extract_roads_dll_parameter * get_param();
ROADS_EXTRACTION_DLL_API void set_roads(long nb_roads,hds_polyline *param);
ROADS_EXTRACTION_DLL_API hds_polyline * get_roads(long x,long y, unsigned long radius,unsigned long *nbroads);
ROADS_EXTRACTION_DLL_API void freeRoads(hds_polyline * addr, int nbRoads); 

#endif