// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: geodesy.hpp 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef __GEO_UTILITIES__
#define __GEO_UTILITIES__

#include <cmath>
#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace math{

   namespace geodesy {

#ifndef M_PI
       const double M_PI = std::atan(1.0)*4.0;
#endif
  
   /*!
    *  \enum CoordinateSystem
    *  \brief coordinate system enumeration  
    */
   enum CoordinateSystem {_LLH_,_ECEF_,_LAMBERT93_,_ENU_,_NED_,_NONE_};
	
   /*!
    * \def WGS84_a 
    * \brief semi-major axis of WGS84 ellipsoid
    */
   const double WGS84_a = 6378137.0;
   /*!
    * \def WGS84_e 
    * \brief eccentricity of WGS84 ellipsoid
    */
   const double WGS84_e = 0.0818191913108695;

   /*!
    * \def GRS80_a 
    * \brief  semi-major axis of GRS80 ellipsoid
    */
   const double GRS80_a = 6378137.0;
   /*!
    * \def GRS80_a 
    * \brief eccentricity of GRS80 ellipsoid
    */
   const double GRS80_e =0.0818191910428152;

 
   /**Lambert93 conversion parameters */
   const double LAMBERT93_n=0.725607765053267;
   const double LAMBERT93_c = 11754255.4261;
   const double LAMBERT93_Xs = 700000.0;
   const double LAMBERT93_Ys = 12655612.0499;
   const double LAMBERT93_lon0 = 0.0523598775598299;

   /**Conversion functions*/

   /*!
    * \fn inline boost::numeric::ublas::vector<T> LLH2ECEF(const boost::numeric::ublas::vector<T> &llh, const T &a, const T &e)
    * \brief convert an LLH position to a ECEF position
    * \param llh : ublas vector describing a llh position (latitude, longitude,ellipsoidal height) 
    * \param a : semi-major axis of ellipsoid (by default WGS84 value is used)
    * \param e : ellipsoid eccentricity  (by default WGS84 value is used)
    * \return  ublas vector describing a ecef position (x,y,z)
    */
   template<class T> inline boost::numeric::ublas::vector<T> LLH2ECEF(const boost::numeric::ublas::vector<T> &llh, const T &a=WGS84_a, const T &e=WGS84_e){

    	T N=TranversalRadius(llh[0],a,e);
	boost::numeric::ublas::vector<T> ecef(3);
	ecef[0]=(N+llh[2])*std::cos(llh[0])*std::cos(llh[1]);
	ecef[1]=(N+llh[2])*std::cos(llh[0])*std::sin(llh[1]);
	ecef[2]=(N*(1-std::pow(e,2))+llh[2])*std::sin(llh[0]);

	return ecef;
   }

   /*!
    * \fn  inline boost::numeric::ublas::vector<T> ECEF2LLH(const boost::numeric::ublas::vector<T> &ecef,const T &a, const T &e)
    * \brief convert an ECEF position to a LLH position
    * \param ecef : ublas vector describing a ecef position (x,y,z)
    * \param a : semi-major axis of ellipsoid (by default WGS84 value is used)
    * \param e : ellipsoid eccentricity  (by default WGS84 value is used)
    * \return  ublas vector describing a llh position (latitude, longitude,ellipsoidal height)
    */
   template<class T> inline boost::numeric::ublas::vector<T> ECEF2LLH(const boost::numeric::ublas::vector<T> &ecef,const T &a=WGS84_a, const T &e=WGS84_e){
        boost::numeric::ublas::vector<T> lla(3);
	T P= std::sqrt(pow(ecef[0],2) + pow(ecef[1],2));
	T l0 =std::atan(ecef[2]/(P*(1-a*std::pow(e,2)/std::sqrt(std::pow(ecef[0],2) + std::pow(ecef[1],2) + std::pow(ecef[2],2)))));
	lla[1]= std::atan(ecef[1]/ecef[0]);
	lla[0]= std::atan((ecef[2]/P)/(1-a*std::pow(e,2)*std::cos(l0)/(P*std::sqrt(1-std::pow(e,2)*std::pow(sin(l0),2)))));
	while(std::fabs(lla[0]*180/M_PI-l0*180/M_PI)>std::pow(10.0,-12.0)){
		l0=lla[0];
		lla[0]=std::atan((ecef[2]/P)/(1-a*std::pow(e,2)*std::cos(l0)/(P*sqrt(1-std::pow(e*std::sin(l0),2)))));
	}
	lla[2]=(P/std::cos(lla[0]))-(a/std::sqrt(1-pow(e*sin(lla[0]),2)));
	return lla;
   }

   /*!
    * \fn  inline boost::numeric::ublas::vector<T> ECEF2NTF(const boost::numeric::ublas::vector<T> &ecef)
    * \brief convert an ECEF position to a NTF position
    * \param ecef : ublas vector describing a ecef position (x,y,z)
    * \return  ublas vector describing a ntf position (x,y,z)
    */
   template <class T> inline boost::numeric::ublas::vector<T> ECEF2NTF(const boost::numeric::ublas::vector<T> &ecef){      
       boost::numeric::ublas::vector<T> ntf(3);
       ntf[0]=ecef[0]+168;
       ntf[1]=ecef[1]+60;
       ntf[2]=ecef[2]-320;
       return ntf;
   }

   /*!
    * \fn  inline boost::numeric::ublas::vector<T> NTF2ECEF(const boost::numeric::ublas::vector<T> &ntf)
    * \brief convert an ECEF position to a NTF position
    * \param ntf : ublas vector describing a ntf position (x,y,z)
    * \return  ublas vector describing a ecef position (x,y,z)
    */
    template <class T> inline boost::numeric::ublas::vector<T> NTF2ECEF(const boost::numeric::ublas::vector<T> &ntf){
       boost::numeric::ublas::vector<T> ecef(3);
       ecef[0]=ntf[0]-168;
       ecef[1]=ntf[1]-60;
       ecef[2]=ntf[2]+320;
       return ecef;
   }


   /*!
    * \fn  inline boost::numeric::ublas::matrix<T> C_ECEF2ENU(const T &lat0,const  T &lon0)
    * \brief compute transformation matrix using to convert an ECEF position to a ENU position
    * \param lat0 : reference latitude   
    * \param lon0 : reference longitude 
    * \return  ublas matrix 
    */
    template <class T> inline boost::numeric::ublas::matrix<T> C_ECEF2ENU(const T &lat0,const  T &lon0){
     
        T slat = std::sin(lat0);
        T clat = std::cos(lat0);
        T slon = std::sin(lon0);
        T clon = std::cos(lon0);

        boost::numeric::ublas::matrix<T> C(3,3);
        C(0,0) = -slon;
        C(0,1) = clon;
        C(0,2) = 0.0;

        C(1,0) = -clon * slat;
        C(1,1) = -slon * slat;
        C(1,2) = clat;

        C(2,0) = clon * clat;
        C(2,1) = slon * clat;
        C(2,2) = slat;
   
       return C;
   }

   /*!
    * \fn  inline boost::numeric::ublas::matrix<T> C_ENU2ECEF(const T &lat0, const T &lon0)
    * \brief compute transformation matrix using to convert an ENU position to a ECEF position
    * \param lat0 : reference latitude   
    * \param lon0 : reference longitude 
    * \return  ublas matrix 
    */
  template <class T> inline boost::numeric::ublas::matrix<T> C_ENU2ECEF(const T &lat0, const T &lon0){
       T clat = std::cos(lat0);
       T slat = std::sin(lat0);
       T clon = std::cos(lon0);
       T slon = std::sin(lon0);

       boost::numeric::ublas::matrix<T> C(3,3);
       C(0,0) = -slon;
       C(0,1) = -clon * slat;
       C(0,2) = clon * clat;

       C(1,0) = clon;
       C(1,1) = -slon * slat;
       C(1,2) = slon * clat;

       C(2,0) = 0.0;
       C(2,1) = clat;
       C(2,2) = slat;
      
      return C;
   }

   /*!
    * \fn inline boost::numeric::ublas::matrix<T> C_ECEF2NED(const T &lat0,const  T &lon0)
    * \brief compute transformation matrix using to convert an ECEF position to a NED position
    * \param lat0 : reference latitude   
    * \param lon0 : reference longitude 
    * \return  ublas matrix 
    */
   template <class T> inline boost::numeric::ublas::matrix<T> C_ECEF2NED(const T &lat0,const T &lon0){
    
        T clat = std::cos(lat0);
        T clon = std::cos(lon0);
        T slat = std::sin(lat0);
        T slon = std::sin(lon0);

        boost::numeric::ublas::matrix<T> C(3,3);

        C(0,0) = -slat * clon;
        C(0,1) = -slat * slon;
        C(0,2) = clat;

        C(1,0) = -slon;
        C(1,1) = clon;
        C(1,2) = 0.0;

        C(2,0) = -clat * clon;
        C(2,1) = -clat * slon;
        C(2,2) = -slat;

       return C;
    }
 
   /*!
    * \fn  inline boost::numeric::ublas::matrix<T> C_NED2ECEF(const T &lat0, const T &lon0)
    * \brief compute transformation matrix using to convert NED position to a ECEF position
    * \param lat0 : reference latitude   
    * \param lon0 : reference longitude 
    * \return  ublas matrix 
    */
    template <class T> inline boost::numeric::ublas::matrix<T> C_NED2ECEF(const T &lat0, const T &lon0){

        T clat = std::cos(lat0);
        T clon = std::cos(lon0);
        T slat = std::sin(lat0);
        T slon = std::sin(lon0);

        boost::numeric::ublas::matrix<T> C(3,3);

        C(0,0) = -slat * clon;
        C(1,0) = -slat * slon;
        C(2,0) = clat;

        C(0,1) = -slon;
        C(1,1) = clon;
        C(2,1) = 0.0;

        C(0,2) = -clat * clon;
        C(1,2) = -clat * slon;
        C(2,2) = -slat;

      return C;
    }

   /*!
    * \fn  inline boost::numeric::ublas::vector<T> ECEF2TANGENT (const boost::numeric::ublas::matrix<T> & C, const boost::numeric::ublas::vector<T> & P ,const boost::numeric::ublas::vector<T> Ref )
    * \brief convert an ECEF position to a ENU or NED position
    * \param C : transformation matrix 
    * \param P : ECEF position  
    * \param Ref : reference position in ECEF frame 
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> 
    ECEF2TANGENT (const boost::numeric::ublas::matrix<T> & C, const boost::numeric::ublas::vector<T> & P ,const boost::numeric::ublas::vector<T> Ref ){
      return   prod(C,(P-Ref));
    }

   /*!
    * \fn inline boost::numeric::ublas::vector<T> TANGENT2ECEF (const boost::numeric::ublas::matrix<T> & C, const boost::numeric::ublas::vector<T> & P ,const boost::numeric::ublas::vector<T> Ref )
    * \brief convert an ENU or NED position to an ECEF position
    * \param C : transformation matrix 
    * \param P : ENU or NED position  
    * \param Ref : reference position in ECEF frame 
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> 
    TANGENT2ECEF (const boost::numeric::ublas::matrix<T> & C, const boost::numeric::ublas::vector<T> & P ,const boost::numeric::ublas::vector<T> Ref ){
      return Ref+prod(C,P);
    }

   /*!
    * \fn inline boost::numeric::ublas::vector<T> ENU2NED(const boost::numeric::ublas::vector<T> &enu)
    * \brief convert an ENU position to an NED position
    * \param enu : ENU  position  
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> ENU2NED(const boost::numeric::ublas::vector<T> &enu){
      boost::numeric::ublas::vector<T> ned(3);
      ned[0]=enu[1];
      ned[1]=enu[0];
      ned[2]=-enu[2];
      return ned;
    } 

   /*!
    * \fn inline boost::numeric::ublas::vector<T> NED2ENU(const boost::numeric::ublas::vector<T> &ned)
    * \brief convert an NED position to an ENU position
    * \param ned : NED  position  
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> NED2ENU(const boost::numeric::ublas::vector<T> &ned){
       return ENU2NED(ned);
    }

 
   /*!
    * \fn inline boost::numeric::ublas::vector<T> LLH2LAMBERT(const boost::numeric::ublas::vector<T> &llh, T lon0 ,T e, T n, T c ,T Xs, T Ys)
    * \brief convert an LLH position to a LAMBERT position
    * \param llh : LLH position
    * \param lon0 : reference longitude
    * \param e : ellipsoid eccentricity
    * \param n :
    * \param c :
    * \param Xs : false easting
    * \param Ys : false northing
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> LLH2LAMBERT(const boost::numeric::ublas::vector<T> &llh, T lon0 ,T e, T n, T c ,T Xs, T Ys){; 
       boost::numeric::ublas::vector<T> lambert(3);
       T latiso= std::log(std::tan((M_PI / 4) + (llh[0] / 2)) * std::pow((1 - e * std::sin(llh[0])) / (1 + e * std::sin(llh[0])),e / 2));
       lambert[0] = Xs + c*std::exp(-n*latiso)*std::sin(n*(llh[1]-lon0));
       lambert[1] = Ys - c*std::exp(-n*latiso)*std::cos(n*(llh[1]-lon0));
       return lambert;
    }
 

   /*!
    * \fn inline boost::numeric::ublas::vector<T> LLH2LAMBERT93(const boost::numeric::ublas::vector<T> &llh)
    * \brief convert an LLH position to a LAMBERT 93 position
    * \param llh : llh position
    * \return  ublas vector 
    */
   template <class T> inline boost::numeric::ublas::vector<T> LLH2LAMBERT93(const boost::numeric::ublas::vector<T> &llh){
//      boost::numeric::ublas::vector<T> ecef=LLH2ECEF<T>(llh);
//      boost::numeric::ublas::vector<T> ntf=ECEF2NTF<T>(ecef);
//      boost::numeric::ublas::vector<T> llhntf=ECEF2LLH<T>(ntf,GRS80_a,GRS80_e);
     return LLH2LAMBERT<T>(llh,LAMBERT93_lon0 ,GRS80_e, LAMBERT93_n, LAMBERT93_c , LAMBERT93_Xs, LAMBERT93_Ys);
   } 


   /*!
    * \fn inline boost::numeric::ublas::vector <T> LAMBERT2LLH(const boost::numeric::ublas::vector<T> &lambert, T lon0, T e , T n, T c, T Xs ,T Ys )
    * \brief convert an LLH position to a LAMBERT position
    * \param lambert : lambert position
    * \param lon0 : reference longitude
    * \param e : ellipsoid eccentricity
    * \param n :
    * \param c :
    * \param Xs : false easting
    * \param Ys : false northing
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> LAMBERT2LLH(const boost::numeric::ublas::vector<T> &lambert, T lon0, T e , T n, T c, T Xs ,T Ys ){
      boost::numeric::ublas::vector<T> llh(3);

      T latiso=std::log(c/std::abs(std::sqrt(std::pow(lambert[0]-Xs,2)+std::pow(lambert[1]-Ys,2))))/n;
      llh[0]=2*std::atan(std::exp(latiso))-M_PI/2;
      llh[1]=lon0+std::atan(-(lambert[0]-Xs)/(lambert[1]-Ys))/n;
      T l0=llh[0]+1;

      while(std::abs(llh[0]-l0)>std::pow(10.0,-12.0)){
        l0=llh[0];
        llh[0]=2 * std::atan(std::pow((1 + e * std::sin(l0)) / (1 - e * std::sin(l0)), e / 2)*std::exp(latiso)) - M_PI / 2;
      }
      return llh;
    }
  
   /*!
    * \fn inline boost::numeric::ublas::vector<T> LAMBERT932LLH(const boost::numeric::ublas::vector<T> &lambert)
    * \brief convert an LAMBERT93 position to a LLH position
    * \param lambert : lmabert 9 position
    * \return  ublas vector 
    */
    template <class T> inline boost::numeric::ublas::vector<T> LAMBERT932LLH(const boost::numeric::ublas::vector<T> &lambert){
      return LAMBERT2LLH<T>(lambert, LAMBERT93_lon0 ,GRS80_e, LAMBERT93_n, LAMBERT93_c , LAMBERT93_Xs, LAMBERT93_Ys);
      //boost::numeric::ublas::vector<T> llhntf=LAMBERT2LLHCARTO<T>(lambert, LAMBERT93_lon0 ,GRS80_e, LAMBERT93_n, LAMBERT93_c , LAMBERT93_Xs, LAMBERT93_Ys);
      //boost::numeric::ublas::vector<T> ecefntf=LLH2ECEF<T>(llhntf);
      //boost::numeric::ublas::vector<T> ecef=NTF2ECEF<T>(ecefntf);
      //return ECEF2LLH<T>(ecef);
    } 

   /*!
    * \fn inline T MeridionalRadius(const T &latitude,const T &a, const T &e)
    * \brief compute the prime vertical curvature radius
    * \param latitude : a latitude 
    * \param a : semi-major axis of ellipsoid (by default WGS84 value is used)
    * \param e : ellipsoid eccentricity  (by default WGS84 value is used)
    * \return  ublas vector 
    */
   template<class T> inline T MeridionalRadius(const T &latitude,const T &a=WGS84_a, const T &e=WGS84_e){
       return a/(std::pow(1-std::pow(e*std::sin(latitude),2),1.5));
   }

   /*!
    * \fn inline T TranversalRadius(const T &latitude,const T &a, const T &e)
    * \brief compute the prime horizontal curvature radius
    * \param latitude : a latitude 
    * \param a : semi-major axis of ellipsoid (by default WGS84 value is used)
    * \param e : ellipsoid eccentricity  (by default WGS84 value is used)
    * \return  ublas vector 
    */
   template<class T> inline T TranversalRadius(const T &latitude,const T &a=WGS84_a, const T &e=WGS84_e){
      return a/std::sqrt(1-std::pow(e*std::sin(latitude),2));
   }


};
};
#endif



