#include <math.h>
#define pi 3.141592653589793
double atanh(double  z)
{
	return (0.5 * log((z+1)/(1-z)));
}

double  abs_me(double x)
{
	if(x<0) x=-x;
	return x;
}

//transformation des longitudes tatitudes en Lambert93
void lonlattolam(double lon, double lat, double & lam93x, double & lam93y)
	{
		double GRS_a = 6378137;
		double GRS_f = 1./298.257222101;

		double GRS_b = GRS_a*(1-GRS_f);
		double GRS_bb= GRS_b*GRS_b;
		double GRS_aa= 40680631590769.;
		double GRS_e = sqrt((GRS_aa - GRS_bb) / (GRS_aa));

		double n = 0.725607765053267;
		double C = 11754255.4261;
		double XS = 700000;
		double YS = 12655612.0499;

		double latiso;
		latiso = atanh(sin(lat)) - GRS_e*atanh(GRS_e*sin(lat));
		double gamma;
		gamma = (lon - 0.0523598775598299)*n;
		double R;
		R = C * exp(-n*latiso);

		lam93x = R *sin(gamma)+XS;
		lam93y = -R *cos(gamma)+YS;
		//printf("x: %.20lf\n y: %.20lf\n",lam93x,lam93y);

	}



//Transformation des coordonnees de Lambert93 en Longitude lattitude

void lamtolonlat(double lamx, double lamy, double & lon, double & lat)
{

	double GRS_a = 6378137;
	double GRS_f = 1./298.257222101;
	double GRS_b = GRS_a*(1-GRS_f);
	double GRS_bb= GRS_b*GRS_b;
	double GRS_aa= 40680631590769.;
	double GRS_e = sqrt((GRS_aa - GRS_bb) / (GRS_aa));

	double n = 0.725607765053267;
	double C = 11754255.4261;
	double XS = 700000;
	double YS = 12655612.0499;


	//lamx = lamx-700000;
	//lamy = lamy-12655612.0499;

	double gamma;
	gamma = atan(-(lamx-700000)/(lamy-12655612.0499));


	lon = gamma/0.725607765053267 + 0.0523598775598299;
	double R;
	R = sqrt((lamx-700000) * (lamx-700000) + (lamy-12655612.0499) * (lamy-12655612.0499));

	double latiso;
	latiso = log((11754255.4261)/R)/(0.725607765053267);

	double phiNew, phiOld;
	phiOld =1;
	phiNew= asin (tanh ( latiso + GRS_e * atanh(GRS_e * sin(phiOld))));
	//printf("\nphiNew: %.20lf",phiNew);
	while (abs_me(phiOld-phiNew) > 1e-10)
	{

		if(abs_me(phiOld-phiNew) > 1e-10)
		{

			phiOld = phiNew;
			phiNew = asin(tanh(latiso+GRS_e*atanh(GRS_e*sin(phiOld))));
		}
		else
			phiOld = phiNew;
	}

	lat = phiNew;

}
