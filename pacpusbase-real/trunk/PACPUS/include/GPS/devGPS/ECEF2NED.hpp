#ifndef H_ECEF2NED_HPP
#define H_ECEF2NED_HPP


#include "geometry.hpp"                   // DEG_TO_RAD
#include "Matrix.hpp"
#include "Position.hpp"
#include "MatrixOperators.hpp"


class ECEF2NED 
{
public:

    /// Default constructor.
    ECEF2NED() : refLat(0.0), refLon(0.0)
    {
        Prepare();
    };

    ECEF2NED(const double& lat, const double& lon)
    {
        setLatLon(lat, lon);
    };


	ECEF2NED(const gpstk::Position& refPos)
    {
		NEDcenter = refPos;
        setLatLon(refPos.getGeodeticLatitude(), refPos.getLongitude());
    };

	gpstk::Position getCenter() const
	{return NEDcenter;};

    /// Method to get the latitude of the reference point, in degrees.
    virtual double getLat() const
    {
        return (refLat*gpstk::RAD_TO_DEG);
    };


    /// Method to get the longitude of the reference point, in degrees.
    virtual double getLon() const
    {
       return (refLon*gpstk::RAD_TO_DEG);
    };

	virtual void setCenter(const gpstk::Position& refPos)
	{
		NEDcenter = refPos;
		refLat = (refPos.getGeodeticLatitude()*gpstk::DEG_TO_RAD);
		refLon = (refPos.getLongitude()*gpstk::DEG_TO_RAD);
        Prepare();
	};

	virtual void setLatLon(const double& lat, const double& lon)
    {
        // Don't allow latitudes out of the -90/+90 interval
        if ( (lat > 90.0) || (lat < -90.0) ) refLat = 0.0; else refLat = (lat*gpstk::DEG_TO_RAD);
		NEDcenter.setGeodetic(lat,lon,0);
		refLon = (lon*gpstk::DEG_TO_RAD);
        Prepare();
    };


    /// Destructor.
    virtual ~ECEF2NED() {};

	gpstk::Vector<double> rotate(gpstk::Vector<double> input);

	gpstk::Vector<double> rotate(double Xecef, double Yecef, double Zecef);

	gpstk::Vector<double> rotateENU(gpstk::Vector<double> input);

	gpstk::Vector<double> rotateENU(double Xecef, double Yecef, double Zecef);

	gpstk::Vector<double> rotateInv(gpstk::Vector<double> input);

	gpstk::Vector<double> transform(gpstk::Vector<double> input);

	gpstk::Vector<double> transform(double Xecef, double Yecef, double Zecef);

	gpstk::Vector<double> transformENU(gpstk::Vector<double> input);
	
	gpstk::Vector<double> transformENU(double Xecef, double Yecef, double Zecef);


private:


    /// Latitude of the reference point (topocentric reference), in radians.
    double refLat;

    /// Longitude of the reference point (topocentric reference), in radians.
    double refLon;

	gpstk::Position NEDcenter;

    /// Rotation matrix.
	gpstk::Matrix<double> rotationMatrix;


    /// This method builds the rotation matrix according to refLat and refLon values.
	virtual void Prepare();

}; // class ECEF2NED


#endif
