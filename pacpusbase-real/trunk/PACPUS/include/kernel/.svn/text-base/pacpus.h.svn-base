#ifndef PACPUS_H
#define PACPUS_H

#include "err.h"
#include "road_time.h"
#include "../structure/structure_gps.h"

#define PACPUS_PI       3.1415926

// Export macro for PacpusLib DLL for Windows only
#ifdef WIN32
#   ifdef PACPUSLIB_EXPORTS
//  make DLL
#       define PACPUSLIB_API __declspec(dllexport)
#   else
//      use DLL
#       define PACPUSLIB_API __declspec(dllimport)
#   endif
#else
//  On other platforms, simply ignore this
#   define PACPUSLIB_API
#endif

struct donnees_gps{
    long  ind_qualite;
    double x, y;
    double lon, lat;
    float a,b,phi,sigma_lat,sigma_lon;
    road_time_t time;
    double alt_msl,d_geoidal;
};

struct donnees_abs_zy{        
  float dArD, dArG;
  float speed;
	road_time_t time;
};

struct donnees_gyro{
  // les mesures sont prises par rapport au point C
  // position de la centrale inertielle
  // vitesse de lacet (rad.s-1) dans le repère de la masse suspendue
  float psi_s;
  road_time_t time;
};

// Definition of the structure which will be sent for each positioning
// requests -> MapMatching.cpp 
struct s_MatchedPosition
{
  int				state;      /* Etat du serveur de position absolue hybridée*/
  double			x_match;	/* Position Matchée         */
  double			y_match;	/*  en x et y				*/
  double			x;			/* Position du véhicule		*/
  double			y;			/*	en x et y				*/
  double			theta;		/* cap (par rapport à l'est) dans le système de la carte */
  double			v;			/* vitesse horizontale par rapport à la terre  */
  unsigned long	ID;			/* ID de la route à laquelle appartient la position matchée */
  road_time_t		time;
  int				way;		/* Sens de la route parcourue 1=W2E, 2=E2W*/
  double			dist;		/* abscisse curviligne par rapport au début de la route */
  double			pxx, pyy, pxy; /* covariance de l'erreur en position absolue*/
  double			ptheta;		/*covariance de l'erreur en cap*/
  double      error; 
  donnees_gyro gyro;  
  donnees_abs_zy odo; 
};

#endif // PACPUS_H
