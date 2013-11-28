// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: utilities.hpp 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__


namespace math {

 namespace utility {


   /*!
    * \fn inline  std::vector<T> LineCircleIntersection(const boost::numeric::ublas::vector<T> & A,const boost::numeric::ublas::vector<T> & B, const boost::numeric::ublas::vector<T> & C,const double R)
    * \brief Compute points of intersection of circle and line defined  through two poinst A and B
    * \param A : a point of the line
    * \param B : a point of the line
    * \param C : 
    * \param R : circle radius
    * \return  a list of abscissas with respect of point A
    */
    template <class T> inline  std::vector<T> LineCircleIntersection(const boost::numeric::ublas::vector<T> & A,    
                                                                       const boost::numeric::ublas::vector<T> & B,
                                                                       const boost::numeric::ublas::vector<T> & C,
                                                                       const double R){
           std::vector<T> intersection;
           
           double alpha = (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]);
           double norm = std::sqrt(alpha);
           double beta = 2 *(B[0]-A[0])*(A[0]-C[0]) + (B[1]-A[1])*(A[1]-C[1]);
           double gamma = A[0]*A[0] + A[1]*A[1] + C[0]*C[0] + C[1]*C[1] - 2*(A[0]*C[0] + A[1]*C[1] ) - R*R;
           double delta = beta*beta - 4*alpha*gamma;

           if(delta>0){
              intersection.push_back( (-beta -sqrt(delta))/(2*norm) );
              intersection.push_back( (-beta +sqrt(delta))/(2*norm) );
           }

           return intersection;
    }

   /*!
    * \fn inline  std::vector<T> SegmentCircleIntersection(const boost::numeric::ublas::vector<T> & A,const boost::numeric::ublas::vector<T> & B, const boost::numeric::ublas::vector<T> & C,const double R)
    * \brief Compute points of intersection of circle and segment defined  through two poinst A and B
    * \param A : a point of the line
    * \param B : a point of the line
    * \param C : 
    * \param R : circle radius
    * \return  a list of abscissas with respect of point A and in taking account the hypothesis abscissas in [A,B]
    */
    template <class T> inline  std::vector<T> SegmentCircleIntersection(const boost::numeric::ublas::vector<T> & A,    
                                                                       const boost::numeric::ublas::vector<T> & B,
                                                                       const boost::numeric::ublas::vector<T> & C,
                                                                       const double R){


           std::vector<T> intersection;
           double  alpha = (B[0] - A[0]) * (B[0] - A[0]) + (B[1] - A[1]) * (B[1] - A[1]);
           double norm = std::sqrt(alpha);
           double  beta  = 2 * ((B[0] - A[0]) * (A[0] - C[0]) + (B[1] - A[1]) * (A[1] - C[1]));
           double  gamma = A[0] * A[0] + A[1] * A[1] + C[0] * C[0] + C[1] * C[1] - 2 * (A[0] * C[0] + A[1] * C[1]) - R * R;
          
           double delta = beta*beta - 4*alpha*gamma;

           if(delta>0){
              intersection.push_back( (-beta -sqrt(delta))/(2*norm) );
              intersection.push_back( (-beta +sqrt(delta))/(2*norm) );

               if(intersection[0]<1 && intersection[1]>0){
                   if(intersection[0] <0 ) intersection[0]=0;
                   if(intersection[1] >norm) intersection[1]=norm;
               }else{
                intersection.clear();
              }
           }


          return intersection;
    }

   /*!
    * \fn inline boost::numeric::ublas::vector<RealType> Cov2Ellipse(const RealType & pxx,const RealType & pxy,const RealType & pyy,const RealType &proba)
    * \brief Convert 2D covariance to a ellipse parameters
    * \param pxx : variance X
    * \param pxy : covariance XY
    * \param pyy : variance Y
    * \param proba : percentage 
    * \return  ublas vector  containing semi-major axis, semi-minor axis and orientation of the ellipse
    */
    template <class RealType> inline boost::numeric::ublas::vector<RealType> Cov2Ellipse(const RealType & pxx,const RealType & pxy,const RealType & pyy,const RealType &proba){

        boost::numeric::ublas::vector<RealType> ellipse(3);

        // le scalaire "k" definit l'ellipse avec l'equation :(x-mx)T*(1/P)*(x-mx)=k^2
        double k=sqrt(-2*log(1-proba));
  
        // coeficient de correlation
        double ro = pxy / sqrt(pxx * pyy);
        if ( fabs( ro ) > 1 ) 
	  {
	    std::cout << "ro=" << ro << "pxx=" << pxx << "pxy=" << pxy << "pyy=" << pyy << std::endl; 
	    throw math_error("Cov2Ellipse: correlation coefficient is not included between -1 and 1. Covariance matrix is not defined positive");
	  }
        double a = 1/(pxx*(1- ro * ro));
        double b = -ro/(sqrt(pyy*pxx)*(1- ro * ro)); 
        double c = 1/(pyy*(1- ro * ro));
  
        // calcul des deux valeurs propres
        // la gde vp (lambda1) est associee au petit axe.
        double delta = (a-c)*(a-c)+4*b*b;
        double lambda1 = 0.5*(a+c+sqrt(delta));
        double lambda2 = 0.5*(a+c-sqrt(delta));
  
        // vecteur directeur du grand axe
        double aux = (lambda2-a)/b; 
        double deno=sqrt(1+aux*aux);
        double Ux = 1/deno;
        double Uy = aux/deno;
  
        // longueur des axes dans le repere propre
        double axeX = k/sqrt(lambda2); // demi axe
        double axeY = k/sqrt(lambda1); // demi axe
  
        ellipse(2) = - atan2(Uy, Ux);//heading 
        ellipse(0) = axeY * 2 * 3; // width    x3 (sigma) si PROBA = 0.4 ellipsoide a deux dimensions (test du khi2)
        ellipse(1) = axeX * 2 * 3; //height

        //   heading = - atan2(Uy, Ux); 
        //   width = axeY * 2 * 3; // x3 (sigma) si PROBA = 0.4 ellipsoide a deux dimensions (test du khi2)
        //   height = axeX * 2 * 3; 

       return ellipse; 
    }

   /*!
    * \fn inline boost::numeric::ublas::vector<RealType> Cov2Ellipse(boost::numeric::ublas::matrix<RealType> P,const RealType &proba)
    * \brief Convert 2D covariance to a ellipse parameters
    * \param P : 2D covariance matrix 
    * \param proba : 
    * \return  ublas vector  containing semi-major axis, semi-minor axis and orientation of the ellipse
    */
    template <class RealType> inline boost::numeric::ublas::vector<RealType> Cov2Ellipse(boost::numeric::ublas::matrix<RealType> P,const RealType &proba){
        if(P.size1()==2 & P.size2()==2) throw math_error("Cov2Ellipse: covariance is not a 2D square matrix");
        return Cov2Ellipse(P(0,0),P(0,1),P(1,1),proba);
     }

};
};
#endif
