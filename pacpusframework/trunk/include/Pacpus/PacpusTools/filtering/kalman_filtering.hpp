// %pacpus:license{
// This file is part of the PACPUS framework distributed under the
// CECILL-C License, Version 1.0.
// %pacpus:license}
/// @file
/// @author  Firstname Surname <firstname.surname@utc.fr>
/// @date    Month, Year
/// @version $Id: kalman_filtering.hpp 76 2013-01-10 17:05:10Z kurdejma $
/// @copyright Copyright (c) UTC/CNRS Heudiasyc 2006 - 2013. All rights reserved.
/// @brief Brief description.
///
/// Detailed description.

#ifndef __KALMAN_FILTERING__
#define __KALMAN_FILTERING__

#include "bayes_filtering.hpp"
#include "../math/ublas.hpp"

namespace filter{
namespace kalman{
  using namespace math::ublas;


  /*!
   * \class State
   * \brief This class describes a basic Kalman state
   */
  class State {
    public :

      Vector X; /*!<  State vector */
    
      Matrix P; /*!< Covariance matrix*/ 

      /*!
       * \brief method where the state vector and covariance matrix are allocated 
       * \param state_size : the size of the state vector
       */ 
      void Allocator(const size_t &state_size){
         X=ZeroVector(state_size);
         P=ZeroMatrix(state_size,state_size);
      }

   };

  
  /*!
   * \class DynamicEquation
   * \brief This class describes a basic Kalman dynamic equation
   */
  template <class S=State> class DynamicEquation: public BayesDynamicEquation<S,S>{
   public :
    
       /*!
        * \brief virtual method where matrices of state system must be allocated 
        * \param state_size : the size of the state vector
        * \param data_size : the size of the input vector 
        */ 
       virtual void Allocator(const size_t &state_size,const size_t &data_size)=0;

       /*!
        * \brief virtual method where parameters of the dynamic equation must be evaluated 
        * \param s : the state vector at time k-1 
        */
       virtual void EvaluateParameters(S *s)=0;
  
       /*!
        * \brief virtual method where the a priori state vector must be computed
        * \param in  the state vector at time k-1  
        * \param out  the state vector at time k 
        */
       virtual void Predict(S *in,S *out)=0;
 
       /*! 
        * \brief Destructor 
        */ 
       virtual ~DynamicEquation(){}

       /*!
        * \brief Get/Set data in input vector U
        * \return  vector U
        */ 
       double & U(const int &row){return _U(row);}

       /*!
        * \brief Get/Set data in covariance matrix Q
        * return  matrix Q
        */ 
       double & Q(const int &row, const int &column){return _Q(row,column);}

     protected :
       Vector _U; /*!<   Input vector */

       Matrix _Q; /*!<   Input covariance matrix */
   };

    /*!
    * \class LinearDynamicEquation 
    * \brief This clas dscribes a linear dynamic equation 
    *  \n
    *   X(k+1|k) =A*X(k)+B*U(k) \n
    *   P(k+1|k) = A*P(k+1|k)*A'+B*Q(k)*B' \n
    *   A = state matrix \n
    *   B = input matrix \n
    *   U = input of dynamic system \n
    *   Q = input covariance matrix  \n
    */
    template <class S=State> class LinearDynamicEquation : public DynamicEquation<S>{
      public :
        /*!
        * \brief virtual method where matrices of state system must be allocated 
        * \param state_size : the size of the state vector
        * \param data_size : the size of the input vector 
        */ 
      virtual void Allocator(const size_t &state_size,const size_t &data_size);
        /*!
        * \brief virtual method where parameters of the dynamic equation must be evaluated 
        * \param s : the state vector at time k-1 
        */
      virtual void EvaluateParameters(S *s)=0;

      /*!
        * \brief virtual method where the a priori state vector must be computed
        * \param in : the state vector at time k-1  
        * \param out : the state vector at time k 
        */      
      virtual void Predict(S *in,S *out);

      /*!
       * \brief Destructor 
       */
      virtual ~LinearDynamicEquation(){}

      /*!
       * \brief Get/Set an constant variable in A matrix
       *  \return  A(row,column) 
       */ 
      double & A(const int &row, const int &column){return _A(row,column);}

      /*!
       * \brief Get/Set an constant variable in B matrix
       * \return   B(row,column)
       */ 
      double & B(const int &row, const int &column){return _B(row,column);}

     protected :  
       Matrix _A;   /*!<   A matrix */

       Matrix _B;  /*!<    B matrix */


   };


