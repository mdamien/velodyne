#ifndef RUE_DATA_H
#define RUE_DATA_H

# include "../../include/BeNomad/BTypes.h"

//Structure décrivant 
//- la géométrie d'une route
//- la connexité avec ses voisines
//- quelques attributs (name, speed limit, driving_direction
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

//Pour le passage de paramètres à l'extraction de routes
typedef struct
{
TB_2D_LONGPOINT Point;
TBuint32 Radius;
} extract_roads_dll_parameter;

#endif