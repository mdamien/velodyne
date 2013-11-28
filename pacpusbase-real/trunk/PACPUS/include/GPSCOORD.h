typedef struct
{
	double lon, lat, alt_msl, d_geoidal;
	int type; //code de la requete échangée
	char nom[32]; //xml ou svs
} gpsdata;