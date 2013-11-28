#ifndef TUBE_HPP
#define TUBE_HPP

#ifdef TUBE_EXPORTS
#define TUBE_API __declspec(dllexport)
#else
#define TUBE_API __declspec(dllimport)
#endif

#include "../../Include/GPSCOORD.h"

//pour afficher la position
//et transmettre les noms des fichiers (plus utilisé dans les nouveaux devs)
TUBE_API void senddata(gpsdata);
TUBE_API void recievedata (gpsdata &);

#endif