    // Kalman linear dynamic equation member functions
   template <class S> void LinearDynamicEquation<S>::Allocator(const size_t &state_size,const size_t &data_size){
      DynamicEquation<S>::_U=ZeroVector(data_size);
      DynamicEquation<S>::_Q=ZeroMatrix(data_size,data_size);
      _A=ZeroMatrix(state_size,state_size);
      _B=ZeroMatrix(state_size,data_size);

    }
    
   template <class S> void LinearDynamicEquation<S>::Predict(S *in,S *out){
          EvaluateParameters(in); 
          out->P=_A*in->P*Trans(_A) +_B*DynamicEquation<S>::_Q*Trans(_B);
          out->X=_A*in->X+_B*DynamicEquation<S>::_U; 
    }



    /*!
     *  \class NonLinearDynamicEquation
     *  \brief this class describes a non linear dynamic equation
     *  \n
     *   X(k+1|k) =f(X(k)+U(k)) \n
     *   P(k+1|k) = F*P(k+1|k)*F'+G*Q(k)*G' \n
     *   F= Jacobian of dynamic equation with respect of the state vector \n
     *   G= Jacobian of dynamic equation with respect of the entrie vector \n
     *   U = entrie of dynamic system \n
     *   Q = covariance matrix associated with U \n
     */
    template <class S=State> class NonLinearDynamicEquation : public DynamicEquation<S>{
       public :
       /*!
        * \brief virtual method where matrices of state system must be allocated 
        * \param state_size : the size of the state vector
        * \param data_size : the size of the input vector 
        */ 
        virtual void Allocator(const size_t &state_size,const size_t &data_size);

       /*!
        * \brief virtual method where parameters of the dynamic equation must be evaluated 
        * \param s : the state vector at time k-1 
        * f=
        * F= 
        * G=
        */

      virtual void EvaluateParameters(S *s)=0;

      
      /*!
        * \brief virtual method where the a priori state vector must be computed
        * \param in : the state vector at time k-1  
        * \param out : the state vector at time k 
        */      
      virtual void Predict(S *in,S *out);

      /*! 
       * \brief Destructor 
       */
      virtual ~NonLinearDynamicEquation(){}

      /*!
       * \brief Get/Set a constant variable in F matrix 
       * return : F(row,column)
       */ 
      double & F(const int &row, const int &column){return _F(row,column);}

      /*!
       * \brief Get/Set a constant variable in G matrix 
       * return : G(row,column)
       */ 
      double & G(const int &row, const int &column){return _G(row,column);}
       

       protected:
      
       Vector _f; /*!< Vector f where f(X,U) is stored */  

       Matrix _F; /*!< Jacobian of dynamic equation with respect of the state vector */

       Matrix _G; /*!< Jacobian of dynamic equation with respect of the input vector*/

   };


    // Kalman non linear dynamic equation member functions
    template <class S> void NonLinearDynamicEquation<S>::Allocator(const size_t &state_size,const size_t &data_size){
        DynamicEquation<S>::_U=ZeroVector(data_size);
        DynamicEquation<S>::_Q=ZeroMatrix(data_size,data_size);
        _f=ZeroVector(state_size);
        _F=ZeroMatrix(state_size,state_size);
        _G=ZeroMatrix(state_size,data_size);
     }

