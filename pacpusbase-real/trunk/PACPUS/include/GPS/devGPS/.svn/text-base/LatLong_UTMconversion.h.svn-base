//LatLong- UTM conversion..h
//definitions for lat/long to UTM and UTM to lat/lng conversions

/*Reference ellipsoids derived from Peter H. Dana's website- 
http://www.utexas.edu/depts/grg/gcraft/notes/datum/elist.html
Department of Geography, University of Texas at Austin
Internet: pdana@mail.utexas.edu
3/22/95

Source
Defense Mapping Agency. 1987b. DMA Technical Report: Supplement to Department of Defense World Geodetic System
1984 Technical Report. Part I and II. Washington, DC: Defense Mapping Agency
*/


#include <string.h>

#ifndef LATLONGCONV
#define LATLONGCONV

void LLtoUTM(int ReferenceEllipsoid, const double Lat, const double Long, 
			 double &UTMNorthing, double &UTMEasting, char* UTMZone);
void UTMtoLL(int ReferenceEllipsoid, const double UTMNorthing, const double UTMEasting, const char* UTMZone,
			  double& Lat,  double& Long );
char UTMLetterDesignator(double Lat);


class Ellipsoid
{
public:
	Ellipsoid(){};
	Ellipsoid(int Id, char* name, double radius, double ecc)
	{
		id = Id; ellipsoidName = name; 
		EquatorialRadius = radius; eccentricitySquared = ecc;
	}

	int id;
	char* ellipsoidName;
	double EquatorialRadius; 
	double eccentricitySquared;  

};



#endif