    template <class S> void NonLinearDynamicEquation<S>::Predict(S *in,S *out){
         EvaluateParameters(in);
         out->X=_f;
         out->P=_F*in->P*Trans(_F) + _G*DynamicEquation<S>::_Q*Trans(_G);
    }
   


  /*!
   * \class MeasureEquation
   * \brief This class describes a basic Kalman measure equation
   */
   template <class S=State> class MeasureEquation: public BayesMeasureEquation<S,S>{
   public :


       /*!
        * \brief virtual method where matrices of state system must be allocated 
        * \param state_size : the size of the state vector
        * \param data_size : the size of the observation vector 
        */ 
       virtual void Allocator(const size_t &state_size,const size_t &data_size)=0;

       /*!
        * \brief virtual method where parameters of the dynamic equation must be evaluated 
        * \param s  the state vector at time k 
        */
       virtual void EvaluateParameters(S *s)=0;

      /*!
        * \brief virtual method where the a posteriori state vector must be computed
        * \param in : the a priori state vector at time k  
        * \param out : the a posteriori state vector at time k 
        */      
       virtual void Update(S *in,S *out)=0;
 
       /*!
        * \brief Destructor 
        */ 
       virtual ~MeasureEquation(){};

       /*!
        * \brief Get/Set data in observation vector Z 
        * \return  Z(row,column)
        */ 
       double & Z(const int &row){return _Z(row);}

       /*!
        * \brief Get/Set data in observation covariane matrix R
        * return  R(row,column)
        */ 
       double & R(const int &row,const int &column){return _R(row,column);}

       /*!
        * \brief Get/Set observation vector Z
        * return  vector Z
        */ 
       Vector & Z(){return _Z;}
       /*!
        * \brief Get/Set observation covariance matrix R 
        * return  matrix R
        */ 
       Matrix & R(){return _R;}
       
     
       protected :
    
       Vector _Z;  /*!< Observation  vector */

       Matrix _R;  /*!< Observation  covariance matrix */

       Matrix _K;  /*!< Kalman gain matrix */

       
       /*!
        * \brief Coherency of observation data \n
        *  This parameter must be computed in the EvaluateParameters method \n
        *  For kalman filtering the mahalanobis distance is usually used \n
        *  By default the coherency value is true  \n
        */
       bool _coherency;
   };



    /*! 
    *   \class LinearMeasureEquation
    *   \brief This class describes a linear measure equation \n 
    *   X(k+1|k+1)=X(k+1|k)+K(Z(k)-H*X(k+1|k)) \n
    *   P(k+1|k+1) = (I-K*H)P(k+1|k) \n
    *   K=P(k+1|k)*H'/(H*P(k+1|k)*H'+R) \n
    *   H = observation matrix \n
    *   Z = observation data \n
    *   Q = observation covariance matrix \n
    */
    template<class S=State> class LinearMeasureEquation : public MeasureEquation<S>{
      public :
       /*!
        * \brief virtual method where matrices of state system must be allocated 
        * \param state_size : the size of the state vector
        * \param data_size : the size of the observation vector 
        */ 
       virtual void Allocator(const size_t &state_size,const size_t &data_size);

       /*!
        * \brief virtual method where parameters of the dynamic equation must be evaluated 
        * \param s : the state vector at time k 
        */
       virtual void EvaluateParameters(S *s)=0;

        /*!
        * \brief virtual method where the a posteriori state vector must be computed
        * \param in : the a priori state vector at time k  
        * \param out : the a posteriori state vector at time k 
        */  
       virtual void Update(S *in,S *out);

       /*!
        *  \brief Destructor 
        */
       virtual ~LinearMeasureEquation(){}

       /*!
        * \brief Get/Set an constant variable in observation matrix H 
        */ 
       double & H(int row, int column){return _H(row,column);}

      protected:  

       Matrix _H; /*!< Observation matrix */

   };


    // Kalman  linear measure equation member functions
    template <class S> void LinearMeasureEquation<S>::Allocator(const size_t &state_size,const size_t &data_size){
        MeasureEquation<S>::_Z=ZeroVector(data_size);
        MeasureEquation<S>::_R=ZeroMatrix(data_size,data_size);
        _H=ZeroMatrix(data_size,state_size);
        MeasureEquation<S>::_coherency=true;
    }
    
    template <class S> void LinearMeasureEquation<S>::Update(S *in,S *out){
         MeasureEquation<S>::_coherency=true;
         EvaluateParameters(in);  

         if(MeasureEquation<S>::_coherency){
            MeasureEquation<S>::_K=in->P*Trans(_H) *InvQR( _H*in->P*Trans(_H) +MeasureEquation<S>::_R );     
             out->X=in->X + MeasureEquation<S>::_K*(MeasureEquation<S>::_Z - _H*in->X);       
             out->P=in->P - MeasureEquation<S>::_K*_H*in->P;
         }
    }


    /*!
    *   \class NonLinearMeasureEquation
    *   \brief This clas describes a non linear measure equation \n
    *   X(k+1|k+1)=X(k+1|k)+K(Z(k)-h(X(k+1|k))) \n
    *   P(k+1|k+1) = (I-K*H)P(k+1|k) \n
    *   K=P(k+1|k)*H'/(H*P(k+1|k)*H'+R) \n
    *   H = jacobian matrix of h() with respect of X \n
    *   Z = observation data \n
    *   Q = covariance matrix associated with Z \n
    */
    template <class S=State> class NonLinearMeasureEquation : public MeasureEquation<S>{
      public :
       /*!
        * \brief virtual method where matrices of state system must be allocated 
        * \param state_size : the size of the state vector
        * \param data_size : the size of the observation vector 
        */ 
       virtual void Allocator(const size_t &state_size,const size_t &data_size);

       /*!
        * \brief virtual method where parameters of the dynamic equation must be evaluated 
        * \param s : the state vector at time k   
        * h=
        * H=
        */
       virtual void EvaluateParameters(S *s )=0;

        /*!
        * \brief virtual method where the a posteriori state vector must be computed
        * \param in : the a priori state vector at time k  
        * \param out : the a posteriori state vector at time k 
        */  
       virtual void Update(S *in,S *out); 
       
        /** destructor */
       virtual ~NonLinearMeasureEquation(){}

        /*!
         * \brief Get/Set  constant data in H matrix  
         * \return H(row,column) 
         */ 
        double & H(const int &row,const int &column){return _H(row,column);}

      protected :  
        


       Matrix _H;   /*!< Jacobian of measure equation with respect of the state vector */
     
       Vector _h;   /*!< Vector f where h(X) is stored */  

   };

    // Kalman  non linear measure equation member functions
    template <class S> void NonLinearMeasureEquation<S>::Allocator(const size_t &state_size,const size_t &data_size){
        MeasureEquation<S>::_Z=ZeroVector(data_size);
        MeasureEquation<S>::_R=ZeroMatrix(data_size,data_size);
        _H=ZeroMatrix(data_size,state_size);
        _h=ZeroVector(data_size);
    }
    
    template <class S> void NonLinearMeasureEquation<S>::Update(S *in,S *out){
         MeasureEquation<S>::_coherency=true;
         EvaluateParameters(in);   

         if(MeasureEquation<S>::_coherency){ 
             MeasureEquation<S>::_K=in->P*Trans(_H) *( InvLU(_H*in->P*Trans(_H) + MeasureEquation<S>::_R));
             out->X=in->X+MeasureEquation<S>::_K*(MeasureEquation<S>::_Z-_h);
             out->P=in->P-MeasureEquation<S>::_K*_H*in->P;
         }
    }
} // namespace kalman
} // namespace filter

#endif // __KALMAN_FILTERING__
